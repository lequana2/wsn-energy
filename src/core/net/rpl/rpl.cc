/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rpl.h
 */

#include <rpl.h>

#include <algorithm>

#include "mac.h"
#include "ipv6.h"
#include "energest.h"
#include "hopEnergy.h"
#include "statistic.h"
#include "packet_m.h"

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

  // Self timer
  this->dioTimer = new Command;
  this->dioTimer->setKind(COMMAND);
  this->dioTimer->setNote(NET_TIMER_DIO);

  // Self timer
  this->disTimer = new Command;
  this->disTimer->setKind(COMMAND);
  this->disTimer->setNote(NET_TIMER_DIS);

  this->isDIOsent = true; // 0 to sent ~ success !!!
  this->isDISsent = true; // 0 to sent ~ success !!!

  // create DIO timer
  resetDIOTimer();

  // create DIS timer
  this->net->scheduleAt(this->net->getModuleByPath("^.^")->par("setupDelay").doubleValue(), disTimer);
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
  if (simulation.getModuleByPath("WSN")->par("usingELB").boolValue())
  {
    this->rplDag.rank = 256;
  }
  else
  {
    this->rplDag.rank = 1;
  }
//  sendDIO();
}

void RPL::finish()
{
  this->net->cancelAndDelete(dioTimer);
  this->net->cancelAndDelete(disTimer);
}

void RPL::sendDIO()
{
  if (DEBUG)
    ev << "Broadcast DIO" << endl;

  DIO *dio = new DIO;
  dio->setKind(DATA);
  dio->setByteLength(dio->getPayloadLength());
  dio->setSenderID(this->net->getId());

  dio->setDodagID(this->rplDag.dodagID);
  dio->setVersion(this->rplDag.version);
  dio->setRank(this->rplDag.rank);

  IcmpPacket *icmpPacket = new IcmpPacket;
  icmpPacket->setKind(DATA);
  icmpPacket->setByteLength(icmpPacket->getHeaderLength());

  icmpPacket->setType(ICMP_RPL);
  icmpPacket->setCode(RPL_DIO_CODE);

  icmpPacket->encapsulate(dio);

  net->multicast(icmpPacket);

//  this->isDIOsent = false; // keep track of lastest DIO
}

void RPL::sendDIS()
{
  if (DEBUG)
    ev << "Broadcast DIS" << endl;

  DIS* dis = new DIS;
  dis->setKind(DATA);
  dis->setByteLength(dis->getPayloadLength());

  IcmpPacket *icmpPacket = new IcmpPacket;
  icmpPacket->setKind(DATA);
  icmpPacket->setByteLength(icmpPacket->getHeaderLength());

  icmpPacket->setType(ICMP_RPL);
  icmpPacket->setCode(RPL_DIS_CODE);

  icmpPacket->encapsulate(dis);

  net->multicast(icmpPacket);

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
      this->net->cancelEvent(dioTimer);
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

void RPL::processICMP(IcmpPacket *icmpPacket)
{
  switch (icmpPacket->getCode())
  {
    case RPL_DIO_CODE: /* receiving DIO */
    {
      this->processDIO(check_and_cast<DIO*>(icmpPacket->getEncapsulatedPacket()));

      /* consider preferred parent is un-nultified under behavior of DIO */
      if (this->rplDag.preferredParent != NULL)
        this->net->selfTimer(0, NET_CHECK_BUFFER); // prepare to send data again

      delete icmpPacket;

      break;
    } /* receiving DIO */

    case RPL_DIS_CODE: /* receiving DIS */
    {
      this->processDIS(check_and_cast<DIS*>(icmpPacket->getEncapsulatedPacket()));

      delete icmpPacket;

      break;
    } /* receiving DIS */

    default:
      delete icmpPacket;
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

  // process DIO
  neighbor->neighborID = dio->getSenderID();
  neighbor->neighborRank = dio->getRank();

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
          if (DEBUG)
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

          this->updatePrefferredParent(); // Update preferred parent
        }
        // same rank, update quality
        else if ((*oldParent)->neighborRank == neighbor->neighborRank)
        {
          this->updatePrefferredParent(); // Update preferred parent
        }
        // worse rank
        else
        {
          // is sole parent ?
          if (this->rplDag.parentList.size() == 1)
          {
            // if yes, update
            (*oldParent)->neighborRank = neighbor->neighborRank;
          }
          else
          {
            // else, remove this parent
            this->rplDag.parentList.remove(*oldParent);
            this->updatePrefferredParent();
          }
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
    this->resetDIOTimer();
}

void RPL::purgeRoute()
{
  // should remove default route and update preffered parent ?
//  if (this->rplDag.parentList.size() == 1)
//  {
//    // in case of only 1 default route left
//    this->sendDIS();
//    return;
//  }

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

  RPL_neighbor *tentativeParent = this->rplDag.of->updatePreferredParent(this->rplDag.parentList);

  if (tentativeParent != NULL)
  {
    if (this->rplDag.preferredParent == NULL)
    {
      this->rplDag.preferredParent = tentativeParent;
    }
    else
    {
      this->rplDag.preferredParent =
          this->rplDag.preferredParent->neighborRank <= tentativeParent->neighborRank ? this->rplDag.preferredParent :
              tentativeParent;
    }
  }
  else
  {
    this->rplDag.preferredParent = NULL;
  }

  // draw new preferred parent (if exist)
  if (ANNOTATE_DEFAULT_ROUTE && this->rplDag.preferredParent != NULL)
  {
    char channelParent[20];
    sprintf(channelParent, "out %d to %d", this->net->getParentModule()->getId(),
    simulation.getModule(this->rplDag.preferredParent->neighborID)->getParentModule()->getId());
    simulation.getModule(this->net->getParentModule()->getId())->gate(channelParent)->setDisplayString("ls=purple,1");
  }

  // update default route
  if (this->rplDag.preferredParent != NULL)
  {
    this->net->defaultRoute = this->rplDag.preferredParent->neighborID;

    // mac default route in case of mesh-routing / IPv6
    if (this->net->getModuleByPath("^.^")->par("usingHDC"))
      (check_and_cast<MACdriver*>(this->net->getModuleByPath("^.mac")))->defaultRoute = simulation.getModule(
          this->net->defaultRoute)->getModuleByPath("^.mac")->getId();

    // route is repaired, ready to send
    this->net->selfTimer(0, NET_CHECK_BUFFER);
  }
  else
  {
    this->net->defaultRoute = 0;

    // mac default route in case of mesh-routing / IPv6
    if (this->net->getModuleByPath("^.^")->par("usingHDC"))
      (check_and_cast<MACdriver*>(this->net->getModuleByPath("^.mac")))->defaultRoute = 0;
  }
}
}/* namespace wsn_energy */
