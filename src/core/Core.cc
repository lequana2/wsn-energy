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

#include "Core.h"
#include "ICMP_m.h"
#include "Enviroment.h"

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
  this->dodagid = 0;
  this->rank = RANK_INFINITY;

  cMessage *initMessage = new cMessage();
  initMessage->setKind(INIT_MESSAGE);
  scheduleAt(simTime(), initMessage);
}
//---------------------------------------------------------------------------//
void Core::handleMessage(cMessage *msg)
{
  if (msg->getKind() == MESSAGE)
  {
    //WSN send
    ICMP* icmp = (ICMP*) messageBuffer.front();

    char outName[20];
    sprintf(outName, "out %d to %d", this->getId(), icmp->getRecvID());

    Tranmission *completeTranmission = new Tranmission(this, (Core*) simulation.getModule(icmp->getRecvID()));

    //check feasible
    if (((Enviroment*) simulation.getModuleByPath("enviroment"))->isFeasibleTranmission(completeTranmission))
    {
      EV << outName << " sent" << endl;
      send(icmp, outName);
    }
    else
    {
      EV << "Conflict" << endl;
//      send(icmp, outName);
    }

    ((Enviroment*) simulation.getModuleByPath("enviroment"))->stopTranmission(completeTranmission);

    messageBuffer.pop_front();

    return;
  }
}

//---------------------------------------------------------------------------//
void Core::sendMessage(Core*recv, ICMP *msg)
{
//buffer
  messageBuffer.push_back(msg);
  ((Enviroment*) simulation.getModuleByPath("enviroment"))->registerTranmission(new Tranmission(this, recv));

// Length of broadcast message
  int size = 1;

//schedule
  cMessage *message = new cMessage();
  message->setKind(MESSAGE);
  scheduleAt(simTime() + size, message);
}
//---------------------------------------------------------------------------//
void Core::sendDIO()
{
  ev << "broadcast DIO" << endl;

  DIO *icmp = new DIO();
  ((cMessage*) icmp)->setKind(ICMP_MESSAGE);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);

  icmp->setSendID(this->getId());
  icmp->setDodagID(this->dodagid);

  for (unsigned int i = 0; i < this->neighbor.size(); i++)
  {
    DIO *icmp_dup = icmp->dup();
    icmp_dup->setRecvID(this->neighbor.at(i));
    this->sendMessage((Core*) simulation.getModule(this->neighbor.at(i)), icmp_dup);
  }
}

//---------------------------------------------------------------------------//
void Core::sendDIS(int convergence)
{
  ev << "broadcast DIS" << endl;

  DIS *icmp = new DIS();
  ((cMessage*) icmp)->setKind(ICMP_MESSAGE);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIS_CODE);

  icmp->setConvergence(convergence);

  for (unsigned int i = 0; i < this->neighbor.size(); i++)
  {
    DIS *icmp_dup = icmp->dup();
    icmp_dup->setRecvID(this->neighbor.at(i));

    this->sendMessage((Core*) simulation.getModule(this->neighbor.at(i)), icmp_dup);
  }
}

} /* namespace wsn_energy */
