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

    case LAYER_NET: /* Control message */
    {
      switch (check_and_cast<IpPacket*>(msg)->getNote())
      {
        case LAYER_NET_CHECK_BUFFER:
          ev << "Queue size " << this->buffer.size() << endl;
          if (this->buffer.size() == 1) // In-turn
            send(this->buffer.front(), gate("lowerOut"));
          break;
      }
    }
      break; /* Control message */

    case LAYER_APP: /* message from Application layer */
    {
      // Still have parent
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

        dataMessage->encapsulate(check_and_cast<IpPacket*>(msg));

        dataMessage->setType(NET_DATA);
        dataMessage->setSourceIpAddress(this->getId());
        dataMessage->setSinkIpAddress(simulation.getModuleByPath("server.net")->getId());

        unicast(dataMessage, this->rpl->rplDag.preferredParent->neighborID);
      }
      // WSN Trigger repair
      else
      {
      }
    }
      break; /* message from Application layer */

    case LAYER_MAC: /* message from MAC layer */
    {
      IpPacket* ipPacket = check_and_cast<IpPacket*>(msg);

      ev << "Net-layer, mac type: " << ipPacket->getType() << endl;

      switch (ipPacket->getNote())
      {
        case LAYER_NET_SEND_OK: /* ending transmitting phase */
          if (DEBUG)
            ev << "Success NET trans" << endl;
          this->buffer.pop_front();
          ipPacket->setKind(LAYER_NET);
          ipPacket->setNote(LAYER_NET_CHECK_BUFFER);
          scheduleAt(simTime(), ipPacket);
          break; /* ending transmitting phase */

        case LAYER_NET_SEND_NOT_OK: /* ending transmitting phase */
          if (DEBUG)
            ev << "Failure NET trans" << endl;
          this->buffer.pop_front();
          ipPacket->setKind(LAYER_NET);
          ipPacket->setNote(LAYER_NET_CHECK_BUFFER);
          scheduleAt(simTime(), ipPacket);
          break; /* ending transmitting phase */

        case LAYER_NET_RECV_OK: {
          switch (ipPacket->getType())
          {
            case NET_ICMP_DIO:
              /* receiving DIO */
              this->rpl->receiveDIO((DIO*) ipPacket);
              break; /* receiving DIO */

            case NET_ICMP_DIS:
              /* receiving DIS */
              this->rpl->receiveDIS((DIS*) ipPacket);
              break; /* receiving DIS */

            case NET_DATA:
              /* forward data */
              if (DEBUG)
                ev << "Get Data packet" << endl;

              if (ipPacket->getRecverIpAddress() != 0 && ipPacket->getRecverIpAddress() != this->getId())
              {
                // wrong IP address in unicast, drop message
                if (DEBUG)
                  ev << "Wrong IP message" << endl;

                delete ipPacket;

                return;
              }

              // Coming to destination
              if (this->getId() == ipPacket->getSinkIpAddress())
              {
                ev << "received" << endl;
                send(check_and_cast<Data*>(ipPacket->decapsulate()), gate("upperOut"));

                delete ipPacket;
              }
              // Forwarding data
              else
              {
                if (this->rpl->rplDag.preferredParent != NULL)
                {
                  if (ANNOTATE)
                  {
                    char channelParent[20];
                    sprintf(channelParent, "out %d to %d", getParentModule()->getId(),
                        (simulation.getModule(this->rpl->rplDag.preferredParent->neighborID))->getParentModule()->getId());
                    getParentModule()->gate(channelParent)->setDisplayString("ls=purple,1");
                  }

                  IpPacket* broadcastMessage = check_and_cast<IpPacket*>(msg);
                  broadcastMessage->setType(NET_DATA);
                  broadcastMessage->setIsRequestAck(true);

                  unicast(broadcastMessage, this->rpl->rplDag.preferredParent->neighborID);
                }
                else
                {
                }
              }
              break; /* forward data */
          }
        }
      }
    }
      break; /* message from MAC layer */
  }
}

void IPv6::finish()
{
  this->buffer.clear();
}

void IPv6::multicast(IpPacket *ipPacket)
{
  ipPacket->setKind(LAYER_NET);
  ipPacket->setNote(LAYER_NET_CHECK_BUFFER);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(0);

  this->buffer.push_back(ipPacket);
  scheduleAt(simTime(), ipPacket);
}

void IPv6::unicast(IpPacket *ipPacket, int recverIpAddress)
{
  ipPacket->setKind(LAYER_NET);
  ipPacket->setNote(LAYER_NET_CHECK_BUFFER);
  ipPacket->setSenderIpAddress(this->getId());
  ipPacket->setRecverIpAddress(recverIpAddress);

  this->buffer.push_back(ipPacket);
  scheduleAt(simTime(), ipPacket);
}

} /* namespace wsn_energy */
