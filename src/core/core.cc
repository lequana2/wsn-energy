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

#include "world.h"
#include "statistic.h"
#include "app.h"
#include "core.h"
#include "rpl.h"
#include "radio.h"

namespace wsn_energy {

Define_Module(Core);

Core::Core()
{
}
Core::~Core()
{
  this->route.clear();
}

//---------------------------------------------------------------------------//
void Core::initialize()
{
  this->rpl = new RPL(this);

//  scheduleAt(simTime(), new cMessage("abc"));
//  if (this->getId() == simulation.getModuleByPath("server.core")->getId())
//    this->rpl->rpl_set_root();
}
//---------------------------------------------------------------------------//
void Core::handleMessage(cMessage *msg)
{
// dispatch event
  if (msg->getKind() == RPL_CONSTRUCT)
  {
    this->rpl->sendDIO();
    return;
  }

  if (msg->getKind() == FIN_TRANSMISS)
  {
    //App layer
//    App* app = ((App*) getParentModule()->getModuleByPath(".app"));
//
//    for (unsigned int i = 0; i < app->neighbor.size(); i++)
//    {
//      Core* recver = (Core*) simulation.getModule(app->neighbor.at(i));

//      Transmission *completeTranmission = new Transmission(this, recver);

      // check feasible

//      if (((World*) simulation.getModuleByPath("world"))->isFeasibleTranmission(completeTranmission))
//      {
        // EV << "Recv" << endl;

//        Radio::broadcastMessage->setRecvID(simulation.getModule(app->neighbor.at(i))->getParentModule()->getId());

//        cGate* gate = simulation.getModule(app->neighbor.at(i))->gate("stream");
//        sendDirect(Radio::broadcastMessage->dup(), gate);

//        ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();
//
//        ((World*) simulation.getModuleByPath("world"))->stopTranmission(completeTranmission);
//      }
//      else
//      {
//        // EV << "Disposed" << endl;
//
//        recver->getParentModule()->bubble("dispose");
//
//        ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
//      }

      // Turn on receiving broadcast
//    }

    // Turn off sending broadcast

//    char newDisplay[20];
//    if (this->getId() == simulation.getModuleByPath("server.core")->getId())
//      sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s", app->axisX, app->axisY);
//    else
//      sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", app->axisX, app->axisY);
//    this->getParentModule()->setDisplayString(newDisplay);

    return;
  }

  // Check arrival message
  if (msg->getKind() == IP_PACKET)
  {
    // receive RPL construct
    if (((IpPacket*) msg)->getType() == IP_ICMP)
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
    }
    //WSN forward data
    else if (((IpPacket*) msg)->getType() == IP_DATA)
    {
    }
  }
}

void Core::finish()
{
}

//---------------------------------------------------------------------------//
void Core::broadcast(IpPacket *msg)
{
  //buffer
//  Radio::broadcastMessage = msg;
//  Radio::broadcastMessage->setSendID(this->getParentModule()->getId());

  //App layer
//  App* app = ((App*) getParentModule()->getModuleByPath(".app"));

  // start broadcasting
//  char newDisplay[20];
//  if (this->getId() == simulation.getModuleByPath("server.core")->getId())
//    sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s;r=120", app->axisX, app->axisY);
//  else
//    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs;r=120", app->axisX, app->axisY);
//  this->getParentModule()->setDisplayString(newDisplay);

//  for (unsigned int i = 0; i < app->neighbor.size(); i++)
//  {
    // register transmission
//    ((World*) simulation.getModuleByPath("world"))->registerTranmission(
//        new Transmission(this, ((Core*) simulation.getModule(app->neighbor.at(i)))));
    // receiving
//  }

  int finishTime = 1;
  scheduleAt(simTime() + finishTime, new cMessage(NULL, FIN_TRANSMISS));
  send(new cMessage(NULL, TRX_BROADCAST), gate("radioOut"));
}

} /* namespace wsn_energy */
