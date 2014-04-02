/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to client.h
 */

#include "client.h"

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  // WSN Client scheme
//  cMessage *event = new cMessage;
//  event->setKind(APP_SENSING_FLAG);

  /* Contiki test scheme */
//  newData();
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
//  if (msg->getKind() == APP_SENSING_FLAG)
//  {
//    Data *data = new Data;
//    data->setKind(LAYER_APP);
//
//    data->setValue("Hello");
//    data->setTime(simTime().dbl());
//    send(data, gate("lowerOut"));
//
//    newData();
//
//    /* End to end statistics */
//    ((Statistic*) simulation.getModuleByPath("statistic"))->packetRateTracking(APP_SEND);
//  }
}

void Client::finish()
{
}

void Client::newData()
{
//  int randomness = 2;   // second
//  int sendInterval = 4; // second
//
//  int time = sendInterval + ((rand() % randomness));
//
//  cMessage *event = new cMessage;
//  event->setKind(APP_SENSING_FLAG);
//
//  if (simTime().dbl() == 0)
//    time++;
//  scheduleAt(simTime() + time, event);
}

}
;
// namespace

