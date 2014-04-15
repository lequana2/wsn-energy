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
#include "energest.h"
#include "count.h"
#include "mac.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cconfiguration.h>

namespace wsn_energy {

Define_Module(Statistic);

void Statistic::initialize()
{
  polling = new cMessage();
  pollingCount = new cMessage();

  // Initialize statistics number
  numNetworkEnergyCount = 0;
  numSensorEnergyCount = 0;
  numNetworkEnergy = 0;
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
  timeIdle = 0;
  timeListen = 0;
  timeTrans = 0;
  numDIOsent = 0;
  numIPinter = 0;
  numIPtrans = 0;

  // register signal
  sigNetworkEnergyCount = registerSignal("networkEnergyCount");
  sigSensorEnergyCount = registerSignal("sensorEnergyCount");
  sigNetworkEnergy = registerSignal("networkEnergy");
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
  sigTimeIdle = registerSignal("timeIdle");
  sigTimeListen = registerSignal("timeListen");
  sigLifeTime = registerSignal("lifeTime");
  sigTimeTrans = registerSignal("timeTrans");
  sigNumDIOsent = registerSignal("dioSent");
  sigNumIPinter = registerSignal("ipInter");
  signumIPtrans = registerSignal("ipTrans");

  // Record total sensor energy for first time
  pollTotalSensorEnergy();
  pollTotalSensorEnergyCount();

  if (getParentModule()->par("isPolling").doubleValue())
    scheduleAt(simTime() + getParentModule()->par("polling").doubleValue(), polling);

  if (getParentModule()->par("isPollingCount").doubleValue())
    scheduleAt(simTime() + getParentModule()->par("polling").doubleValue(), pollingCount);
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
    else if (msg == pollingCount)
    {
      if (simTime() + getParentModule()->par("polling") < getModuleByPath("^")->par("timeLimit").doubleValue())
      {
        pollTotalSensorEnergyCount();
        scheduleAt(simTime() + getParentModule()->par("polling").doubleValue(), pollingCount);
      }
    }
  }
}

void Statistic::finish()
{
  // poll last time
  pollTotalSensorEnergy();

  // Power status of remaining sensor(s)
  cModule *wsn = getModuleByPath("WSN");
  int numberClient = wsn->par("numberClient").longValue();
  int shitRemainingInBuffer = 0;

  for (int i = 0; i < numberClient; i++)
  {
    numSensorEnergy =
        (check_and_cast<Energest*>(wsn->getSubmodule("client", i)->getSubmodule("energest")))->energestRemaining;

    numTotalEnergy += numSensorEnergy;

    // % duty cycling
    timeTrans +=
        (check_and_cast<Energest*>(wsn->getSubmodule("client", i)->getSubmodule("energest")))->capsuleTotalTime[ENERGEST_TYPE_TRANSMIT];
    timeListen +=
        (check_and_cast<Energest*>(wsn->getSubmodule("client", i)->getSubmodule("energest")))->capsuleTotalTime[ENERGEST_TYPE_LISTEN];
    timeIdle +=
        (check_and_cast<Energest*>(wsn->getSubmodule("client", i)->getSubmodule("energest")))->capsuleTotalTime[ENERGEST_TYPE_IDLE];
    emit(sigSensorEnergy, numSensorEnergy);

    // residual energy
    numSensorEnergyCount =
        check_and_cast<Count*>(wsn->getSubmodule("client", i)->getSubmodule("count"))->residualEnergy;
    emit(sigSensorEnergyCount, numSensorEnergyCount);

    shitRemainingInBuffer +=
        (check_and_cast<MACdriver*>(wsn->getSubmodule("client", i)->getSubmodule("mac")))->buffer.size();
  }

  emit(sigTimeIdle, timeIdle);
  emit(sigTimeTrans, timeTrans);
  emit(sigTimeListen, timeListen);
  emit(sigTotalEnergy, numTotalEnergy);

  // WSN just DEBUG
  emit(sigRadioRecv, shitRemainingInBuffer);
  emit(sigRadioSend, timeIdle + timeTrans + timeListen);

  cancelAndDelete(polling);
  cancelAndDelete(pollingCount);
}

void Statistic::pollTotalSensorEnergyCount()
{
  cModule *wsn = getModuleByPath("WSN");
  int numberClient = wsn->par("numberClient").longValue();

  numNetworkEnergyCount = 0.0;

  for (int i = 0; i < numberClient; i++)
  {
    numNetworkEnergyCount +=
        (check_and_cast<Count*>(wsn->getSubmodule("client", i)->getSubmodule("count")))->residualEnergy;
  }

  emit(sigNetworkEnergyCount, numNetworkEnergyCount);
}

void Statistic::pollTotalSensorEnergy()
{
  cModule *wsn = getModuleByPath("WSN");
  int numberClient = wsn->par("numberClient").longValue();

  numNetworkEnergy = 0.0;

  for (int i = 0; i < numberClient; i++)
  {
    (check_and_cast<Energest*>(wsn->getSubmodule("client", i)->getSubmodule("energest")))->update();
    numNetworkEnergy +=
        (check_and_cast<Energest*>(wsn->getSubmodule("client", i)->getSubmodule("energest")))->energestRemaining;
  }

  emit(sigNetworkEnergy, numNetworkEnergy);
}

void Statistic::packetRateTracking(int type)
{
  Enter_Method_Silent
  ("packetRateTracking");
  switch (type)
  {
    case APP_SEND:
      emit(sigAppSend, ++numAppSend);
      break;
    case APP_RECV:
      emit(sigAppRecv, ++numAppRecv);
      break;
    case NET_SEND:
      emit(sigNetSend, ++numNetSend);
      break;
    case NET_RECV:
      emit(sigNetRecv, ++numNetRecv);
      break;
    case MAC_SEND:
      emit(sigMacSend, ++numMacSend);
      break;
    case MAC_RECV:
      emit(sigMacRecv, ++numMacRecv);
      break;
    case RADIO_SEND:
      emit(sigRadioSend, ++numRadioSend);
      break;
    case RADIO_RECV:
      emit(sigRadioRecv, ++numRadioRecv);
      break;
    case DIO_SENT:
      emit(sigNumDIOsent, ++numDIOsent);
      break;
    case IP_INTER:
      emit(sigNumIPinter, ++numIPinter);
      break;
    case IP_TRANS:
      emit(signumIPtrans, ++numIPtrans);
      break;
    case LIFE_TIME_INCREASE_SERVER_NEIGHBOR:
      this->numServerNeighbor++;
      std::cout << "Server neighbor: " << numServerNeighbor << endl;
      break;
    case LIFE_TIME_DECREASE_SERVER_NEIGHBOR:
      this->numServerNeighbor--;
      std::cout << "Dead neighbor: " << numServerNeighbor << endl;
      if (this->numServerNeighbor == 0)
        emit(sigLifeTime, simTime().dbl());
      break;
  }
}

void Statistic::packetDelayTracking(double delayTime)
{
  Enter_Method_Silent
  ("packetDelayTracking");
  numTotalDelay += delayTime;
  emit(sigTotalDelay, numTotalDelay);
}
}
