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
  /*
   * Turn on to transmit
   */
  if (msg->getKind() == TRX_BROADCAST)
  {
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
      // register transmission
      ((World*) simulation.getModuleByPath("world"))->registerTranmission(
          new Transmission(this, ((Radio*) simulation.getModule(neighbor.at(i)))));
    }

    int finishTime = 1;
    scheduleAt(simTime() + finishTime, new cMessage(NULL, END_BROADCAST));
  }
  /*
   * Turn off transmitting
   */
  else if (msg->getKind() == END_BROADCAST)
  {
    ev << "Trans off" << endl;

    broadcastMessage->setKind(RCV_BROADCAST);

    for (unsigned int i = 0; i < neighbor.size(); i++)
    {
      Radio* recver = (Radio*) simulation.getModule(neighbor.at(i));

      Transmission *completeTranmission = new Transmission(this, recver);

      // check feasible
      if (((World*) simulation.getModuleByPath("world"))->isFeasibleTranmission(completeTranmission))
      {
        // EV << "Recv" << endl;

        cGate* gate = simulation.getModule(neighbor.at(i))->gate("raw");
        sendDirect(broadcastMessage->dup(), gate);

        ((World*) simulation.getModuleByPath("world"))->stopTranmission(completeTranmission);

        ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();

        // WSN send to upper layer
      }
      else
      {
        // EV << "Disposed" << endl;

        recver->getParentModule()->bubble("dispose");

        ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
      }
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

    return;
  }
  /*
   * Turn on to receive
   */
  else if (msg->getKind() == RCX_BROADCAST)
  {
    ev << "Recv on" << endl;
  }
  /*
   * Turn off receiving
   */
  else if (msg->getKind() == RCV_BROADCAST)
  {
    ev << "Recv off" << endl;
  }
}

void Radio::finish()
{
}

void Radio::transmit_on()
{
}

void Radio::receive_on()
{
}
void Radio::transmit_off()
{
}

void Radio::receive_off()
{
}
}
/* namespace wsn_energy */
