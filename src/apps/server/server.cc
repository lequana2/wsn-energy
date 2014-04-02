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
  IpPacket *msg = new IpPacket;
  msg->setNote(RPL_CONSTRUCT);
  scheduleAt(simTime(), msg);
}

void Server::handleMessage(cMessage *msg)
{
  switch (check_and_cast<IpPacket*>(msg)->getNote())
  {
    case RPL_CONSTRUCT:
      send(msg, gate("lowerOut"));
      break;

    case LAYER_APP:
      Data* data = check_and_cast<Data*>(msg);
      this->getParentModule()->bubble(data->getValue());

      // End to end statistics
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
