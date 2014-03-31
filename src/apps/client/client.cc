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

#include "statistic.h"
#include "client.h"
#include "packet_m.h"

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  App::initialize();

  // WSN Client scheme
  cMessage *event = new cMessage;
  event->setKind(APP_SENSING_FLAG);

  /* Contiki test scheme */
  newData();
//  scheduleAt(simTime() + 3600, event->dup());

//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[79]")->getId())
//    scheduleAt(simTime() + 1, event->dup());
//
//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[79]")->getId())
//    scheduleAt(simTime() + 2, event->dup());
//
//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[79]")->getId())
//    scheduleAt(simTime() + 3, event->dup());

//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
//    scheduleAt(simTime() + 1, event->dup());
//
//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
//    scheduleAt(simTime() + 2, event->dup());
//
//  if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
//    scheduleAt(simTime() + 3, event->dup());
}

void Client::handleMessage(cMessage *msg)
{
  if (msg->getKind() == APP_SENSING_FLAG)
  {
    Data *data = new Data;
    data->setKind(LAYER_APP);

    data->setValue("Hello");
    data->setTime(simTime().dbl());
    send(data, gate("lowerOut"));

    newData();

    /* End to end statistics */
    ((Statistic*) simulation.getModuleByPath("statistic"))->packetRateTracking(APP_SEND);
  }
}

void Client::finish()
{
}

void Client::newData()
{
  int randomness = 2;   // second
  int sendInterval = 4; // second

  int time = sendInterval + ((rand() % randomness));

  cMessage *event = new cMessage;
  event->setKind(APP_SENSING_FLAG);

  if (simTime().dbl() == 0)
    time++;
  scheduleAt(simTime() + time, event);
}

}
;
// namespace

