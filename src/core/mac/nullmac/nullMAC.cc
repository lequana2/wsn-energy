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

nullMAC::nullMAC()
{
  // TODO Auto-generated constructor stub

}

nullMAC::~nullMAC()
{
  // TODO Auto-generated destructor stub
}

void nullMAC::initialize()
{
}

void nullMAC::handleMessage(cMessage *msg)
{
  Frame *frame = (Frame*) msg;
  if (msg->getSenderModule()->getId() == getParentModule()->getModuleByPath(".net")->getId())
  {
    frame->setSenderMacAddress(this->getId());
    frame->setRecverMacAddress(getModuleByPath("server.mac")->getId());

    send(msg, gate("lowerOut"));
  }
  else
  {
    send(frame, gate("upperOut"));
  }
}

void nullMAC::finish()
{
}

} /* namespace wsn_energy */
