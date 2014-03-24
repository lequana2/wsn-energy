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

#include "cc2420.h"
#include "cc2420-const.h"

#include "world.h"
#include "statistic.h"
#include "battery.h"

#ifndef  DEBUG
#define  DEBUG 1
#endif

namespace wsn_energy {

Define_Module(cc2420);

void cc2420::initialize()
{
  RadioDriver::initialize();
}

void cc2420::handleMessage(cMessage* msg)
{
  RadioDriver::handleMessage(msg);
}

void cc2420::finish()
{
  RadioDriver::finish();
}

/*
 * Turn on to transmit
 */
void cc2420::transmit_on(Raw *msg)
{
  if (DEBUG)
    ev << "Trans on" << endl;

  // WSN Carrier sense
  if (isClearChannel())
  {
    if (DEBUG)
      ev << "busy channel" << endl;
    Raw *msg = new Raw;
    msg->setKind(LAYER_RADIO);
    msg->setTypeRadioLayer(LAYER_RADIO_COL);
    send(msg,gate("upperOut"));
    return;
  }

  // buffer
  broadcastMessage = (Raw*) msg;

  // start broadcasting
  char newDisplay[20];

  int x = getParentModule()->par("axisX");
  int y = getParentModule()->par("axisY");

  if (this->getId() == simulation.getModuleByPath("server.radio")->getId())
    sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s;r=%d", x, y, trRange);
  else
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs;r=%d", x, y, trRange);

  getParentModule()->setDisplayString(newDisplay);

  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    RadioDriver *recver = (RadioDriver*) simulation.getModule(neighbor.at(i));
    // register transmission
    ((World*) simulation.getModuleByPath("world"))->registerTransmission(new Transmission(this, recver));
  }

  // WSN finish time = len / data rate
  double finishTime = 127.0 * 8 / 250000;
  scheduleAt(simTime() + finishTime, new cMessage(NULL, LAYER_RADIO_END_TRANS));

  // turn off listening and transmitting
  listen_off();
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_TRANSMIT);
}

/*
 *   Turn off transmitting
 */
void cc2420::transmit_off()
{
  if (DEBUG)
    ev << "Trans off" << endl;

  broadcastMessage->setKind(LAYER_RADIO_END_RECV);
  broadcastMessage->setRadioSendId(this->getParentModule()->getId());

  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    RadioDriver* recver = (RadioDriver*) simulation.getModule(neighbor.at(i));

    Transmission *completeTranmission = new Transmission(this, recver);

    // check feasible
    if (((World*) simulation.getModuleByPath("world"))->isFeasibleTransmission(completeTranmission))
    {
      // EV << "Received" << endl;
      broadcastMessage->setBitError(true);
      broadcastMessage->setTypeRadioLayer(LAYER_RADIO_OK);

      ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();
    }
    else
    {
      // EV << "Disposed" << endl;
      recver->getParentModule()->bubble("Corrupted");
      broadcastMessage->setBitError(false);
      broadcastMessage->setTypeRadioLayer(LAYER_RADIO_COL);

      ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
    }

    broadcastMessage->setRadioRecvId(recver->getParentModule()->getId());
    cGate* gate = simulation.getModule(neighbor.at(i))->gate("radioIn");
    sendDirect(broadcastMessage->dup(), gate);

    // Turn receiving mote off
    ((World*) simulation.getModuleByPath("world"))->stopTransmission(completeTranmission);
  }

  // Turn off sending broadcast
  char newDisplay[20];

  int x = getParentModule()->par("axisX");
  int y = getParentModule()->par("axisY");

  if (this->getId() == simulation.getModuleByPath("server.radio")->getId())
    sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s", x, y);
  else
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", x, y);

  getParentModule()->setDisplayString(newDisplay);

  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_TRANSMIT, getTxPower());
}

bool cc2420::isClearChannel(){
  return ((World*) simulation.getModuleByPath("world"))->senseBusyTransmission(new Transmission(this, NULL));
}

double cc2420::getTxPower()
{
  return TXPOWER_CURRENT * SUPPLY_VOLTAGE;
}

double cc2420::getRxPower()
{
  return RXPOWER_CURRENT * SUPPLY_VOLTAGE;
}

}
/* namespace wsn_energy */
