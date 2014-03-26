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

void nullMAC::sendPacket(cMessage* msg)
{
  Frame *frame = (Frame*) msg;

  frame->setKind(LAYER_MAC);
  frame->setLen(frame->getLen() + MAC_HEADER_FOOTER_LEN);
  frame->setSenderMacAddress(this->getId());
  frame->setRecverMacAddress(getModuleByPath("server.mac")->getId());

  send(frame, gate("lowerOut"));
}

void nullMAC::receivePacket(cMessage* msg)
{
  msg->setKind(LAYER_MAC);
  send(msg, gate("upperOut"));
}

} /* namespace wsn_energy */
