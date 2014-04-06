/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to server.h
 */

#include "server.h"
#include "statistic.h"
#include "packet_m.h"

namespace wsn_energy {

Define_Module(Server);

void Server::initialize()
{
  Data *msg = new Data;
  msg->setNote(RPL_CONSTRUCT);
  scheduleAt(simTime(), msg);
}

void Server::processSelfMessage(cPacket* packet)
{
  switch (check_and_cast<Data*>(packet)->getNote())
  {
    case RPL_CONSTRUCT:
      sendMessageToLower(packet);
      break;
  }
}

void Server::processUpperLayerMessage(cPacket* packet)
{
  // this is highest layer
  return;
}

void Server::processLowerLayerMessage(cPacket* packet)
{
  Data* data = check_and_cast<Data*>(packet);
  this->getParentModule()->bubble(data->getValue());

  // End to end statistics
  ((Statistic*) simulation.getModuleByPath("statistic"))->packetRateTracking(APP_RECV);
  ((Statistic*) simulation.getModuleByPath("statistic"))->packetDelayTracking(simTime().dbl() - data->getTime());
}

}
;
// namespace
