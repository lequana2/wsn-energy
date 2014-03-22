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

#include "nullRDC.h"
#include "packet_m.h"

#ifndef  DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(nullRDC);

nullRDC::nullRDC()
{
  // TODO Auto-generated constructor stub

}

nullRDC::~nullRDC()
{
  // TODO Auto-generated destructor stub
}

void nullRDC::initialize()
{
}

void nullRDC::handleMessage(cMessage *msg)
{
  Frame *frame = (Frame*) msg;
  if (msg->getSenderModule()->getId() == getParentModule()->getModuleByPath(".mac")->getId())
  {
    msg->setKind(TRX_BROADCAST);
    send(msg, gate("lowerOut"));
  }
  else
  {
    if (((Raw*) msg)->getBitError())
    {
      send(frame, gate("upperOut"));
    }
    else
    {
      if(DEBUG)
        ev << "Collision message" << endl;
    }
  }
}

void nullRDC::finish()
{
}

} /* namespace wsn_energy */
