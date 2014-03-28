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

#include <math.h>

#include "world.h"
#include "statistic.h"
#include "app.h"
#include "ipv6.h"
#include "rpl.h"
#include "battery.h"

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(IPv6);

void IPv6::initialize()
{
  this->rpl = new RPL(this);
}

void IPv6::handleMessage(cMessage *msg)
{
  if (DEBUG)
    ev << "IpMessage type: " << msg->getKind() << endl;

  switch (msg->getKind())
  {
    case RPL_CONSTRUCT: /* Construct RPL DODAG */
      this->rpl->rpl_set_root();
      this->rpl->sendDIO();
      break; /* Construct RPL DODAG*/

    case RPL_SOLICIT: /* Solicit DODAG information*/
      this->rpl->sendDIS(5);
      break; /*Solicit information*/

    case LAYER_APP: /* message from Application layer */
    {
      ((Statistic*) simulation.getModuleByPath("statistic"))->incSensData();

      RPL_neighbor *des = this->rpl->getPrefferedParent();
      if (des != NULL)
      {
        // choosing preferfed parent
        char channelParent[20];
        sprintf(channelParent, "out %d to %d", getParentModule()->getId(), des->neighborID);
        getParentModule()->gate(channelParent)->setDisplayString("ls=yellow,1");

        IpPacket* broadcastMessage = check_and_cast<IpPacket*>(msg);
        broadcastMessage->setType(NET_DATA);
        broadcastMessage->setIsRequestAck(false);

        unicast(broadcastMessage, des->neighborID);
      }
      else
      {
        // WSN dismiss message ?
      }
    }
      break; /* message from Application layer */

    case LAYER_MAC: /* message from MAC layer */
    {
      IpPacket* ipPacket = check_and_cast<IpPacket*>(msg);

      ev << "RECV " << ipPacket->getType() << endl;

      switch (ipPacket->getType())
      {
        case NET_ICMP_DIO: /* receiving DIO */
          this->rpl->receiveDIO((DIO*) ipPacket);
          break; /* receiving DIO */

        case NET_ICMP_DIS: /* receiving DIS */
          this->rpl->receiveDIS((DIS*) ipPacket);
          break; /* receiving DIS */

        case NET_ICMP_ACK: /* WSN update parent list */
          if (DEBUG)
            ev << "Receive Net ACK" << endl;
          this->rpl->updateParent((ACK*) msg);
          break; /* WSN update parent list */

        case NET_DATA: /* forward data */
          // Requesting an ACK from itself
          if (DEBUG)
            ev << "ACK " << ipPacket->getSenderIpAddress() << "/" << this->getParentModule()->getId() << endl;

          // message from it lower self + request sending an ACK
          if (ipPacket->getSenderIpAddress() == this->getParentModule()->getId() && ipPacket->getIsRequestAck())
          {
            if (DEBUG)
              ev << "Net ignite ACK" << endl;

            ACK *ack = new ACK;
            ack->setType(NET_ICMP_ACK);
            ack->setIsRequestAck(false);
            ack->setEnergy(((Battery*) this->getParentModule()->getModuleByPath(".battery"))->energestRemaining);
            unicast(ack, ipPacket->getRecverIpAddress());
          }
          // Fowarding a data
          else
          {
            if (ipPacket->getRecverIpAddress() != 0
                && ipPacket->getRecverIpAddress() != this->getParentModule()->getId())
            {
              // wrong IP address in unicast, drop message
              if (DEBUG)
                ev << "Wrong IP message" << endl;
              delete ipPacket;
              return;
            }

            ev << "Forward Data" << endl;

            // Root
            if (this->getParentModule()->getId() == simulation.getModuleByPath("server")->getId())
            {
              this->getParentModule()->bubble(((Data*) ipPacket)->getValue());
              ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvData();
              // WSN send to application layer
            }
            else
            {
              RPL_neighbor *des = this->rpl->getPrefferedParent();
              if (des != NULL)
              {
                // choosing preferfed parent
                char channelParent[20];
                sprintf(channelParent, "out %d to %d", getParentModule()->getId(), des->neighborID);
                getParentModule()->gate(channelParent)->setDisplayString("ls=yellow,1");

                IpPacket* broadcastMessage = check_and_cast<IpPacket*>(msg);
                broadcastMessage->setType(NET_DATA);
                broadcastMessage->setIsRequestAck(true);

                unicast(broadcastMessage, des->neighborID);
              }
              else
              {
              }
            }
          }
          break; /* forward data */
      }
    }
      break; /* message from MAC layer */
  }
}

void IPv6::finish()
{
  this->buffer.clear();
}

void IPv6::broadcast(IpPacket *ipPacket)
{
  ipPacket->setKind(LAYER_NET);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(0);

  send(ipPacket, gate("lowerOut"));

  // WSN insert to buffer
  this->buffer.push_back(ipPacket);
}

void IPv6::unicast(IpPacket *ipPacket, int recverID)
{
  ipPacket->setKind(LAYER_NET);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(recverID);

  send(ipPacket, gate("lowerOut"));

  // WSN insert to buffer
  this->buffer.push_back(ipPacket);
}

} /* namespace wsn_energy */
