/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rpl.h
 */

#include <rpl.h>

#include <algorithm>

#include "ipv6.h"
#include "energest.h"
#include "hopEnergy.h"
#include "statistic.h"

#ifndef DODAG_PAR
#define DODAG_PAR
#define RPL_DIO_INTERVAL_MIN          12 // 2 ^ 12 = 4096 ms = 4s, based on ContikiRPL
#define RPL_DIO_INTERVAL_DOUBLINGS     8 // 2 ^ (8+12) = 1048576 ms = 17 min, based on ContikiRPL
#define RPL_DIO_REDUNDANCY            10 // further RFC 6206, 10 is specified in RFC 6550
#endif

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef ANNOTATE_DEFAULT_ROUTE
#define ANNOTATE_DEFAULT_ROUTE 1
#endif

#ifndef ANNOTATE_PARENT
#define ANNOTATE_PARENT 0
#endif

#ifndef ANNOTATE_SIBLINGS
#define ANNOTATE_SIBLINGS 0
#endif

namespace wsn_energy {

RPL::RPL(IPv6 *net)
{
  this->net = net;
  this->rpl_init();

  this->dioTimer = new Command;
  this->dioTimer->setKind(COMMAND);
  this->dioTimer->setNote(NET_TIMER_DIO);

  this->disTimer = new Command;
  this->disTimer->setKind(COMMAND);
  this->disTimer->setNote(NET_TIMER_DIS);

  this->isDIOsent = true; // 0 to sent ~ success !!!
  this->isDISsent = true; // 0 to sent ~ success !!!
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

  sendDIO();
}

void RPL::finish()
{
  if (dioTimer->isSelfMessage())
    this->net->cancelAndDelete(dioTimer);
  if (disTimer->isSelfMessage())
    this->net->cancelAndDelete(disTimer);
}

void RPL::sendDIO()
{
  ev << "Broadcast DIO" << endl;

  DIO *dio = new DIO();

  dio->setMessageCode(NET_ICMP_RPL);
  dio->setIcmpCode(NET_ICMP_DIO);
  dio->setVersion(this->rplDag.version);
  dio->setRank(this->rplDag.rank);
  dio->setByteLength(DIO_LEN);

  dio->setSelfEnergy(
      (check_and_cast<Energest*>(this->net->getParentModule()->getModuleByPath(".energest")))->energestRemaining);

  net->multicast(dio);

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(DIO_SENT));

  this->isDIOsent = false; // keep track of lastest DIO
}

void RPL::sendDIS()
{
  if (DEBUG)
    ev << "Broadcast DIS" << endl;

  DIS *dis = new DIS();

  dis->setMessageCode(NET_ICMP_RPL);
  dis->setIcmpCode(NET_ICMP_DIS);
  dis->setByteLength(DIS_LEN);

  net->multicast(dis);

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(DIS_SENT));

  this->isDISsent = false; // keep track of lastest DIS
}

void RPL::hasSentDIO()
{
  this->isDIOsent = true;
}

void RPL::hasSentDIS()
{
  this->isDISsent = true;
}

void RPL::resetDIOTimer()
{
  // reset to initial stage
  dioCurrent = RPL_DIO_INTERVAL_MIN;
  newDIOinterval();
}

void RPL::newDIOinterval()
{
  // reset counter
  dioCounter = 0;

  // create new interval
  dioInterval = 1 << dioCurrent;  // millis

  /* random number between I/2 and I */
  if (this->net->getModuleByPath("^.^")->par("rand").doubleValue() == 0)
    dioDelay = (dioInterval / 2.0 + ((rand() % 1000) / 2000.0) * dioInterval) / 1000.0;      // convert to sec
  else if (this->net->getModuleByPath("^.^")->par("rand").doubleValue() == 1)
    dioDelay = (dioInterval / 2.0 + (intuniform(0, 1000) / 2000.0) * dioInterval) / 1000.0;      // convert to sec

  if (DEBUG)
    std::cout << this->net->getId() << " has DIO interval: " << dioDelay << "(second)" << " of " << dioCurrent << " at "
        << simTime() << endl;

  // simulation break
  if (simTime() + dioDelay < this->net->getModuleByPath("^.^")->par("timeLimit").doubleValue())
  {
    this->net->cancelEvent(dioTimer);
    this->net->scheduleAt(simTime() + dioDelay, dioTimer);
  }
}

