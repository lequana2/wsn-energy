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

#include <stdio.h>

#include "client.h"
#include "packet_m.h"

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  App::initialize();

  // WSN Client scheme
  cMessage *event = new cMessage;
  event->setKind(RPL_SOLICIT);

//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[4]")->getId())
//    send(event, gate("appOut"));

  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[35]")->getId())
    scheduleAt(simTime() + 20, event);

  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[45]")->getId())
    scheduleAt(simTime() + 30, event);
}

void Client::handleMessage(cMessage *msg)
{
  if (msg->getKind() == RPL_SOLICIT)
  {
    send(msg, gate("appOut"));
  }
}

void Client::finish()
{
}

}
;
// namespace

