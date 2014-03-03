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

#include <math.h>

#include "core.h"
#include "ipPacket_m.h"
#include "enviroment.h"
#include "rpl.h"

#include "statistic.h"

namespace wsn_energy {

Define_Module(Core);

//---------------------------------------------------------------------------//
void Core::initialize()
{
  this->numberClient = par("numberClient");
  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->redundancy = par("redundancy");
  this->axisX = par("axisX");
  this->axisY = par("axisY");
  this->rpl = new RPL(this);
}
//---------------------------------------------------------------------------//
void Core::handleMessage(cMessage *msg)
{
  //WSN Dispatch event
  // End of broadcast transmitting
  if (msg->getKind() == END_BROADCAST)
  {
    // send
    for (unsigned int i = 0; i < this->neighbor.size(); i++)
    {
      char outName[20];
      sprintf(outName, "out %d to %d", this->getId(), this->neighbor.at(i));

      Tranmission *completeTranmission = new Tranmission(this, (Core*) simulation.getModule(this->neighbor.at(i)));
      //check feasible
      if (((Enviroment*) simulation.getModuleByPath("enviroment"))->isFeasibleTranmission(completeTranmission))
      {
        EV << outName << " sent" << endl;
        send(broadcastMessage->dup(), outName);
        ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
      }
      else
      {
        EV << outName << " disposed" << endl;
//        send(broadcastMessage->dup(), outName);
        ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
      }

      ((Enviroment*) simulation.getModuleByPath("enviroment"))->stopTranmission(completeTranmission);

    }

    char newDisplay[20];
    if (this->getId() == simulation.getModuleByPath("server")->getId())
      sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s", this->axisX, this->axisY);
    else
      sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", this->axisX, this->axisY);
    this->setDisplayString(newDisplay);

    return;
  }
  // dispatch constructing
  else if (msg->getKind() == RPL_CONSTRUCT)
  {
    this->rpl->sendDIO();

    return;
  }
  //WSN dispatch message
  else if (msg->getKind() == ICMP_MESSAGE)
  {
    switch (((ICMP*) msg)->getIcmp_code())
    {
      case ICMP_DIO_CODE:
        this->rpl->receiveDIO((DIO*) msg);
        break;
      case ICMP_DIS_CODE:
        this->rpl->receiveDIS((DIS*) msg);
        break;
    }

    return;
  }
}

//---------------------------------------------------------------------------//
void Core::broadcast(IpPacket *msg)
{
//buffer
  broadcastMessage = msg;

  for (unsigned int i = 0; i < this->neighbor.size(); i++)
  {
    ((Enviroment*) simulation.getModuleByPath("enviroment"))->registerTranmission(
        new Tranmission(this, (Core*) simulation.getModule(this->neighbor.at(i))));
  }

// WSN Length of broadcast message
  double size = 0.4;

  char newDisplay[20];
  if (this->getId() == simulation.getModuleByPath("server")->getId())
    sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s;r=120", this->axisX, this->axisY);
  else
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs;r=120", this->axisX, this->axisY);
  this->setDisplayString(newDisplay);

// start broadcasting, check succeed in future
  cMessage *message = new cMessage();
  message->setKind(END_BROADCAST);
  scheduleAt(simTime() + size, message);
}
} /* namespace wsn_energy */
