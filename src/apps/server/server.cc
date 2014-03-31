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

#include "server.h"

#include "statistic.h"
#include "packet_m.h"

namespace wsn_energy {

Define_Module(Server);

void Server::initialize()
{
  App::initialize();

  cMessage *msg = new cMessage;
  msg->setKind(RPL_CONSTRUCT);
  scheduleAt(simTime(), msg);
}

void Server::handleMessage(cMessage *msg)
{
  switch (msg->getKind())
  {
    case RPL_CONSTRUCT:
      send(msg, gate("lowerOut"));
      break;

    case LAYER_APP:
      Data* data = check_and_cast<Data*>(msg);
      this->getParentModule()->bubble(data->getValue());

      /* End to end statistics */
      ((Statistic*) simulation.getModuleByPath("statistic"))->packetRateTracking(APP_RECV);
      ((Statistic*) simulation.getModuleByPath("statistic"))->packetDelayTracking(simTime().dbl() - data->getTime());
      break;
  }
}

void Server::finish()
{
}

}
;
// namespace
