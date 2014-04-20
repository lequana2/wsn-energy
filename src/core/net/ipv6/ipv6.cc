/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to ipv6.h
 */

#include <math.h>

#include "world.h"
#include "statistic.h"
#include "ipv6.h"
#include "rpl.h"
#include "energest.h"
#include "count.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(IPv6);

void IPv6::initialize()
{
  this->rpl = new RPL(this);
  this->pendingPacket = NULL;

  selfTimer(0.000016, NET_TIMER_DIS);
}

void IPv6::finish()
{
  // WSN Clear queue !!!
  std::cout << "SEND (NET) remaining: " << this->ipPacketQueue.size() << " @ " << this->getParentModule()->getFullName()
      << endl;

  for (std::list<IpPacket*>::iterator it = this->ipPacketQueue.begin(); it != this->ipPacketQueue.end(); it++)
    cancelAndDelete(*it);
  this->ipPacketQueue.clear();

  this->rpl->finish();
}

void IPv6::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case NET_CHECK_BUFFER: /* Check buffer */
        {
          if (ipPacketQueue.size() == 0) // empty, do nothing, reset flag
          {
            pendingPacket = NULL;
          }
          else if (pendingPacket == NULL) // do not have any pending packet
          {
            if (DEBUG)
              std::cout << "SEND (NET) remaining: " << this->ipPacketQueue.size() << " @ " << this->getId() << endl;

            // get packet and sen to MAC layer
            preparePacketToBeSent();

            if (pendingPacket == NULL)
            {
              // unsuccessful dequeue, just ignore and wait for another check
            }
            else
            {
              // successful dequeue
              sendMessageToLower(pendingPacket->dup());
            }
          }
          delete packet;
          break;
        } /* Check buffer */

        case NET_TIMER_DIO: /* DIO timer*/
        {
          this->rpl->handleDIOTimer();
          break;
        } /* DIO timer*/

        case NET_TIMER_DIS: /* Solicit DODAG information*/
        {
          this->rpl->handleDISTimer();
          break;
        } /* Solicit DODAG information */

        default:
          delete packet;
          if (DEBUG)
            std::cout << "Unknown command" << endl;
          break;
      }
      break;
    } /* Command */

    default:
      if (DEBUG)
        std::cout << "Unknown kind" << endl;
      break;
  }
}

void IPv6::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      IpPacket *dataMessage = new IpPacket;
      dataMessage->setMessageCode(NET_DATA);
      dataMessage->encapsulate(packet);

      unicast(dataMessage);

      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RPL_CONSTRUCT: /* Construct RPL DODAG */
        {
          this->rpl->rpl_set_root();
          break;
        } /* Construct RPL DODAG*/

        default:
          if (DEBUG)
            std::cout << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
    } /* Command */

    default:
      if (DEBUG)
        std::cout << "Unknown kind" << endl;
      break;
  }
}

void IPv6::processLowerLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      if (DEBUG)
        if (DEBUG)
          std::cout << "RECV (NET)" << endl;

      switch (check_and_cast<IpPacket*>(packet)->getMessageCode())
      {
        case NET_DATA: /* forward data */
        {
          (check_and_cast<Statistic*>(getModuleByPath("^.^.statistic")))->registerStatistic(NET_RECV); // statistics

          if (check_and_cast<IpPacket*>(packet)->getRecverIpAddress() != 0
              && check_and_cast<IpPacket*>(packet)->getRecverIpAddress() != this->getId())
          {
            /* wrong IP address in unicast, drop message or overhear ??? */
            if (DEBUG)
              if (DEBUG)
                std::cout << "Wrong IP message" << endl;
          }
          else
          {
            // Energy calculated by counting bits
            // WSN what if dead while receiving ???
            if (getModuleByPath("^.^")->par("isPollingCount").boolValue())
            {
              check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->receive(
                  check_and_cast<IpPacket*>(packet)->getBitLength());
              check_and_cast<Statistic*>(getModuleByPath("^.^.statistic"))->registerStatisticDelay(DELAY_NET_LAYER,
                  simTime().dbl() - check_and_cast<IpPacket*>(packet)->getTime()); // statistics
            }

            sendMessageToUpper(packet->decapsulate()); // Forward to upper layer
          }

          delete packet;
          break;
        } /* forward data */

        case NET_ICMP_RPL:
          /* RPL ICMP */
        {
          // Energy calculated by counting bits
          if (getModuleByPath("^.^")->par("isPollingCount").boolValue())
            check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->receive(
                check_and_cast<IpPacket*>(packet)->getBitLength());

          this->rpl->processICMP(check_and_cast<IpPacket*>(packet));

          break;
        } /* RPL ICMP */

        default:
          if (DEBUG)
            if (DEBUG)
              std::cout << "Missing resolution" << endl;
          break;
      }
      break;
    } /* Data */

    case RESULT:
      /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case MAC_FINISH_PHASE: /* MAC layer finish a transmitting phase */
        {
          // check buffer
          this->ipPacketQueue.remove(pendingPacket);
          cancelAndDelete(pendingPacket);
          pendingPacket = NULL;

          selfTimer(0, NET_CHECK_BUFFER);
          break;
        }/* MAC layer finish a transmitting phase */

        case MAC_SEND_DEAD_NEIGHBOR: /* dead neighbor handling */
        {
          if (DEBUG)
            std::cout << "NET DEAD NEIGHBOR" << endl;

          // RPL purge default route
          this->rpl->purgeRoute();
          if (DEBUG)
            std::cout << "Purge route" << endl;

          break;
        } /* dead neighbor handling */

        case NET_DIO_SENT: /* just send DIO */
        {
          this->rpl->hasSentDIO();
          break;
        } /* just send DIO*/

        case NET_DIS_SENT: /* just send DIS */
        {
          this->rpl->hasSentDIS();
          break;
        } /* just send DIS*/

        default:
          if (DEBUG)
            std::cout << "Unknown result" << endl;
          break;
      }
      delete packet; // done result
      break;
    } /* Result */

    default:
      if (DEBUG)
        std::cout << "Unknown kind" << endl;
      break;
  }
}

