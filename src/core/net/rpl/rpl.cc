//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <rpl.h>

#include <algorithm>

#include "ipv6.h"
#include "energest.h"
#include "hopEnergy.h"

#ifndef ANNOTATE
#define ANNOTATE 1
#endif

#ifndef ANNOTATE_PARENT
#define ANNOTATE_PARENT 1
#endif

#ifndef ANNOTATE_SIBLINGS
#define ANNOTATE_SIBLINGS 0
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

RPL::RPL(IPv6 *net)
{
  this->net = net;
  this->rpl_init();
}

void RPL::rpl_init()
{
  this->rplDag.version = 0;
  this->rplDag.joined = false;
  this->rplDag.rank = RANK_INFINITY;
  this->rplDag.preferredParent = NULL;

  // choosing objective function
  this->rplDag.of = new hopEnergy;
}

void RPL::rpl_set_root()
{
  this->rplDag.version++;
  this->rplDag.joined = true;
  this->rplDag.rank = 1;
}

void RPL::sendDIO()
{
  ev << "Broadcast DIO" << endl;

  DIO *icmp = new DIO();

  icmp->setMessageCode(NET_ICMP_RPL);
  icmp->setIcmpCode(NET_ICMP_DIO);
  icmp->setByteLength(DIO_LEN);
  icmp->setVersion(this->rplDag.version);
  icmp->setRank(this->rplDag.rank);

  icmp->setSelfEnergy(
      (check_and_cast<Energest*>(this->net->getParentModule()->getModuleByPath(".energest")))->energestRemaining);

  net->multicast(icmp);
}

void RPL::sendDIS(int hopTTL)
{
  if (DEBUG)
    ev << "Broadcast DIS" << endl;

  DIS *icmp = new DIS();

  icmp->setMessageCode(NET_ICMP_RPL);
  icmp->setIcmpCode(NET_ICMP_DIO);
  icmp->setByteLength(DIS_LEN);
  icmp->setHopTTL(hopTTL);

  net->multicast(icmp);
}

void RPL::processICMP(IpPacket *packet)
{
  switch (packet->getIcmpCode())
  {
    case NET_ICMP_DIO: /* receiving DIO */
    {
      this->processDIO(check_and_cast<DIO*>(packet));
      break;
    } /* receiving DIO */

    case NET_ICMP_DIS: /* receiving DIS */
    {
      this->processDIS(check_and_cast<DIS*>(packet));
      break;
    } /* receiving DIS */

    default:
      if (DEBUG)
        ev << "Missing resolution" << endl;
      break;
  }

  delete packet; // done icmp
}

