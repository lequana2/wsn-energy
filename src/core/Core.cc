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

void Core::handleMessage(cMessage *msg)
{
  if (msg->getKind() == INIT_MESSAGE)
  {
    cMessage *startMessage = new cMessage();
    startMessage->setKind(START_MESSAGE);
    scheduleAt(simTime() + 1, startMessage);
  }
}

//---------------------------------------------------------------------------//
void Core::sendDIO()
{
  ev << "broadcast DIO" << endl;

  DIO *icmp = new DIO();
  ((cMessage*) icmp)->setKind(ICMP_MESSAGE);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);

  icmp->setDodagID(this->dodagid);

  for (unsigned int i = 0; i < this->neighbor.size(); i++)
  {
    char outName[20];
    sprintf(outName, "out %d to %d", this->getId(), this->neighbor.at(i));
//    send(icmp->dup(), outName);
    sendDelayed(icmp->dup(), 1, outName);
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
    sendDelayed(icmp->dup(), 1, outName);
  }
}

} /* namespace wsn_energy */