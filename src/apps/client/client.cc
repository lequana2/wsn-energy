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
    case 1: /* one event */
    {
      cPacket *event = new cPacket;
      event->setKind(APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        scheduleAt(simTime() + 1, event->dup());

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        scheduleAt(simTime() + 2, event->dup());

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        scheduleAt(simTime() + 3, event->dup());
    }
      break; /* one event */

    case 2: /* ignite periodically */
    {
      newData();
    }
      break; /* ignite periodically */

    default:
      ev << "Just construct " << endl;
      break;
  }

  this->maximumPacket = 0;
}

void Client::handleMessage(cMessage *msg)
{
  // stop working
  if (check_and_cast<RadioDriver*>(this->getParentModule()->getModuleByPath(".radio")) == POWER_DOWN)
  {
    delete msg;
    return;
  }

  myModule::handleMessage(msg);
}

void Client::finish()
{
}

void Client::processSelfMessage(cPacket* msg)
{
  if (msg->getKind() == APP_SENSING_FLAG)
  {
    Data *data = new Data;

    data->setKind(DATA);
    data->setValue("Hello");
    data->setTime(simTime().dbl());
    sendMessageToLower(data);

    delete msg;

    /* End to end statistics */
    ((Statistic*) simulation.getModuleByPath("statistic"))->packetRateTracking(APP_SEND);

    if ((int) this->getParentModule()->getParentModule()->par("scheme").doubleValue() == 2)
    {
      // control maximum number
      if (this->maximumPacket++ < MAX)
        newData();
    }
  }
}

void Client::processUpperLayerMessage(cPacket*)
{
  /* Highest layer */
  return;
}

void Client::processLowerLayerMessage(cPacket*)
{
  /* ??? feedback */
  return;
}

void Client::newData()
{
  int sendInterval = 4; // second
  int randomness = 4;   // second

  // avoid immediately sending
  double time = sendInterval + (((rand() % randomness) + 1) / 1000.0);

  cPacket *event = new cPacket;
  event->setKind(APP_SENSING_FLAG);

  this->getParentModule()->bubble("Data");

  scheduleAt(simTime() + time, event);
}

}
;
// namespaces
