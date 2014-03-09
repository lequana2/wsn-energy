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

#include <radio.h>
#include "world.h"
#include "statistic.h"

#ifndef DEBUG
#define DEBUG 0

namespace wsn_energy {

Define_Module(Radio)

Radio::Radio()
{
}

Radio::~Radio()
{
  this->neighbor.clear();
}

void Radio::initialize()
{
  this->trRange = par("trRange");
  this->coRange = par("coRange");
}

void Radio::handleMessage(cMessage* msg)
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
    msg->setKind(WORKING_FLAG);
    send(msg, gate("radioOut"));
  }
}

void Radio::finish()
{
}

/*
 * Turn on to transmit
 */
void Radio::transmit_on(Raw *msg)
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
    Radio *recver = (Radio*) simulation.getModule(neighbor.at(i));
    // register transmission
    ((World*) simulation.getModuleByPath("world"))->registerTranmission(new Transmission(this, recver));

    // turn receiving mote on
    recver->receive_on();
  }

  int finishTime = 1;
  scheduleAt(simTime() + finishTime, new cMessage(NULL, TOF_BROADCAST));
}

/*
 *   Turn off transmitting
 */
void Radio::transmit_off()
{
  if (DEBUG)
    ev << "Trans off" << endl;

  broadcastMessage->setKind(ROF_BROADCAST);
  broadcastMessage->setRadioSendId(this->getParentModule()->getId());

  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    Radio* recver = (Radio*) simulation.getModule(neighbor.at(i));

    Transmission *completeTranmission = new Transmission(this, recver);

    // check feasible
    if (((World*) simulation.getModuleByPath("world"))->isFeasibleTranmission(completeTranmission))
    {
      // EV << "Received" << endl;
      broadcastMessage->setRadioRecvId(recver->getParentModule()->getId());

      cGate* gate = simulation.getModule(neighbor.at(i))->gate("raw");
      sendDirect(broadcastMessage->dup(), gate);

      ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();
    }
    else
    {
      // EV << "Disposed" << endl;

      recver->getParentModule()->bubble("dispose");

      ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
    }

    // Turn receiving mote off
    ((World*) simulation.getModuleByPath("world"))->stopTranmission(completeTranmission);
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
}

/*
 *   Turn on receiving
 */
void Radio::receive_on()
{
  if (DEBUG)
    ev << "Recv on" << endl;
  // Battery utils
}

/*
 *   Turn off receiving
 */
void Radio::receive_off()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  // Battery utils
}
}
/* namespace wsn_energy */
