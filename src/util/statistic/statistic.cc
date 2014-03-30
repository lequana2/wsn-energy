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
  numTotalEnergy = 0;

  sigNodeEnergy = registerSignal("node_energy");
  sigTotalEnergy = registerSignal("total_sensor_energy");

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
  /* Record total sensor energy for first time */
  pollTotalSensorEnergy();
  if (getParentModule()->par("isPolling").doubleValue())
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

  Battery *battery;
  numTotalEnergy = 0;

  for (int i = 0; i < numberClient; i++)
  {
    battery = check_and_cast<Battery*>(wsn->getSubmodule("client", i)->getSubmodule("battery"));
    numTotalEnergy += battery->energestRemaining;
  }

  emit(sigNodeEnergy, numTotalEnergy);
  emit(sigTotalEnergy, numTotalEnergy);
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
//  recRemainingEnergy();
}

}
