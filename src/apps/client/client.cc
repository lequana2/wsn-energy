/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to client.h
 */

#include "client.h"
#include "radio.h"
#include "statistic.h"

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  /* Contiki test scheme */
  switch ((int) this->getParentModule()->getParentModule()->par("scheme").doubleValue())
  {
    case 1: {
      cMessage *event = new cMessage;
      event->setKind(APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        scheduleAt(simTime() + 1, event->dup());

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        scheduleAt(simTime() + 2, event->dup());

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        scheduleAt(simTime() + 3, event->dup());
    }
      break;

    case 2: {
      newData();
    }
      break;
  }
}

void Client::handleMessage(cMessage *msg)
{
  // stop working
  if (check_and_cast<RadioDriver*>(this->getParentModule()->getModuleByPath(".radio")) == POWER_DOWN)
    return;

  if (msg->getKind() == APP_SENSING_FLAG)
  {
    Data *data = new Data;
    data->setValue("Hello");
    data->setTime(simTime().dbl());
    send(data, gate("lowerOut"));

    if ((int) this->getParentModule()->getParentModule()->par("scheme").doubleValue() == 2)
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
  int sendInterval = 4; // second
  int randomness = 20;   // second

  double time = sendInterval + ((rand() % randomness) / 1000.0);

  cMessage *event = new cMessage;
  event->setKind(APP_SENSING_FLAG);

  this->bubble("Message");
  scheduleAt(simTime() + time, event);
}

}
;
// namespace

