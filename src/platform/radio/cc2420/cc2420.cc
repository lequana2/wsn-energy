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

#include "world.h"
#include "statistic.h"

#include "battery.h"

#ifndef  DEBUG
#define  DEBUG 1
#endif

namespace wsn_energy {

Define_Module(cc2420)

cc2420::~cc2420()
{
  this->neighbor.clear();
}

void cc2420::initialize()
{
  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->broadcastMessage = NULL;

  receive_on();
}

void cc2420::handleMessage(cMessage* msg)
{
  if (msg->getKind() == TRX_BROADCAST)
  {
    transmit_on((Raw*) msg);
  }
  else if (msg->getKind() == TOF_BROADCAST)
  {
    transmit_off();
  }
  else if (msg->getKind() == ROF_BROADCAST)
  {
    // to upper layer
    msg->setKind(LAYER_NET);
    send(msg, gate("upperOut"));
  }
}

void cc2420::finish()
{
}

/*
 * Turn on to transmit
 */
void cc2420::transmit_on(Raw *msg)
{
  if (DEBUG)
    ev << "Trans on" << endl;

  // WSN Carrier sense
  if (((World*) simulation.getModuleByPath("world"))->senseBusyTransmission(new Transmission(this, NULL)))
  {
    if (DEBUG)
      ev << "busy channel" << endl;
//    scheduleAt(simTime() + 0.01, msg);
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
    cc2420 *recver = (cc2420*) simulation.getModule(neighbor.at(i));
    // register transmission
    ((World*) simulation.getModuleByPath("world"))->registerTransmission(new Transmission(this, recver));
  }

  // WSN finish time = len / data rate
  double finishTime = 127.0 * 8 / 250000;
  scheduleAt(simTime() + finishTime, new cMessage(NULL, TOF_BROADCAST));

  receive_off();
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_TRANSMIT);
}

/*
 *   Turn off transmitting
 */
void cc2420::transmit_off()
{
  if (DEBUG)
    ev << "Trans off" << endl;

  broadcastMessage->setKind(ROF_BROADCAST);
  broadcastMessage->setRadioSendId(this->getParentModule()->getId());

  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    cc2420* recver = (cc2420*) simulation.getModule(neighbor.at(i));

    Transmission *completeTranmission = new Transmission(this, recver);

    // check feasible
    if (((World*) simulation.getModuleByPath("world"))->isFeasibleTransmission(completeTranmission))
    {
      // EV << "Received" << endl;
      broadcastMessage->setBitError(true);
      ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();
    }
    else
    {
      // EV << "Disposed" << endl;
      recver->getParentModule()->bubble("Collision");
      broadcastMessage->setBitError(false);
      ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
    }

    broadcastMessage->setRadioRecvId(recver->getParentModule()->getId());
    cGate* gate = simulation.getModule(neighbor.at(i))->gate("radioIn");
    sendDirect(broadcastMessage->dup(), gate);

    // Turn receiving mote off
    ((World*) simulation.getModuleByPath("world"))->stopTransmission(completeTranmission);

    recver->receive_off();
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

  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_TRANSMIT);
  //WSN turn listen on
  receive_on();
}

/*
 *   Turn on receiving
 */
void cc2420::receive_on()
{
  if (DEBUG)
    ev << "Recv on" << endl;
  this->isListen = true;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_LISTEN);
}

/*
 *   Turn off receiving
 */
void cc2420::receive_off()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  this->isListen = false;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_LISTEN);
}
}
/* namespace wsn_energy */
