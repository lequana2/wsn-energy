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

#include "nullMAC.h"
#include "packet_m.h"

namespace wsn_energy {

Define_Module(nullMAC);

void nullMAC::deferPacket(FrameMAC* frameMac)
{
  // WSN dismiss + announce failure duty
  IpPacket* ipPacket = new IpPacket;

  ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
  ipPacket->setKind(LAYER_MAC);
  ipPacket->setNote(LAYER_NET_SEND_NOT_OK);
  send(ipPacket, gate("upperOut"));
  return;
}

void nullMAC::sendPacket(FrameMAC* frameMAC)
{
  send(frameMAC, gate("lowerOut"));
}

void nullMAC::receivePacket(FrameMAC* frame)
{
  frame->setKind(LAYER_MAC);
  send(frame, gate("upperOut"));
}

} /* namespace wsn_energy */
