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
//#include "rdc.h"

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef HOP_LIMIT
#define HOP_LIMIT 64
#endif

namespace wsn_energy {

Define_Module(IPv6);

void IPv6::initialize()
{
  this->rpl = new RPL(this);
  this->bufferNET = NULL;
  this->defaultRoute = 0;

  // If server then create RPL DODAG
  if (getParentModule()->getId() == simulation.getModuleByPath("server")->getId())
    this->rpl->rpl_set_root();

//  this->defaultRoute = simulation.getModuleByPath("server.net")->getId();
}

void IPv6::finish()
{
//  if (DEBUG)
  std::cout << "Packet remaining: " << ipPacketQueue.size() << " @ " << getParentModule()->getFullName()
//      << " _ " << check_and_cast<RDCdriver*>(getModuleByPath("^.rdc"))->phase
      << endl;

  // Clear queue !!!
  for (std::list<IpPacketInterface*>::iterator it = this->ipPacketQueue.begin(); it != this->ipPacketQueue.end(); it++)
    delete *it;

  this->ipPacketQueue.clear();

  // clear RPL
  this->rpl->finish();
}

void IPv6::processSelfMessage(cPacket* packet)
{
  // if power down, does not put into queue
  if (check_and_cast<RadioDriver*>(this->getModuleByPath("^.radio")) == POWER_DOWN)
  {
    delete packet;
    return;
  }

  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case NET_CHECK_BUFFER: /* Check buffer */
        {
          if (ipPacketQueue.size() == 0) // successful send all packet in queue
          {
          }
          else if (bufferNET != NULL) // have any pending packet
          {
          }
          else
          {
            // prepare a packet to be sent
            preparePacketToBeSent();

            // send duplicated packet to MAC layer
            sendMessageToLower(bufferNET->dup());
          }

          delete packet; // done command

          break;
        } /* Check buffer */

        case NET_TIMER_DIO: /* DIO timer*/
        {
          if (this->rpl->rplDag.joined)
            this->rpl->handleDIOTimer();

          break;
        } /* DIO timer*/

        case NET_TIMER_DIS: /* Solicit DODAG information*/
        {
          if (!this->rpl->rplDag.joined)
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
      delete packet;
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
      unicast(check_and_cast<UdpPacketInterface*>(packet));

      break;
    } /* Data */

    default:
      delete packet;
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
        std::cout << "NET: received" << endl;

      if (getModuleByPath("^.^")->par("usingHDC").boolValue())
      {
        // WSN compress using HC01
      }
      else
      {
        switch (check_and_cast<IpPacketStandard*>(packet)->getNextHeader())
        {
          case NEXT_HEADER_UDP: /* UDP */
          {
            (check_and_cast<Statistic*>(getModuleByPath("^.^.statistic")))->registerStatistic(NET_RECV); // statistics

            // Energy calculated by counting bits
            // what if dead while receiving <- nonsense due to critical level
            if (getModuleByPath("^.^")->par("isPollingCount").boolValue())
            {
              check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->receive(
                  check_and_cast<IpPacketStandard*>(packet)->getBitLength());
              check_and_cast<Statistic*>(getModuleByPath("^.^.statistic"))->registerStatisticDelay(DELAY_NET_LAYER,
                  simTime().dbl() - check_and_cast<IpPacketStandard*>(packet)->getTime()); // statistics
            }

            if (check_and_cast<IpPacketStandard*>(packet)->getDestinationIpAddress() != 0
                && check_and_cast<IpPacketStandard*>(packet)->getDestinationIpAddress() != this->getId())
            {
              // hop limit !!!
              if (check_and_cast<IpPacketStandard*>(packet)->getHopLimit() == 1)
              {
                delete packet;
              }
              else
              {
                check_and_cast<IpPacketStandard*>(packet)->setHopLimit(
                    check_and_cast<IpPacketStandard*>(packet)->getHopLimit() - 1);

                // wrong IP address in unicast, keep forwarding using default route !!!
                putIntoQueue(check_and_cast<IpPacketStandard*>(packet));
              }
            }
            else
            {
              // arrive right IP destination
              sendMessageToUpper(packet->decapsulate()); // Forward to upper layer

              delete packet;
            }
            break;
          } /* UDP */

          case NEXT_HEADER_ICMP: /* ICMP */
          {
            // Energy calculated by counting bits
            if (getModuleByPath("^.^")->par("isPollingCount").boolValue())
              check_and_cast<Count*>(getParentModule()->getSubmodule("count"))->receive(
                  check_and_cast<IpPacketStandard*>(packet)->getBitLength());

            IcmpPacket* icmpPacket = check_and_cast<IcmpPacket*>(packet->decapsulate());
            delete packet;

            if (icmpPacket->getType() == ICMP_RPL)
              this->rpl->processICMP(icmpPacket);

            break;
          } /* ICMP */

          default:
            delete packet;
            if (DEBUG)
              std::cout << "Missing resolution" << endl;
            break;
        }
      }

      break;
    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case MAC_FINISH_PHASE: /* MAC layer finish a transmitting phase */
        {
          // Consider has sent ICMP or not !!!
          if (getModuleByPath("^.^")->par("usingHDC").boolValue())
          {
            // WSN compress using HC01
          }
          else
          {
            if (check_and_cast<IpPacketStandard*>(bufferNET)->getNextHeader() == NEXT_HEADER_ICMP)
            {
              if (check_and_cast<IcmpPacket*>(bufferNET->getEncapsulatedPacket())->getType() == ICMP_RPL)
              {
                if (check_and_cast<IcmpPacket*>(bufferNET->getEncapsulatedPacket())->getCode() == RPL_DIO_CODE)
                  this->rpl->hasSentDIO();
                else if (check_and_cast<IcmpPacket*>(bufferNET->getEncapsulatedPacket())->getCode() == RPL_DIS_CODE)
                  this->rpl->hasSentDIS();
              }
            }
          }

          // remove pending packet from buffer
          this->ipPacketQueue.remove(bufferNET);

          if (bufferNET != NULL)
          {
            delete bufferNET;
            bufferNET = NULL;
          }

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

        case MAC_RELIABLE: /* resend */
        {
          putIntoQueue(bufferNET->dup());
          break;
        } /* resend */

        default:
          if (DEBUG)
            std::cout << "Unknown result" << endl;
          break;
      }

      delete packet; // done result
      break;
    } /* Result */

