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

#include <rdc.h>
#include "packet_m.h"

namespace wsn_energy {

Define_Module(Rdc);

Rdc::Rdc()
{
  // TODO Auto-generated constructor stub

}

Rdc::~Rdc()
{
  // TODO Auto-generated destructor stub
}

void Rdc::initialize()
{
}

void Rdc::handleMessage(cMessage *msg)
{
  Frame *frame = (Frame*) msg;
  if (msg->getSenderModule()->getId() == getParentModule()->getModuleByPath(".mac")->getId())
  {
    msg->setKind(TRX_BROADCAST);
    send(msg, gate("lowerOut"));
  }
  else
  {
    send(frame, gate("upperOut"));
  }
}

void Rdc::finish()
{
}

} /* namespace wsn_energy */
