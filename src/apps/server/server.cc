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

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(Server);

void Server::initialize() {
    this->macAddress = new MacAddress(this->getId());
    // set gloabl server address
    // network address aaaa::/64
    // suppose it is a MAC-48 from 64 bit by putting ff::fe to midle
    // server address aaaa::ff::fe:1
    this->ipAddress = new IpAddress(170, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255,
            254, 0, 0, 1);

    if (DEBUG) {
        std::cout << this->getFullPath() << "has mac address ";
        this->macAddress->print();
        std::cout << this->getFullPath() << "has tentative link-local address ";
        this->ipAddress->print();
        std::cout << endl;
    }

    // create new session file
    std::ofstream myfile;
    myfile.open("data.txt");
    myfile << "[Data received from client]";
    myfile.close();
}

void Server::processSelfMessage(cPacket* packet) {
}

void Server::processUpperLayerMessage(cPacket* packet) {
    // this is highest layer
    return;
}

void Server::processLowerLayerMessage(cPacket* packet) {
    Data* data = check_and_cast<Data*>(packet);

    // Write value to file
    std::ofstream myfile;
    myfile.open("data.txt", std::ios::app);
    myfile << "\n" << data->getValue();
    myfile.close();

    if (DEBUG)
        this->getParentModule()->bubble(data->getValue());

    // End to end statistics
    if (simulation.getModuleByPath("WSN") != NULL) {
        ((Statistic*) simulation.getModuleByPath("statistic"))->registerStatistic(
                APP_RECV);
        ((Statistic*) simulation.getModuleByPath("statistic"))->registerStatisticDelay(
                DELAY_APP_LAYER, simTime().dbl() - data->getTime());
    }

    delete packet;
}

}
;
// namespace
