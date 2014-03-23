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

#include "nullRadio.h"

#include "world.h"
#include "statistic.h"
#include "battery.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(nullRadio);

void nullRadio::initialize()
{
  RadioDriver::initialize();
}

void nullRadio::handleMessage(cMessage* msg)
{
  RadioDriver::handleMessage(msg);
}

void nullRadio::finish()
{
  RadioDriver::finish();
}

/*
 * Turn on to transmit
 */
void nullRadio::transmit_on(Raw *msg)
{
  if (DEBUG)
    ev << "Trans on" << endl;

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

  listen_off();
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_TRANSMIT);
}

/*
 *   Turn off transmitting
 */
void nullRadio::transmit_off()
{
  if (DEBUG)
    ev << "Trans off" << endl;

  broadcastMessage->setKind(LAYER_RADIO_END_RECV);
  broadcastMessage->setRadioSendId(this->getParentModule()->getId());

  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    RadioDriver* recver = (RadioDriver*) simulation.getModule(neighbor.at(i));

    Transmission *completeTranmission = new Transmission(this, recver);

    broadcastMessage->setBitError(true);
    broadcastMessage->setRadioRecvId(recver->getParentModule()->getId());
    broadcastMessage->setTypeRadioLayer(LAYER_RADIO_OK);

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

/*
 *   Turn on receiving
 */
void nullRadio::listen_on()
{
  if (DEBUG)
    ev << "Recv on" << endl;
  this->isListen = true;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_LISTEN);
}

/*
 *   Turn off receiving
 */
void nullRadio::listen_off()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  this->isListen = false;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_LISTEN, getRxPower());
}

double nullRadio::getTxPower()
{
  return 1;
}

double nullRadio::getRxPower()
{
  return 1;
}

} /* namespace wsn_energy */
