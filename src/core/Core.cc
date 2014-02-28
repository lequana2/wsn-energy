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
  this->rank    = RANK_INFINITY;

  cMessage *initMessage = new cMessage();
  initMessage->setKind(INIT_MESSAGE);
  scheduleAt(simTime(), initMessage);
}

void Core::handleMessage(cMessage *msg)
{
  if (msg->getKind() == INIT_MESSAGE)
  {
    createConnection();
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
//---------------------------------------------------------------------------//
void Core::createConnection()
{
  // Check with server
  Core *module = (Core*) simulation.getModuleByPath("server");
  if (checkConnection(this, module))
    this->neighbor.push_back(module->getId());

  // Check with client(s)
  for (int i = 0; i < this->numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    Core *module = (Core*) simulation.getModuleByPath(modulePath);

    if (checkConnection(this, module))
      this->neighbor.push_back(module->getId());
  }

//  EV << "Number of neighbor " << this->neighbor.size() << endl;
}

//---------------------------------------------------------------------------//
int Core::checkConnection(Core *x, Core *y)
{
  if (calculateDistance(x->axisX, x->axisY, y->axisX, y->axisY) > x->trRange)
    return 0;
  if (x->getId() == y->getId())
    return 0;

  char setOutConnectionCommand[20];
  char setInConnectionCommand[20];
  cGate *outGate;
  cGate *inGate;

  sprintf(setOutConnectionCommand, "out %d to %d", x->getId(), y->getId());
  sprintf(setInConnectionCommand, "in %d to %d", x->getId(), y->getId());

  outGate = this->addGate(setOutConnectionCommand, cGate::OUTPUT);
  inGate = y->addGate(setInConnectionCommand, cGate::INPUT);
  outGate->connectTo(inGate);

  //hidden connection
//  outGate->setDisplayString("ls=,0");

  return 1;
}

//---------------------------------------------------------------------------//
double Core::calculateDistance(int x1, int y1, int x2, int y2)
{
  int x = (x1 - x2) * (x1 - x2);
  int y = (y1 - y2) * (y1 - y2);
  return sqrt(x + y);
}

} /* namespace wsn_energy */