void IPv6::preparePacketToBeSent()
{
  // get first packet from queue
  pendingPacket = check_and_cast<IpPacket*>(this->ipPacketQueue.front());

  if (pendingPacket->getMessageCode() == NET_ICMP_RPL)
  {
    // Energy calculated by counting bits
    if (pendingPacket->getIcmpCode() == NET_ICMP_DIO)
    {
      if (getModuleByPath("^.^")->par("isPollingCount").boolValue())
      {
        if (getModuleByPath("^.^")->par("usingELB").boolValue())
          check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->transmit(pendingPacket->getBitLength() + 8);
        else
          check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->transmit(pendingPacket->getBitLength());
      }
    }
    else if (pendingPacket->getIcmpCode() == NET_ICMP_DIO)
    {
      check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->transmit(pendingPacket->getBitLength());
    }
  }
  else if (pendingPacket->getMessageCode() == NET_DATA)
  {
    // if data, consider parent
    if (this->rpl->rplDag.preferredParent == NULL)
    {
      // if no parent found, wait
      // if (DEBUG)
      std::cout << "NET: no parent found, wait" << endl;
      this->pendingPacket = NULL;
    }
    else
    {
      (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(NET_SEND));

      // Energy calculated by counting bits
      if (getModuleByPath("^.^")->par("isPollingCount").boolValue())
        check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->transmit(pendingPacket->getBitLength());

      // if not, change IP address submit
      pendingPacket->setRecverIpAddress(this->rpl->rplDag.preferredParent->neighborID);

      // WSN hack is neccesary ? /update every round/net-ack
      // this->rpl->updatePrefferredParent();
    }
  }
}

void IPv6::multicast(IpPacket *ipPacket)
{
  /* stops working */
  if (check_and_cast<RadioDriver*>(this->getModuleByPath("^.radio")) == POWER_DOWN)
  {
    delete ipPacket;
    return;
  }

  ipPacket->setKind(DATA);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(0);

  // insert into buffer and check
  if (ipPacket->getMessageCode() == NET_ICMP_RPL)
  {
    // if DIO push back
    if (ipPacket->getIcmpCode() == NET_ICMP_DIO)
      this->ipPacketQueue.push_back(ipPacket);
    // if DIS push front
    else if (ipPacket->getIcmpCode() == NET_ICMP_DIS)
      this->ipPacketQueue.push_front(ipPacket);
  }

  // Check buffer
  selfTimer(0, NET_CHECK_BUFFER);
}

void IPv6::unicast(IpPacket *ipPacket)
{
  /* stops working */
  if (check_and_cast<RadioDriver*>(this->getModuleByPath("^.radio")) == POWER_DOWN)
  {
    delete ipPacket;
    return;
  }

  ipPacket->setTime(simTime().dbl());
  ipPacket->setKind(DATA);
  ipPacket->setSenderIpAddress(this->getId());
  // the recver address will be decided just intime

  // insert into buffers
  this->ipPacketQueue.push_back(ipPacket);

  // Check buffer
  selfTimer(0, NET_CHECK_BUFFER);
}

} /* namespace wsn_energy */
