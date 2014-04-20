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
#include "statistic.h"

namespace wsn_energy {

Define_Module(UDP);

void UDP::processSelfMessage(cPacket* packet)
{
}

void UDP::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      (check_and_cast<Statistic*>(getModuleByPath("^.^.statistic"))->registerStatistic(IP_TRANS));

      UdpPacket *udpPacket = new UdpPacket;
      udpPacket->setKind(DATA);
      udpPacket->setSourceIpAddress(getParentModule()->getModuleByPath(".net")->getId());
      udpPacket->setSinkIpAddress(getModuleByPath("^.^.server.net")->getId());

      udpPacket->encapsulate(packet);

      sendMessageToLower(udpPacket);

      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RPL_CONSTRUCT: {
          sendCommand(RPL_CONSTRUCT);
          break;
        }

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

void UDP::processLowerLayerMessage(cPacket* packet)
{
  // Has reached destination
  if (this->getParentModule()->getModuleByPath(".net")->getId()
      == check_and_cast<UdpPacket*>(packet)->getSinkIpAddress())
  {
    ev << "Arrived base station !!!" << endl;
    sendMessageToUpper(packet->decapsulate());

    delete packet;
  }
  // Acts as intermediate node
  else
  {
    (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(IP_INTER));

    sendMessageToLower(packet);
  }
}

} //namespace
