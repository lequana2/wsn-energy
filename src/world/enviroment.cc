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

#include <enviroment.h>

#include "moteClient.h"
#include "moteServer.h"

namespace wsn_energy {

Define_Module(Enviroment);

void Enviroment::initialize()
{
  this->numberClient = par("numberClient");

  // Arrange nodes into positions
  arrangeNodes();

// Create connections
//  connectNodes();
}

void Enviroment::handleMessage(cMessage *msg)
{
}

/*
 * Arrange position of nodes in network.
 */
void Enviroment::arrangeNodes()
{
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    MoteClient *mote = (MoteClient*) simulation.getModuleByPath(modulePath);

    // Partition
    mote->axisX = (i % 10) * 100 + 15;
    mote->axisY = (i / 10) * 100 + 50;
    if ((i / 10) % 2 != 0)
      mote->axisX += 50;

    // Randomize
    mote->axisX = uniform(mote->axisX - 20, mote->axisX + 20);
    mote->axisY = uniform(mote->axisY - 20, mote->axisY + 20);

    EV << i << " " << mote->axisX << " " << mote->axisY << " " << endl;

    char newDisplay[20];
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", mote->axisX, mote->axisY);
    mote->setDisplayString(newDisplay);
  }
}

/*
 * Create connection accords to every node
 */
void Enviroment::connectNodes()
{
  Core *server = (Core*) simulation.getModuleByPath("server");
  this->checkConnection(server);

  for (int i = 0; i < server->numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    this->checkConnection((Core*) simulation.getModuleByPath(modulePath));
  }
}

/*
 * Create connection from node to others
 */
void Enviroment::checkConnection(Core *core)
{
// Check with server
  Core *module = (Core*) simulation.getModuleByPath("server");
  if (deployConnection(core, module))
    core->neighbor.push_back(module->getId());

// Check with client(s)
  for (int i = 0; i < core->numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    Core *module = (Core*) simulation.getModuleByPath(modulePath);

    if (deployConnection(core, module))
      core->neighbor.push_back(module->getId());
  }
}

int Enviroment::deployConnection(Core *x, Core *y)
{
  if (calculateDistance(x->axisX, x->axisY, y->axisX, y->axisY) > x->trRange)
    return 0;
  if (x->getId() == y->getId())
    return 0;

  char setOutConnectionName[20];
  char setInConnectionName[20];
  cGate *outGate;
  cGate *inGate;

  sprintf(setOutConnectionName, "out %d to %d", x->getId(), y->getId());
  sprintf(setInConnectionName, "in %d to %d", x->getId(), y->getId());

  outGate = x->addGate(setOutConnectionName, cGate::OUTPUT);
  inGate = y->addGate(setInConnectionName, cGate::INPUT);

  //WSN create channel
  cDatarateChannel *channel = cDatarateChannel::create(NULL);
//  channel->setDatarate(250000);
//  channel->setDelay(1);

  outGate->connectTo(inGate, channel);
  channel->callInitialize();

  //hidden connection
  outGate->setDisplayString("ls=,0");

  return 1;
}

double Enviroment::calculateDistance(Core *a, Core *b)
{
  return this->calculateDistance(a->axisX, a->axisY, b->axisX, b->axisY);
}

double Enviroment::calculateDistance(int x1, int y1, int x2, int y2)
{
  int x = (x1 - x2) * (x1 - x2);
  int y = (y1 - y2) * (y1 - y2);
  return sqrt(x + y);
}

void Enviroment::registerTranmission(Transmission *tranmission)
{
  this->onTheAir.push_back(tranmission);

  if (this->onTheAir.size() == 1)
    return;

  Core* sender = tranmission->getSender();
  Core* recver = tranmission->getRecver();

//  check collision with activated tranmission
  for (std::list<Transmission*>::iterator otherTranmission = this->onTheAir.begin();
      otherTranmission != this->onTheAir.end(); otherTranmission++)
  {
    Core *otherSender = (*otherTranmission)->getSender();

    // check is same source
    if (otherSender == sender)
      ;
    // check interference
    else
    {
      Core *otherRecver = (*otherTranmission)->getRecver();

      // at this transmission
      if (tranmission->isCollided())
        ;
      else if (calculateDistance(otherSender, recver) < otherSender->coRange)
        tranmission->collide();

      // at other transmission
      if ((*otherTranmission)->isCollided())
        ;
      else if (calculateDistance(sender, otherRecver) < sender->coRange)
        (*otherTranmission)->collide();
    }
  }
}

bool Enviroment::isFeasibleTranmission(Transmission* tranmission)
{
  if (this->onTheAir.size() == 1)
    return true;

  Core* sender = tranmission->getSender();
  Core* recver = tranmission->getRecver();

  for (std::list<Transmission*>::iterator otherTranmission = this->onTheAir.begin();
      otherTranmission != this->onTheAir.end(); otherTranmission++)
  {
    if (sender == (*otherTranmission)->getSender() && recver == (*otherTranmission)->getRecver()
        && !(*otherTranmission)->isCollided())
      return true;
  }

  return false;
}

void Enviroment::stopTranmission(Transmission* trans)
{
  this->onTheAir.remove(trans);
}

} /* namespace wsn_energy */
