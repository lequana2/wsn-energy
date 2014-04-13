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

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef ANNOTATE
#define ANNOTATE 0
#endif

namespace wsn_energy {

Define_Module(IPv6);

void IPv6::initialize()
{
  this->rpl = new RPL(this);
}

void IPv6::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case NET_TIMER_DIO: /* DIO timer*/
        {
          this->rpl->handleDIOTimer();
          break;
        } /* DIO timer*/

          //        case RPL_SOLICIT: /* WSN Solicit DODAG information*/
          //        {
          //          this->rpl->sendDIS(5);
          //          break;
          //        } /*Solicit information*/

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
    } /* Command */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void IPv6::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      /* Still have parent */
      if (this->rpl->rplDag.preferredParent != NULL)
      {
        if (ANNOTATE)
        {
          char channelParent[20];
          sprintf(channelParent, "out %d to %d", getParentModule()->getId(),
              (simulation.getModule(this->rpl->rplDag.preferredParent->neighborID))->getParentModule()->getId());
          getParentModule()->gate(channelParent)->setDisplayString("ls=purple,1");
        }

        IpPacket *dataMessage = new IpPacket;
        dataMessage->setMessageCode(NET_DATA);

        dataMessage->encapsulate(packet);

        unicast(dataMessage, this->rpl->rplDag.preferredParent->neighborID);
      }
      else
      {
        // WSN Trigger local/global repair

        delete packet;
      }
      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RPL_CONSTRUCT: /* Construct RPL DODAG */
        {
          this->rpl->rpl_set_root();
          this->rpl->sendDIO();
          break;
        } /* Construct RPL DODAG*/

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
    } /* Command */

    case RESULT:
      /* Result */
    {
      delete packet;
      break;
    } /* Result */

    default:
      ev << "Unknown kind" << endl;
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
        ev << "RECV (NET)" << endl;

      (check_and_cast<Statistic*>(getModuleByPath("WSN.statistic")))->packetRateTracking(NET_RECV); // statistics

      switch (check_and_cast<IpPacket*>(packet)->getMessageCode())
      {
        case NET_DATA: /* forward data */
        {
          if (check_and_cast<IpPacket*>(packet)->getRecverIpAddress() != 0
              && check_and_cast<IpPacket*>(packet)->getRecverIpAddress() != this->getId())
          {
            /* wrong IP address in unicast, drop message */
            if (DEBUG)
              ev << "Wrong IP message" << endl;
          }
          else
          {
            sendMessageToUpper(packet->decapsulate()); // Forward to upper layer
          }
          delete packet;
          break;
        } /* forward data */

        case NET_ICMP_RPL: /* ICMP */
        {
          this->rpl->processICMP(check_and_cast<IpPacket*>(packet));
          break;
        } /* ICMP */

        default:
          if (DEBUG)
            ev << "Missing resolution" << endl;
          break;
      }
      break;
    } /* Data */

    case RESULT:
      /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case MAC_SEND_DEAD_NEIGHBOR: /* WSN ending transmitting phase, no ack, purge route */
        {
          if (DEBUG)
            ev << "NET TRANS FAILED" << endl;
        }
          break; /* ending transmitting phase */

        default:
          ev << "Unknown result" << endl;
          break;
      }
      delete packet; // done result
      break;
    } /* Result */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void IPv6::multicast(IpPacket *ipPacket)
{
  ipPacket->setKind(DATA);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(0);

  sendMessageToLower(ipPacket);

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->packetRateTracking(NET_SEND));
}

void IPv6::unicast(IpPacket *ipPacket, int recverIpAddress)
{
  ipPacket->setKind(DATA);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(recverIpAddress);

  sendMessageToLower(ipPacket);

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->packetRateTracking(NET_SEND));
}

} /* namespace wsn_energy */
