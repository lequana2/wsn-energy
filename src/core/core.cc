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
#include "core.h"
#include "rpl.h"
#include "radio.h"

namespace wsn_energy {

Define_Module(Core);

Core::Core()
{
}
Core::~Core()
{
}

//---------------------------------------------------------------------------//
void Core::initialize()
{
  this->rpl = new RPL(this);

  if (this->getId() == simulation.getModuleByPath("server.core")->getId())
    this->rpl->rpl_set_root();
}
//---------------------------------------------------------------------------//
void Core::handleMessage(cMessage *msg)
{
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
  // IP messeage
  else if (msg->getKind() == WORKING_FLAG)
  {
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
    }
  }
  // WSN Enviroment message
}

void Core::finish()
{
}

//---------------------------------------------------------------------------//
void Core::broadcast(IpPacket *msg)
{
  msg->setKind(TRX_BROADCAST);

  send(msg, gate("radioOut"));
}

} /* namespace wsn_energy */
