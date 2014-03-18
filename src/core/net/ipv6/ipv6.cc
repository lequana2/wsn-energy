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

namespace wsn_energy {

Define_Module(IPv6);

IPv6::IPv6()
{
}
IPv6::~IPv6()
{
}

//---------------------------------------------------------------------------//
void IPv6::initialize()
{
  this->rpl = new RPL(this);

  if (this->getId() == simulation.getModuleByPath("server.net")->getId())
    this->rpl->rpl_set_root();
}
//---------------------------------------------------------------------------//
void IPv6::handleMessage(cMessage *msg)
{
  ev << msg->getKind() << endl;

  // dispatch event
  if (msg->getKind() == RPL_CONSTRUCT)
  {
    this->rpl->sendDIO();
    return;
  }
  else if (msg->getKind() == RPL_SOLICIT)
  {
    this->rpl->sendDIS(5);
    return;
  }
  // Enviroment flag
  else if (msg->getKind() == ENVIRON_FLAG)
  {
    ((Statistic*) simulation.getModuleByPath("statistic"))->incSensData();

    RPL_neighbor *des = this->rpl->getPrefferedParent();
    if (des != NULL)
    {
      // choosing preferfed parent
      char channelParent[20];
      sprintf(channelParent, "out %d to %d", getParentModule()->getId(), des->neighborID);
      getParentModule()->gate(channelParent)->setDisplayString("ls=purple,1");

      IpPacket* broadcastMessage = (IpPacket*) msg;
      broadcastMessage->setRecverIpAddress(des->neighborID);
      broadcastMessage->setType(IP_DATA);

      broadcast(broadcastMessage);

      // WSN remove
      this->rpl->rplDag.parentList.remove(des);
    }
    else
    {
      // WSN dismiss message ?
    }
  }
  // IP messeage
  else if (msg->getKind() == WORKING_FLAG)
  {
    // WSN dismiss if recvID is not the same
//    if (((IpPacket*) msg)->getRecverIpAddress() != 0
//        && ((IpPacket*) msg)->getRecverIpAddress() != this->getParentModule()->getId())
//      return;

    // receive RPL construct
    if (((IpPacket*) msg)->getType() == IP_ICMP)
    {
      switch (((ICMP*) msg)->getIcmp_code())
      {
        case ICMP_DIO_CODE:
          this->rpl->receiveDIO((DIO*) msg);
          break;
        case ICMP_DIS_CODE:
          this->rpl->receiveDIS((DIS*) msg);
          break;
      }
    }
    //WSN forward data
    else if (((IpPacket*) msg)->getType() == IP_DATA)
    {
      if (((IpPacket*) msg)->getRecverIpAddress() != this->getParentModule()->getId())
        return;

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
          getParentModule()->gate(channelParent)->setDisplayString("ls=purple,1");

          IpPacket* broadcastMessage = (IpPacket*) msg;
          broadcastMessage->setRecverIpAddress(des->neighborID);
          broadcastMessage->setType(IP_DATA);

          broadcast(broadcastMessage);
        }
        else
        {
          // WSN dismiss message ?
        }
      }
    }
  }
  // WSN Enviroment message
}

void IPv6::finish()
{
}

//---------------------------------------------------------------------------//
void IPv6::broadcast(IpPacket *msg)
{
  msg->setSenderIpAddress(this->getId());
  msg->setRecverIpAddress(getModuleByPath("server.net")->getId());

  send(msg, gate("lowerOut"));
}

} /* namespace wsn_energy */
