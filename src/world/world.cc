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

#include "world.h"

#include <math.h>

namespace wsn_energy {

Define_Module(World);

void World::initialize()
{
  this->numberClient = par("numberClient");

  // Arrange nodes into positions
  arrangeNodes();

  // Create connections
  connectNodes();
}

void World::handleMessage(cMessage *msg)
{
}

/*
 * Arrange position of nodes in network.
 */
void World::arrangeNodes()
{
  for (int i = 0; i < numberClient; i++)
  {
    int x, y;

    // Partition
    x = (i % 10) * 100 + 20;
    y = (i / 10) * 100 + 50;

    if ((i / 10) % 2 != 0)
      x += 50;

    // Randomize
    x = uniform(x - 20, x + 20);
    y = uniform(y - 20, y + 20);

    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    cModule *mote = getParentModule()->getModuleByPath(modulePath);

    mote->par("axisX").setDoubleValue(x);
    mote->par("axisY").setDoubleValue(y);

//    x = mote->par("axisX");
//    y = mote->par("axisY");
//    ev << i << " " << x << " " << y << " " << endl;

    char newDisplay[20];
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", x, y);
    mote->setDisplayString(newDisplay);
  }
}

/*
 * Create connection accords to every node
 */
void World::connectNodes()
{
  // Connect server to other(s)
  Radio *server = (Radio*) simulation.getModuleByPath("server.radio");
  this->checkConnection(server);

  // Connect client(s) to other(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].radio", i);
    this->checkConnection((Radio*) simulation.getModuleByPath(modulePath));
  }
}

/*
 * Create connection from node to others
 */
void World::checkConnection(Radio *radio)
{
  // Check with server
  Radio *server = (Radio*) simulation.getModuleByPath("server.radio");
  if (deployConnection(radio, server))
    radio->neighbor.push_back(server->getParentModule()->getModuleByPath(".radio")->getId());

  // Check with client(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].radio", i);
    Radio *client = (Radio*) simulation.getModuleByPath(modulePath);

    if (deployConnection(radio, client))
      radio->neighbor.push_back(client->getParentModule()->getModuleByPath(".radio")->getId());
  }
}

/*
 * Check and create connection
 */
int World::deployConnection(Radio *x, Radio *y)
{
  if (calculateDistance(x, y) > x->trRange)
    return 0;
  if (x->getId() == y->getId())
    return 0;

  // set up connection
  char setOutConnectionName[20];
  char setInConnectionName[20];

  cGate *outGate;
  cGate *inGate;

  sprintf(setOutConnectionName, "out %d to %d", x->getParentModule()->getId(), y->getParentModule()->getId());
  sprintf(setInConnectionName, "in %d to %d", x->getParentModule()->getId(), y->getParentModule()->getId());

  outGate = x->getParentModule()->addGate(setOutConnectionName, cGate::OUTPUT);
  inGate = y->getParentModule()->addGate(setInConnectionName, cGate::INPUT);

  outGate->connectTo(inGate);

  //hidden connection
  outGate->setDisplayString("ls=,0");

  return 1;
}

/*
 * Calculate distance util
 */
double World::calculateDistance(Radio *a, Radio *b)
{
  int x1 = a->getParentModule()->par("axisX");
  int y1 = a->getParentModule()->par("axisY");
  int x2 = b->getParentModule()->par("axisX");
  int y2 = b->getParentModule()->par("axisY");

  return this->calculateDistance(x1, y1, x2, y2);
}

/*
 * Calculate distance util
 */
double World::calculateDistance(int x1, int y1, int x2, int y2)
{
  int x = (x1 - x2) * (x1 - x2);
  int y = (y1 - y2) * (y1 - y2);
  return sqrt(x + y);
}

void World::registerTranmission(Transmission *tranmission)
{
  this->onTheAir.push_back(tranmission);

  if (this->onTheAir.size() == 1)
    return;

  Radio* sender = tranmission->getSender();
  Radio* recver = tranmission->getRecver();

//  check collision with activated tranmission
  for (std::list<Transmission*>::iterator otherTranmission = this->onTheAir.begin();
      otherTranmission != this->onTheAir.end(); otherTranmission++)
  {
    Radio *otherSender = (*otherTranmission)->getSender();

    // check is same source
    if (otherSender == sender)
      ;
    // check interference
    else
    {
      Radio *otherRecver = (*otherTranmission)->getRecver();

      // at this transmission
      if (tranmission->isCollided())
        ;
      else if (calculateDistance((Radio*) otherSender->getParentModule()->getModuleByPath(".radio"),
          (Radio*) recver->getParentModule()->getModuleByPath(".radio"))
          < ((Radio*) otherSender->getParentModule()->getModuleByPath(".radio"))->coRange)
        tranmission->collide();

      // at other transmission
      if ((*otherTranmission)->isCollided())
        ;
      else if (calculateDistance((Radio*) sender->getParentModule()->getModuleByPath(".radio"),
          (Radio*) otherRecver->getParentModule()->getModuleByPath(".radio"))
          < ((Radio*) sender->getParentModule()->getModuleByPath(".radio"))->coRange)
        (*otherTranmission)->collide();
    }
  }
}

bool World::isFeasibleTranmission(Transmission* tranmission)
{
  if (this->onTheAir.size() == 1)
    return true;

  Radio* sender = tranmission->getSender();
  Radio* recver = tranmission->getRecver();

  for (std::list<Transmission*>::iterator otherTranmission = this->onTheAir.begin();
      otherTranmission != this->onTheAir.end(); otherTranmission++)
  {
    if (sender == (*otherTranmission)->getSender() && recver == (*otherTranmission)->getRecver()
        && !(*otherTranmission)->isCollided())
      return true;
  }

  return false;
}

void World::stopTranmission(Transmission* transmission)
{
  this->onTheAir.remove(transmission);
}

} /* namespace wsn_energy */
