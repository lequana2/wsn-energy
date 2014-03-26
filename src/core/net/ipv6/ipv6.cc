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

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(IPv6);

void IPv6::initialize()
{
  this->rpl = new RPL(this);

  // Server starts forming RPL construct
  if (this->getId() == simulation.getModuleByPath("server.net")->getId())
    this->rpl->rpl_set_root();
}

void IPv6::handleMessage(cMessage *msg)
{
  ev << "Message type: " << msg->getKind() << endl;

  switch (msg->getKind())
  {
    case RPL_CONSTRUCT: /* Construct RPL DODAG */
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

        IpPacket* broadcastMessage = (IpPacket*) msg;
        broadcastMessage->setRecverIpAddress(des->neighborID);
        broadcastMessage->setTypeNetLayer(NET_DATA);
        broadcastMessage->setRecverIpAddress(des->neighborID);

        broadcast(broadcastMessage);

        this->rpl->switchParent();

        // WSN remove
        this->rpl->rplDag.parentList.remove(des);
      }
      else
      {
        // WSN dismiss message ?
      }
    }
      break; /* message from Application layer */

    case LAYER_MAC: /* message from MAC layer */
      // receive RPL DODAG information
      if (((IpPacket*) msg)->getTypeNetLayer() == NET_ICMP_DIO)
      {
        this->rpl->receiveDIO((DIO*) msg);
      }

      // receive RPL DODAG solicitation
      else if (((IpPacket*) msg)->getTypeNetLayer() == NET_ICMP_DIS)
      {
        this->rpl->receiveDIS((DIS*) msg);
      }

      //WSN forward data
      else if (((IpPacket*) msg)->getTypeNetLayer() == NET_DATA)
      {
        if (((IpPacket*) msg)->getRecverIpAddress() != this->getParentModule()->getId())
          return;

        ev << "Forward DATA" << endl;

        // Root
        int value = ((Data*) msg)->getValue();
        char m[20];
        sprintf(m, "%d", value);

        if (this->getParentModule()->getId() == simulation.getModuleByPath("server")->getId())
        {
          this->getParentModule()->bubble(m);
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

            IpPacket* broadcastMessage = (IpPacket*) msg;
            broadcastMessage->setKind(APP_SENSING_FLAG);
            broadcastMessage->setRecverIpAddress(des->neighborID);
            broadcastMessage->setTypeNetLayer(NET_DATA);

            broadcast(broadcastMessage);

            this->rpl->switchParent();
          }
          else
          {
            // WSN dismiss message ?
          }
        }
      }
      break; /* message from MAC layer */
  }
}

void IPv6::finish()
{
}

//---------------------------------------------------------------------------//
void IPv6::broadcast(IpPacket *msg)
{
  msg->setSenderIpAddress(this->getId());
//  msg->setRecverIpAddress(getModuleByPath("server.net")->getId());
  msg->setKind(LAYER_NET);

  send(msg, gate("lowerOut"));
}

} /* namespace wsn_energy */
