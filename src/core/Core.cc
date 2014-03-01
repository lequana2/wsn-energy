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
  this->ssRange = par("ssRange");
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
    //WSN check feasible
    if (((Enviroment*) simulation.getModuleByPath("enviroment"))->checkFeasibleTranmission(this))
    {
      //WSN send
      ICMP* icmp = (ICMP*) messageBuffer.front();
      messageBuffer.erase(messageBuffer.begin());

      EV << "OUT " << icmp->getSendID() << " " << icmp->getRecvID()  << endl;
    }
    else
    {
      EV << "Conflict" << endl;
    }
  }
}

//---------------------------------------------------------------------------//
void Core::sendMessage(ICMP *msg)
{
  //WSN buffer
  messageBuffer.push_back(msg);
  ((Enviroment*) simulation.getModuleByPath("enviroment"))->registerTranmission(this);

  int size = 1;

  //WSN schedule
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
    char outName[20];
    sprintf(outName, "out %d to %d", this->getId(), this->neighbor.at(i));
//    send(icmp->dup(), outName);
    DIO *icmp_dup = icmp->dup();
    icmp_dup->setRecvID(this->neighbor.at(i));
    this->sendMessage(icmp_dup);
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
    char outName[20];
    sprintf(outName, "out %d to %d", this->getId(), this->neighbor.at(i));
//    send(icmp->dup(), outName);
    this->sendMessage(icmp->dup());
  }
}

} /* namespace wsn_energy */
