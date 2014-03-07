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
#include "rpl.h"

namespace wsn_energy {

Define_Module(Core);

/*
 * Set up a kernel
 */
void Core::setUp(){
  this->initialize();
}

//---------------------------------------------------------------------------//
void Core::initialize()
{
  this->rpl = new RPL(this);
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

//  if (msg->getKind() == FIN_TRANSMISS)
//  {
//    for (unsigned int i = 0; i < this->neighbor.size(); i++)
//    {
//      Core* recver = (Core*) simulation.getModule(this->neighbor.at(i));
//
//      char outName[20];
//      sprintf(outName, "out %d to %d", this->getId(), recver->getId());
//
////      Transmission *completeTranmission = new Transmission(this, recver);
//
//      // check feasible
////      if (((Enviroment*) simulation.getModuleByPath("enviroment"))->isFeasibleTranmission(completeTranmission))
////      {
////        //      EV << "Recv" << endl;
////        send(this->broadcastMessage->dup(), outName);
////
////        ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();
////        ((Enviroment*) simulation.getModuleByPath("enviroment"))->stopTranmission(completeTranmission);
////      }
////      else
////      {
////        //      EV << "Disposed" << endl;
////        recver->bubble("dispose");
////
////        ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
////      }
//    }
//
//    // Turn off broadcast
//    char newDisplay[20];
//    if (this->getId() == simulation.getModuleByPath("server")->getId())
//      sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s", this->axisX, this->axisY);
//    else
//      sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", this->axisX, this->axisY);
//
//    this->setDisplayString(newDisplay);
//    return;
//  }

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
  broadcastMessage = msg;
  broadcastMessage->setSendID(this->getId());

  // start broadcasting
  char newDisplay[20];
  if (this->getId() == simulation.getModuleByPath("server")->getId())
    sprintf(newDisplay, "p=\%d,\%d;i=abstract/db;is=s;r=120", this->axisX, this->axisY);
  else
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs;r=120", this->axisX, this->axisY);
  this->setDisplayString(newDisplay);

//  for (unsigned int i = 0; i < this->neighbor.size(); i++)
//  {
//    char outName[20];
//    sprintf(outName, "out %d to %d", this->getId(), this->neighbor.at(i));
//
//    // register transmission
////    ((Enviroment*) simulation.getModuleByPath("enviroment"))->registerTranmission(
////        new Transmission(this, (Core*) simulation.getModule(this->neighbor.at(i))));
//
////    send(broadcastMessage->dup(), outName);
//  }

  int finishTime = 1;
  scheduleAt(simTime() + finishTime, new cMessage(NULL, FIN_TRANSMISS));
}

} /* namespace wsn_energy */