void RPL::handleDIOTimer()
{
  // handle when timer expired
  if (!this->rplDag.joined || !isDIOsent) // link local not OK or last DIO didn't sent
  {
    if (simTime() + dioDelay < this->net->getModuleByPath("^.^")->par("timeLimit").doubleValue())
    {
      this->net->cancelEvent(dioTimer);
      this->net->scheduleAt(simTime() + dioDelay, dioTimer);
    }
    else
    {
      this->net->cancelAndDelete(dioTimer);
      return;
    }
  }
  // do not exceed redundancy
  else if (dioCounter < RPL_DIO_REDUNDANCY)
  {
    sendDIO();
    dioCounter++;
    if (simTime() + dioDelay < this->net->getModuleByPath("^.^")->par("timeLimit").doubleValue())
    {
      this->net->cancelEvent(dioTimer);
      this->net->scheduleAt(simTime() + dioDelay, dioTimer);
    }
  }
  // exceed redundancy, double interval
  else
  {
    if (dioCurrent < RPL_DIO_INTERVAL_MIN + RPL_DIO_INTERVAL_DOUBLINGS)
      dioCurrent++;
    newDIOinterval();
  }
}

void RPL::handleDISTimer()
{
  // simulation break
  if (simTime() + 1 > this->net->getModuleByPath("^.^")->par("timeLimit").doubleValue())
  {
    this->net->cancelAndDelete(this->disTimer);
    return;
  }

  this->net->cancelEvent(this->disTimer);

  if (!this->rplDag.joined && isDISsent)
    sendDIS();
  else
    this->net->scheduleAt(simTime() + 1, disTimer);
}

void RPL::processICMP(IpPacket *packet)
{
  switch (packet->getIcmpCode())
  {
    case NET_ICMP_DIO: /* receiving DIO */
    {
      this->processDIO(check_and_cast<DIO*>(packet));
      /* consider preferred parent is un-nultified under behavior of DIO */
      if (this->rplDag.preferredParent != NULL)
        this->net->selfTimer(0, NET_CHECK_BUFFER); // prepare to send data again

      delete packet;
      break;
    } /* receiving DIO */

    case NET_ICMP_DIS: /* receiving DIS */
    {
      this->processDIS(check_and_cast<DIS*>(packet));
      delete packet;
      break;
    } /* receiving DIS */

    default:
      if (DEBUG)
        ev << "Missing resolution" << endl;
      break;
  }
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
    this->updatePrefferredParent();

    // draw new connection
    if (ANNOTATE_PARENT)
    {
      char channelParent[20];
      sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
          (simulation.getModule(neighbor->neighborID))->getParentModule()->getId());
      EV << "new version: " << channelParent << endl;
      net->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
    }

    this->resetDIOTimer();
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

      // remove out-of-date parents
      if (ANNOTATE_PARENT)
        for (std::list<RPL_neighbor*>::iterator oldParent = this->rplDag.parentList.begin();
            oldParent != this->rplDag.parentList.end(); oldParent++)
        {
          char channelParent[20];
          sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
              (simulation.getModule((*oldParent)->neighborID))->getParentModule()->getId());
          net->getParentModule()->gate(channelParent)->setDisplayString("ls=,0");
        }

      this->rplDag.parentList.clear();
      this->rplDag.parentList.push_back(neighbor);
      this->updatePrefferredParent();

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
      this->resetDIOTimer();
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
          this->updatePrefferredParent();

          // Update parent
          this->resetDIOTimer();
        }
        // siblings, same rank (DMR)
        else if (this->net->getModuleByPath("^.^")->par("usingFLR").boolValue() && this->rplDag.rank == dio->getRank())
        {
          // New neighbor
          if (DEBUG)
            ev << "New sibling" << endl;

          // Update new neighbor
          this->rplDag.siblingList.push_back(neighbor);

          if (ANNOTATE_SIBLINGS)
          {
            char channelParent[20];
            sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
                (simulation.getModule(neighbor->neighborID))->getParentModule()->getId());
            EV << channelParent << endl;
            net->getParentModule()->gate(channelParent)->setDisplayString("ls=blue,1");
          }

          // Update preferred parent
          this->updatePrefferredParent();
        }
        // not better rank
        else
        {
          // Discard DIO
          return;
        }
      }
      // Old parent
      else
      {
        // better rank
        if ((*oldParent)->neighborRank < neighbor->neighborRank)
        {
          (*oldParent)->neighborRank = neighbor->neighborRank;  // update rank

          (*oldParent)->nodeQuality.energy = neighbor->nodeQuality.energy; // update note quality

          this->updatePrefferredParent(); // Update preferred parent
        }
        // same rank, update quality
        else if ((*oldParent)->neighborRank == neighbor->neighborRank)
        {
          (*oldParent)->nodeQuality.energy = neighbor->nodeQuality.energy; // Update node quality

          this->updatePrefferredParent(); // Update preferred parent
        }
        // worse rank
        else
        {
          // WSN is sole parent ?
          // WSN if yes, update
          // WSN else, remove this parent
        }
        return;
      }
    }
  }

  // Bubble current rank
  if (DEBUG)
  {
    char rank[10];
    sprintf(rank, "Rank %d", (int) this->rplDag.rank);
    net->getParentModule()->bubble(rank);
  }
}

