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

#include "udp.h"

namespace wsn_energy {

Define_Module(UDP);

void UDP::processSelfMessage(cPacket* packet)
{
}

void UDP::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* command */
    {
      UdpPacket *udpPacket = new UdpPacket;

      udpPacket->setKind(COMMAND);
      udpPacket->setNote(check_and_cast<Data*>(packet)->getNote());
      sendMessageToLower(udpPacket);

      delete packet;
    }
      break; /* command */

    case DATA: /* data */
    {
      UdpPacket *udpPacket = new UdpPacket;

      udpPacket->setKind(DATA);
      udpPacket->encapsulate(packet);
      udpPacket->setSourceIpAddress(getParentModule()->getModuleByPath(".net")->getId());
      udpPacket->setSinkIpAddress(simulation.getModuleByPath("server.net")->getId());

      sendMessageToLower(udpPacket);
    }
      break; /* data */
  }
}

void UDP::processLowerLayerMessage(cPacket* packet)
{
  // is destination reached ?
  if (this->getParentModule()->getModuleByPath(".net")->getId()
      == check_and_cast<UdpPacket*>(packet)->getSinkIpAddress())
  {
    ev << "Arrived base station !!!" << endl;
    sendMessageToUpper(packet->decapsulate());

    delete packet;
  }
  // Forwarding data
  else
  {
    sendMessageToLower(packet);
  }
}

} //namespace