void RPL::processDIO(DIO* dio)
{
  if (DEBUG)
    ev << "Received DIO " << endl;

  // Consider neighborID
  RPL_neighbor *neighbor = new RPL_neighbor();
  neighbor->neighborID = dio->getSenderIpAddress();
  neighbor->neighborRank = dio->getRank();
  neighbor->nodeQuality.energy = dio->getSelfEnergy();

  if (!this->rplDag.joined)
  {
    this->rplDag.parentList.push_back(neighbor);

    this->rplDag.version = dio->getVersion();
    this->rplDag.joined = true;
    this->rplDag.rank = this->rplDag.of->calculateRank(neighbor);

    this->rplDag.parentList.push_back(neighbor);
    this->rplDag.preferredParent = this->rplDag.of->updatePreferredParent(this->rplDag.parentList);

    // draw new connection
    if (ANNOTATE_PARENT)
    {
      char channelParent[20];
      sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
          (simulation.getModule(neighbor->neighborID))->getParentModule()->getId());
      EV << "new version: " << channelParent << endl;
      net->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
    }

    this->sendDIO();
  }
  else
  {
    // Consider neighbor version
    if (this->rplDag.version < dio->getVersion())
    {
      // Update self information
      this->rplDag.version = dio->getVersion();
      this->rplDag.joined = true;
      this->rplDag.rank = this->rplDag.of->calculateRank(neighbor);

      this->rplDag.parentList.clear();
      this->rplDag.preferredParent = this->rplDag.of->updatePreferredParent(this->rplDag.parentList);

      // remove annotate
      if (ANNOTATE)
        for (std::list<RPL_neighbor*>::iterator oldParent = this->rplDag.parentList.begin();
            oldParent != this->rplDag.parentList.end(); oldParent++)
        {
          char channelParent[20];
          sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
              (simulation.getModule((*oldParent)->neighborID))->getParentModule()->getId());
          net->getParentModule()->gate(channelParent)->setDisplayString("ls=,0");
        }

      // draw new connection
      if (ANNOTATE_PARENT)
      {
        char channelParent[20];
        sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
            (simulation.getModule(neighbor->neighborID))->getParentModule()->getId());
        EV << "new version: " << channelParent << endl;
        net->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
      }

      // Different
      this->sendDIO();
    }

    // obsolete/maintenace DIO
    else if (this->rplDag.version >= dio->getVersion())
    {
      bool isNewParent = true;

      // Consider parent
      std::list<RPL_neighbor*>::iterator oldParent = this->rplDag.parentList.begin();
      for (; oldParent != this->rplDag.parentList.end(); oldParent++)
      {
        if ((*oldParent)->neighborID == neighbor->neighborID)
        {
          isNewParent = false;
          break;
        }
      }

      if (isNewParent)
      {
        // better rank
        if (this->rplDag.rank > dio->getRank())
        {
          ev << "new neighbor" << endl;
          // Update new neighbor
          this->rplDag.parentList.push_back(neighbor);

          // draw new connection
          if (ANNOTATE_PARENT)
          {
            char channelParent[20];
            sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
                (simulation.getModule(neighbor->neighborID))->getParentModule()->getId());
            EV << "update: " << channelParent << endl;
            net->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
          }

          // Update preferred parent
          this->rplDag.preferredParent = this->rplDag.of->updatePreferredParent(this->rplDag.parentList);

          // Update parent
          this->sendDIO();
        }
        // WSN siblings, same rank
        else if (this->rplDag.rank == dio->getRank())
        {
//          // New neighbor
//          if (candidate == this->rplDag.parentList.end())
//          {
//            ev << "new neighbor" << endl;
//            // Update new neighbor
//            // this->rplDag.parentList.push_back(neighbor);
//
//            if (ANNOTATE_SIBLINGS)
//            {
//              char channelParent[20];
//              sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
//                  (simulation.getModule(neighbor->neighborID))->getParentModule()->getId());
//              EV << channelParent << endl;
//              net->getParentModule()->gate(channelParent)->setDisplayString("ls=blue,1");
//            }
//          }
//          // Update sibling
        }
        // WSN not better rank
        else
        {
          // Discard DIO
        }
      }
      // Old parent
      else
      {
        if ((*oldParent)->neighborRank < neighbor->neighborRank)
        {
          // better -> update
          (*oldParent)->neighborRank = neighbor->neighborRank;
          (*oldParent)->neighborRank = neighbor->nodeQuality.energy;

          // Update preferred parent
          this->rplDag.preferredParent = this->rplDag.of->updatePreferredParent(this->rplDag.parentList);
        }
        else
        {
          // WSN not better
        }
        return;
      }
    }

    // Bubble current rank
    if (ANNOTATE)
    {
      char rank[10];
      sprintf(rank, "Rank %d", (int) this->rplDag.rank);
      net->getParentModule()->bubble(rank);
    }
  }
}

void RPL::processDIS(DIS* msg)
{
  if (DEBUG)
    EV << "Received DIS " << endl;

// currently in DAG, then broadcast DIS
  if (this->rplDag.joined)
  {
    this->sendDIO();
  }
// already
  else
  {
//WSN broadcast DIS toward root
//    int convergence = ((DIS*) msg)->getConvergence();
//    if (convergence > 0)
//      this->sendDIS(convergence - 1);
  }
}
}/* namespace wsn_energy */