void RPL::processDIS(DIS* msg)
{
  if (DEBUG)
    EV << "Received DIS " << endl;

  // currently in DAG, then broadcast DIS
  if (this->rplDag.joined)
  {
    this->resetDIOTimer();
  }
}

void RPL::purgeRoute()
{
  // remove default route and update preffered parent
  this->rplDag.parentList.remove(this->rplDag.preferredParent);
  this->updatePrefferredParent();

  // if no parent found
  if (this->rplDag.preferredParent == NULL)
  {
    // fast-local repair
    if (this->net->getModuleByPath("^.^")->par("usingFLR").boolValue() && this->rplDag.siblingList.size() != 0)
    {
      // Self increase rank
      this->rplDag.rank++;

      // Debate all siblings in parent list
      for (std::list<RPL_neighbor*>::iterator it = this->rplDag.siblingList.begin();
          it != this->rplDag.siblingList.end(); it++)
        this->rplDag.parentList.push_back(*it);
      this->rplDag.siblingList.clear();
      this->updatePrefferredParent();
    }
    // local repair
    else
    {
      this->rplDag.rank = RANK_INFINITY;
      this->rplDag.joined = false;
      this->sendDIS();
    }
  }
}

void RPL::updatePrefferredParent()
{
  // delete old preferred parent (if needed)
  if (ANNOTATE_DEFAULT_ROUTE && this->rplDag.preferredParent != NULL)
  {
    char channelParent[20];
    sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
    simulation.getModule(this->rplDag.preferredParent->neighborID)->getParentModule()->getId());
    simulation.getModule(this->net->getParentModule()->getId())->gate(channelParent)->setDisplayString("ls=,0");
  }

  this->rplDag.preferredParent = this->rplDag.of->updatePreferredParent(this->rplDag.parentList);

  // draw new preferred parent (if exist)
  if (ANNOTATE_DEFAULT_ROUTE && this->rplDag.preferredParent != NULL)
  {
    char channelParent[20];
    sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
    simulation.getModule(this->rplDag.preferredParent->neighborID)->getParentModule()->getId());
    simulation.getModule(this->net->getParentModule()->getId())->gate(channelParent)->setDisplayString("ls=purple,1");
  }
}
}/* namespace wsn_energy */
