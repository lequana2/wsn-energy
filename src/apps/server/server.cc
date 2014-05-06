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
#include <iostream>
#include <fstream>

namespace wsn_energy {

Define_Module(Server);

void Server::initialize()
{
  // WSN DEBUG
//  selfTimer(0, RPL_CONSTRUCT);

  // create new session file
  std::ofstream myfile;
  myfile.open("data.txt");
  myfile << "[Data received from client]";
  myfile.close();
}

void Server::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND:
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

  std::ofstream myfile;
  myfile.open("data.txt", std::ios::app);
  myfile << "\n" << data->getValue();
  myfile.close();

  //  this->getParentModule()->bubble(data->getValue());

  // End to end statistics
  ((Statistic*) simulation.getModuleByPath("statistic"))->registerStatistic(APP_RECV);
  ((Statistic*) simulation.getModuleByPath("statistic"))->registerStatisticDelay(DELAY_APP_LAYER, simTime().dbl() - data->getTime());

  delete packet;
}

}
;
// namespace
