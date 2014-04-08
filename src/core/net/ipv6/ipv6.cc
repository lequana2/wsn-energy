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
#define ANNOTATE 1
#endif

namespace wsn_energy {

Define_Module(IPv6);

void IPv6::initialize()
{
  this->rpl = new RPL(this);
  needWaiting = false;
}

void IPv6::finish()
{
  this->rpl = NULL;
}

void IPv6::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Control message */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case LAYER_NET_CHECK_BUFFER:
          /* Check is in turn */
        {
          if (DEBUG)
            ev << "Queue size " << this->buffer.size() << endl;

          if (this->buffer.size() == 0) // empty
          {
            needWaiting = false;
          }
          else if (!needWaiting) // In-turn
          {
            sendMessageToLower(this->buffer.front());
            needWaiting = true;
          }
          delete packet;
        }
          break; /* Check is in turn */

        default: {
          if (DEBUG)
            ev << "Missing resolution" << endl;
        }
          break;
      }
      break;
      /* Control message */
    }

    default:
      if (DEBUG)
        ev << "Missing resolution" << endl;
      break;
  }
}

void IPv6::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* command from upper layer */
    {
      switch (check_and_cast<UdpPacket*>(packet)->getNote())
      {
        case RPL_CONSTRUCT:
          /* Construct RPL DODAG */
          this->rpl->rpl_set_root();
          this->rpl->sendDIO();
          delete packet;
          break; /* Construct RPL DODAG*/

        case RPL_SOLICIT:
          /* Solicit DODAG information*/
          this->rpl->sendDIS(5);
          delete packet;
          break; /*Solicit information*/
      }
    }
      break; /* command from upper layer */

    case DATA: /* message from upper layer */
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

        dataMessage->encapsulate(packet);
        dataMessage->setType(NET_DATA);

        unicast(dataMessage, this->rpl->rplDag.preferredParent->neighborID);
      }
      // WSN Trigger local/global repair
      else
      {
      }
    }
      break; /* message from upper layer */

    default:
      if (DEBUG)
        ev << "Missing resolution" << endl;
      break;
  }
}

void IPv6::processLowerLayerMessage(cPacket* packet)
{
  /* message from MAC layer */
  switch (check_and_cast<IpPacket*>(packet)->getNote())
  {
    case LAYER_MAC_SEND_OK: /* ending transmitting phase, success */
    {
      if (DEBUG)
        ev << "Success NET trans" << endl;

      delete packet;
//      delete buffer.front();
      this->buffer.pop_front();
      needWaiting = false;

      Command *check = new Command;
      check->setKind(COMMAND);
      check->setNote(LAYER_NET_CHECK_BUFFER);
      scheduleAt(simTime(), check);
    }
      break; /* ending transmitting phase */

    case LAYER_NET_SEND_NOT_OK: /* WSN ending transmitting phase, failure */
    {
      if (DEBUG)
        ev << "Failure NET trans" << endl;

      delete packet;
      //      delete buffer.front();
      this->buffer.pop_front();
      needWaiting = false;

      Command *check = new Command;
      check->setKind(COMMAND);
      check->setNote(LAYER_NET_CHECK_BUFFER);
      scheduleAt(simTime(), check);
    }
      break; /* ending transmitting phase */

    case LAYER_MAC_SEND_ERR: /* WSN ending transmitting phase, internal error */
    {
      if (DEBUG)
        ev << "Failure NET trans" << endl;

      delete packet;
//      delete buffer.front();
      this->buffer.pop_front();
      needWaiting = false;

      Command *check = new Command;
      check->setKind(COMMAND);
      check->setNote(LAYER_NET_CHECK_BUFFER);
      scheduleAt(simTime(), check);
    }
      break; /* ending transmitting phase */

    case LAYER_NET_RECV_OK: /* input */
    {
      switch (check_and_cast<IpPacket*>(packet)->getType())
      {
        case NET_ICMP_DIO: /* receiving DIO */
        {
          this->rpl->processDIO(check_and_cast<DIO*>(packet));
          delete packet;
        }
          break; /* receiving DIO */

        case NET_ICMP_DIS:/* receiving DIS */
        {
          this->rpl->processDIS(check_and_cast<DIS*>(packet));
          delete packet;
        }
          break; /* receiving DIS */

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
            /* Forward to upper layer */
            sendMessageToUpper(packet->decapsulate());
          }
          delete packet;
        }
          break; /* forward data */

        default:
          if (DEBUG)
            ev << "Missing resolution" << endl;
          break;
      }
    }
      break; /* input */

    default:
      if (DEBUG)
        ev << "Missing resolution" << endl;
      break;
  }/* message from MAC layer */
}

void IPv6::multicast(IpPacket *ipPacket)
{
  ipPacket->setKind(DATA);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(0);

  this->buffer.push_back(ipPacket);

  Command *check = new Command;
  check->setKind(COMMAND);
  check->setNote(LAYER_NET_CHECK_BUFFER);
  scheduleAt(simTime(), check);
}

void IPv6::unicast(IpPacket *ipPacket, int recverIpAddress)
{
  ipPacket->setKind(DATA);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(recverIpAddress);

  this->buffer.push_back(ipPacket);

  Command *check = new Command;
  check->setKind(COMMAND);
  check->setNote(LAYER_NET_CHECK_BUFFER);
  scheduleAt(simTime(), check);
}

} /* namespace wsn_energy */
