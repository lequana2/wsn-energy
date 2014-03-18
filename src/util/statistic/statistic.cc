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

#include "statistic.h"
#include "battery.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cconfiguration.h>

namespace wsn_energy {

Define_Module(Statistic);

Statistic::Statistic()
{
  polling = new cMessage();

  numRecvPacket = 0;
  numLostPacket = 0;
  numSensData = 0;
  numRecvData = 0;

  totalSensorEnergySignal = registerSignal("total_sensor_energy");

  sigRecvPacket = registerSignal("recv_packet");
  sigLostPacket = registerSignal("lost_packet");
  sigSensData = registerSignal("sens_data");
  sigRecvData = registerSignal("recv_data");
}

Statistic::~Statistic()
{
  cancelAndDelete(polling);
}

void Statistic::initialize()
{
  // Record total sensor energy for first time
  pollTotalSensorEnergy();
  scheduleAt(simTime() + getParentModule()->par("polling").doubleValue(), polling);
}

void Statistic::handleMessage(cMessage *msg)
{
  if (msg->isSelfMessage())
  {
    if (msg == polling)
    {
      pollTotalSensorEnergy();
      scheduleAt(simTime() + getParentModule()->par("polling").doubleValue(), polling);
    }
  }
}

void Statistic::pollTotalSensorEnergy()
{
  /* Calculate total sensor energy */
  cModule *wsn = getModuleByPath("WSN");
  int numberClient = wsn->par("numberClient").longValue();

  double totalEnergy = 0;

  Battery *battery;

  for (int i = 0; i < numberClient; i++)
  {
    battery = check_and_cast<Battery*>(wsn->getSubmodule("client", i)->getSubmodule("battery"));
    totalEnergy += battery->capsuleCumulativeEnergest;
  }

  emit(totalSensorEnergySignal, totalEnergy);
}

void Statistic::incRecvPacket()
{
  Enter_Method_Silent
  ("incRecvPacket");
  numRecvPacket++;
  emit(sigRecvPacket, numRecvPacket);
}

void Statistic::incLostPacket()
{
  Enter_Method_Silent
  ("incLostPacket");
  numLostPacket++;
  emit(sigLostPacket, numLostPacket);
}

void Statistic::incSensData()
{
  Enter_Method_Silent
  ("incSensData");
  numSensData++;
  emit(sigSensData, numSensData);
}

void Statistic::incRecvData()
{
  Enter_Method_Silent
  ("incRecvData");
  numRecvData++;
  emit(sigRecvData, numRecvData);
}

void Statistic::finish()
{
  recRemainingEnergy();
}

void Statistic::recRemainingEnergy()
{
//    using namespace std;
//
//    cConfigurationEx *configEx = ev.getConfigEx();
//    string buffer;
//    cModule *wsn = getModuleByPath("Wsn");
//    Energy *ener;
//    Mobility *mob;
//    int nss = wsn->par("numSensors").longValue();
//    int i;
//
//    buffer.append("results/");
//    buffer.append(configEx->getActiveConfigName());
//    buffer.append("_RemainEnergy.data\0");
//    ofstream out(buffer.c_str(), ios::out | ios::trunc);
//
//    if (!out) {
//        cerr << "Cannot output data\n";
//        return;
//    }
//
//    out << "# Config: " << configEx->getActiveConfigName() << '\n';
//    out << "# Remaining energy" << endl;
//    out << '#' << right << setw(3) << "row" << ' ' << setw(4) << "col" << ' '
//            << setw(7) << "x" << ' ' << setw(7) << "y" << ' '
//            << setw(10) << "energy" << endl;
//
//    for (i = 0; i < nss; i++) {
//        ener = check_and_cast<Energy*>(wsn->getSubmodule("sensor", i)->getSubmodule("energy"));
//        mob = check_and_cast<Mobility*>(wsn->getSubmodule("sensor", i)->getSubmodule("mobility"));
//
//        out << right << setw(4) << mob->getRow() << ' ' << setw(4) << mob->getCol() << ' '
//                << setw(7) << mob->getX() << ' ' << setw(7) << mob->getY() << ' '
//                << setw(10) << ener->getCapacity() << endl;
//    }
//
//    out.close();
}
}
