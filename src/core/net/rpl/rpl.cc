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

#include "core.h"

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

RPL::RPL()
{
}

RPL::~RPL()
{
//  this->neighborList.clear();
}

RPL::RPL(Core *core)
{
  this->rpl_init();
  this->core = core;
}

void RPL::rpl_init()
{
  this->rplDag.version = 0;
  this->rplDag.joined = false;
  this->rplDag.rank = RANK_INFINITY;
}

void RPL::rpl_set_root()
{
  this->rplDag.version++;
  this->rplDag.joined = true;
  this->rplDag.rank = 0;

  // WSN Should send continously, trickle timer ???
  cMessage *constructMessage = new cMessage();
  constructMessage->setKind(RPL_CONSTRUCT);
  core->scheduleAt(simTime(), constructMessage);
}

void RPL::sendDIO()
{
  ev << "broadcast DIO" << endl;

  DIO *icmp = new DIO();
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);
  ((IpPacket*) icmp)->setType(IP_ICMP);

  icmp->setDodagID(this->rplDag.version);
  icmp->setRank(this->rplDag.rank);

  core->broadcast(icmp);
}

void RPL::sendDIS(int convergence)
{
  ev << "broadcast DIS" << endl;

  DIS *icmp = new DIS();
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIS_CODE);
  ((IpPacket*) icmp)->setType(IP_ICMP);

  icmp->setConvergence(convergence);

  core->broadcast(icmp);
}

void RPL::receiveDIO(DIO* msg)
{
  ev << "Received DIO " << endl;

  // Consider neighborID
  RPL_neighbor *neighbor = new RPL_neighbor();
  neighbor->neighborID = msg->getRadioSendId();
  neighbor->neighborRank = msg->getRank();

  // incoming neighbor message
  std::list<RPL_neighbor*>::iterator candidate = this->rplDag.parentList.begin();
  for (; candidate != this->rplDag.parentList.end(); candidate++)
  {
    // Update own neighbor
    if (neighbor->neighborID == (*candidate)->neighborID)
    {
      neighbor->neighborRank = (*candidate)->neighborRank;
    }
  }

  // Consider neighbor dodagID
  if (this->rplDag.version < msg->getDodagID())
  {
    // Update self information
    this->rplDag.version = msg->getDodagID();
    this->rplDag.joined = true;
    this->rplDag.rank = msg->getRank() + 1; // WSN hop count

    // New neighbor
    if (candidate == this->rplDag.parentList.end())
    {
      ev << "new neighbor" << endl;
      // Update new neighbor
      this->rplDag.parentList.push_back(neighbor);

      // draw new connection
      char channelParent[20];
      sprintf(channelParent, "out %d to %d", msg->getRadioRecvId(), msg->getRadioSendId());
      EV << channelParent << endl;
      core->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");

      // Different
      this->sendDIO();
    }
  }
  // obsolete/maintenace DIO
  else if (this->rplDag.version >= msg->getDodagID())
  {
    if (this->rplDag.rank > msg->getRank())
    {
      // New neighbor
      if (candidate == this->rplDag.parentList.end())
      {
        ev << "new neighbor" << endl;
        // Update new neighbor
        this->rplDag.parentList.push_back(neighbor);

        // draw new connection
        char channelParent[20];
        sprintf(channelParent, "out %d to %d", ((Raw*) msg)->getRadioRecvId(), ((Raw*) msg)->getRadioSendId());
        EV << channelParent << endl;
        core->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
      }
      // Update parent
      this->sendDIO();
    }
    else if (this->rplDag.rank == msg->getRank())
    {
      // New neighbor
      if (candidate == this->rplDag.parentList.end())
      {
        ev << "new neighbor" << endl;
        // Update new neighbor
        this->rplDag.parentList.push_back(neighbor);

        // draw new connection
        char channelParent[20];
        sprintf(channelParent, "out %d to %d", ((Raw*) msg)->getRadioRecvId(), ((Raw*) msg)->getRadioSendId());
        EV << channelParent << endl;
        core->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
      }
      // Update sibling
    }
    else
      // Discard DIO
      return;
  }

  // Bubble current rank
  char rank[10];
  sprintf(rank, "Rank %d", (int) this->rplDag.rank);
  core->getParentModule()->bubble(rank);
}

void RPL::receiveDIS(DIS* msg)
{
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

RPL_neighbor* RPL::getPrefferedParent()
{
  std::list<RPL_neighbor*> goodParent;
  for (std::list<RPL_neighbor*>::iterator iterator = this->rplDag.parentList.begin();
      iterator != this->rplDag.parentList.end(); iterator++)
  {
    if ((*iterator)->neighborRank < this->rplDag.rank)
      goodParent.push_back(*iterator);
  }

  RPL_neighbor *prefferedParent = goodParent.front();
  for (std::list<RPL_neighbor*>::iterator iterator = goodParent.begin(); iterator != goodParent.end(); iterator++)
  {
    if ((*iterator)->neighborRank < prefferedParent->neighborRank)
      prefferedParent = *iterator;
  }

  return prefferedParent;
}

} /* namespace wsn_energy */
