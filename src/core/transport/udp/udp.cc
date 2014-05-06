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

#ifndef DEBUG
#define DEBUG 0
#endif

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
      /* statistics */
      (check_and_cast<Statistic*>(getModuleByPath("^.^.statistic"))->registerStatistic(IP_TRANS));

      /* Initialisation */
      UdpPacket *udpPacket = new UdpPacket;
      udpPacket->setKind(DATA);

      // set up port
      udpPacket->setSourcePort(UDP_CLIENT_PORT);
      udpPacket->setDestinationPort((check_and_cast<Data*>(packet))->getDestinationPort());

      // length (in-line pseudo-header)
      // checksum (in-line pseudo-header)

      // encapsulate data
      udpPacket->encapsulate(packet);

      sendMessageToLower(udpPacket);

      break;
    } /* Data */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void UDP::processLowerLayerMessage(cPacket* packet)
{
  int packetDestinationPort = (check_and_cast<UdpPacket*>(packet))->getDestinationPort();

  // Has reached approciate port
  if (packetDestinationPort == UDP_SERVER_PORT)
  {
    if (DEBUG)
      ev << "Arrived base station !!!" << endl;

    sendMessageToUpper(packet->decapsulate());
  }
  else
  {
    // Drop
  }

  delete packet;
}

} //namespace
