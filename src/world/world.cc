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
    char modulePath[20];
    sprintf(modulePath, "client[%d].app", i);
    App *app = (App*) simulation.getModuleByPath(modulePath);

    // Partition
    app->axisX = (i % 10) * 100 + 20;
    app->axisY = (i / 10) * 100 + 50;
    if ((i / 10) % 2 != 0)
      app->axisX += 50;

    // Randomize
    app->axisX = uniform(app->axisX - 20, app->axisX + 20);
    app->axisY = uniform(app->axisY - 20, app->axisY + 20);

//    EV << i << " " << app->axisX << " " << app->axisY << " " << endl;

    char newDisplay[20];
    sprintf(newDisplay, "p=\%d,\%d;i=misc/node;is=vs", app->axisX, app->axisY);
    app->getParentModule()->setDisplayString(newDisplay);
  }
}

/*
 * Create connection accords to every node
 */
void World::connectNodes()
{
  // Connect server to other(s)
  App *server = (App*) simulation.getModuleByPath("server.app");
  this->checkConnection(server);

  // Connect client(s) to other(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].app", i);
    this->checkConnection((App*) simulation.getModuleByPath(modulePath));
  }
}

/*
 * Create connection from node to others
 */
void World::checkConnection(App *app)
{
// Check with server
  App *server = (App*) simulation.getModuleByPath("server.app");
  if (deployConnection(app, server))
    app->neighbor.push_back(server->getParentModule()->getModuleByPath(".core")->getId());

// Check with client(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].app", i);
    App *module = (App*) simulation.getModuleByPath(modulePath);

    if (deployConnection(app, module))
      app->neighbor.push_back(module->getParentModule()->getModuleByPath(".core")->getId());
  }
}

/*
 * Check and create connection
 */
int World::deployConnection(App *x, App *y)
{
  if (calculateDistance(x, y) > x->trRange)
    return 0;
  if (x->getId() == y->getId())
    return 0;

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
double World::calculateDistance(App *a, App *b)
{
  return this->calculateDistance(a->axisX, a->axisY, b->axisX, b->axisY);
}

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
      else if (calculateDistance((App*) otherSender->getParentModule()->getModuleByPath(".app"),
          (App*) recver->getParentModule()->getModuleByPath(".app"))
          < ((App*) otherSender->getParentModule()->getModuleByPath(".app"))->coRange)
        tranmission->collide();

      // at other transmission
      if ((*otherTranmission)->isCollided())
        ;
      else if (calculateDistance((App*) sender->getParentModule()->getModuleByPath(".app"),
          (App*) otherRecver->getParentModule()->getModuleByPath(".app"))
          < ((App*) sender->getParentModule()->getModuleByPath(".app"))->coRange)
        (*otherTranmission)->collide();
    }
  }
}

bool World::isFeasibleTranmission(Transmission* tranmission)
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

void World::stopTranmission(Transmission* trans)
{
  this->onTheAir.remove(trans);
}

} /* namespace wsn_energy */
