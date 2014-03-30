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

void Statistic::initialize()
{
  polling = new cMessage();

  // Initialize statistics number
  numTotalEnergy = 0;
  numTotalDelay = 0;
  numAppSend = 0;
  numAppRecv = 0;
  numNetSend = 0;
  numNetRecv = 0;
  numMacSend = 0;
  numMacRecv = 0;
  numRadioSend = 0;
  numRadioRecv = 0;

  // register signal
  sigSensorEnergy = registerSignal("sensorEnergy");
  sigTotalEnergy = registerSignal("totalEnergy");
  sigTotalDelay = registerSignal("totalDelay");
  sigAppSend = registerSignal("appSend");
  sigAppRecv = registerSignal("appRecv");
  sigNetSend = registerSignal("netSend");
  sigNetRecv = registerSignal("netRecv");
  sigMacSend = registerSignal("macSend");
  sigMacRecv = registerSignal("macRecv");
  sigRadioSend = registerSignal("radioSend");
  sigRadioRecv = registerSignal("radioRecv");

  // Record total sensor energy for first time
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

void Statistic::finish()
{
  // Power status of remaining sensor(s)
  cModule *wsn = getModuleByPath("WSN");
  int numberClient = wsn->par("numberClient").longValue();

  for (int i = 0; i < numberClient; i++)
  {
    numSensorEnergy =
        (check_and_cast<Battery*>(wsn->getSubmodule("client", i)->getSubmodule("battery")))->energestRemaining;
    emit(sigSensorEnergy, numSensorEnergy);
  }

  emit(sigTotalEnergy, numTotalEnergy);

  cancelAndDelete(polling);
}

void Statistic::pollTotalSensorEnergy()
{
  cModule *wsn = getModuleByPath("WSN");
  int numberClient = wsn->par("numberClient").longValue();

  numTotalEnergy = 0;

  for (int i = 0; i < numberClient; i++)
    numTotalEnergy +=
        (check_and_cast<Battery*>(wsn->getSubmodule("client", i)->getSubmodule("battery")))->energestRemaining;

  emit(sigTotalEnergy, numTotalEnergy);
}

void Statistic::packetRateTracking(int type)
{
  Enter_Method_Silent
  ("packetRateTracking");
  switch (type)
  {
    case APP_SEND:
      numAppSend++;
      emit(sigAppSend, numAppSend);
      break;
    case APP_RECV:
      numAppRecv++;
      emit(sigAppRecv, numAppRecv);
      break;
    case NET_SEND:
      numNetSend++;
      emit(sigNetSend, numNetSend);
      break;
    case NET_RECV:
      numNetRecv++;
      emit(sigNetRecv, numNetRecv);
      break;
    case MAC_SEND:
      numMacSend++;
      emit(sigMacSend, numMacSend);
      break;
    case MAC_RECV:
      numMacRecv++;
      emit(sigMacRecv, numMacRecv);
      break;
    case RADIO_SEND:
      numRadioSend++;
      emit(sigRadioSend, numRadioSend);
      break;
    case RADIO_RECV:
      numRadioRecv++;
      emit(sigRadioRecv, numRadioRecv);
      break;
  }
}

void Statistic::increaseTotalDelay(double delayTime)
{
  numTotalDelay += delayTime;
  emit(sigTotalDelay, numTotalDelay);
}
}