    default:
      delete packet;
      if (DEBUG)
        std::cout << "Unknown kind" << endl;
      break;
  }
}

void IPv6::preparePacketToBeSent()
{
  // get first packet from queue
  bufferNET = check_and_cast<IpPacketInterface*>(this->ipPacketQueue.front());

  if (getModuleByPath("^.^")->par("usingHDC").boolValue())
  {
    // WSN compress using HC01
  }
  else
  {
    // statistics
    if (check_and_cast<IpPacketStandard*>(bufferNET)->getNextHeader() == NEXT_HEADER_UDP)
      (check_and_cast<Statistic*>(getModuleByPath("^.^.statistic")))->registerStatistic(NET_SEND);
  }
}

void IPv6::putIntoQueue(IpPacketInterface* ipPacket)
{
  // insert into buffer
  this->ipPacketQueue.push_back(ipPacket);

  // check buffer
  selfTimer(0, NET_CHECK_BUFFER);
}

void IPv6::multicast(IcmpPacket *icmpPacket)
{
  // create interface
  IpPacketInterface *ipPacket;

  if (getModuleByPath("^.^")->par("usingHDC").boolValue())
  {
    // WSN compress using HC01
  }
  else
  {
    // initialisation
    ipPacket = new IpPacketStandard;
    ipPacket->setKind(DATA);
    ipPacket->setByteLength(ipPacket->getHeaderLength());

    (check_and_cast<IpPacketStandard*>(ipPacket))->setNextHeader(NEXT_HEADER_ICMP);
    (check_and_cast<IpPacketStandard*>(ipPacket))->setHopLimit(HOP_LIMIT);
    (check_and_cast<IpPacketStandard*>(ipPacket))->setSourceIpAddress(this->getId());
    (check_and_cast<IpPacketStandard*>(ipPacket))->setDestinationIpAddress(0);
  }

  ipPacket->encapsulate(icmpPacket);

  putIntoQueue(ipPacket);
}

void IPv6::unicast(UdpPacketInterface *udpPacket)
{
  // create interface
  IpPacketInterface *ipPacket;

  if (getModuleByPath("^.^")->par("usingHDC").boolValue())
  {
    // WSN compress using HC01
  }
  else
  {
    // initialisation
    ipPacket = new IpPacketStandard;
    ipPacket->setKind(DATA);
    ipPacket->setByteLength(ipPacket->getHeaderLength());

    (check_and_cast<IpPacketStandard*>(ipPacket))->setNextHeader(NEXT_HEADER_UDP);
    (check_and_cast<IpPacketStandard*>(ipPacket))->setHopLimit(HOP_LIMIT);
    (check_and_cast<IpPacketStandard*>(ipPacket))->setSourceIpAddress(this->getId());
    (check_and_cast<IpPacketStandard*>(ipPacket))->setDestinationIpAddress(
        (check_and_cast<Data*>(udpPacket->getEncapsulatedPacket()))->getDestinationIPAddress());
  }

  ipPacket->encapsulate(udpPacket);

  putIntoQueue(ipPacket);
}

} /* namespace wsn_energy */
