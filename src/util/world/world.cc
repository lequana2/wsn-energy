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
#include "radio.h"

#include <math.h>

#ifndef DEBUG
#define DEBUG 0
#endif

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
  int col = -1; // carry out
  int row = 0;
//  int step = 0;
  int x, y;

  for (int i = 0; i < numberClient; i++)
  {
    switch ((int) getParentModule()->par("topology").doubleValue())
    {
      case 0: /* server at center */
        if (col > 10)
        {
          row++;
          col = 0;
        }
        else
          col++;

        // Partition
        x = col * 25 + 15;
        y = row * 25 + 5;

        // Randomize
        x = uniform(x - 5, x + 5);
        y = uniform(y - 5, y + 5);
        break; /* server at center */

      case 1: /* pyramid */
        break; /* pyramid */
    }

    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    cModule *mote = getParentModule()->getModuleByPath(modulePath);

    mote->par("axisX").setDoubleValue(x);
    mote->par("axisY").setDoubleValue(y);

    oss.seekp(0);
    oss << x << endl;
    (&mote->getDisplayString())->setTagArg("p", 0, oss.str().c_str());

    oss.seekp(0);
    oss << y << endl;
    (&mote->getDisplayString())->setTagArg("p", 1, oss.str().c_str());
  }
}

/*
 * Create connection accords to every node
 */
void World::connectNodes()
{
  // Connect server to other(s)
  RadioDriver *server = (RadioDriver*) simulation.getModuleByPath("server.radio");
  this->checkConnection(server);

  // Connect client(s) to other(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].radio", i);
    this->checkConnection((RadioDriver*) simulation.getModuleByPath(modulePath));
  }
}

/*
 * Create connection from node to others
 */
void World::checkConnection(RadioDriver *radio)
{
  // Check with server
  RadioDriver *server = (RadioDriver*) simulation.getModuleByPath("server.radio");
  if (deployConnection(radio, server))
    radio->neighbor.push_back(server->getParentModule()->getModuleByPath(".radio")->getId());

  // Check with client(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].radio", i);
    RadioDriver *client = (RadioDriver*) simulation.getModuleByPath(modulePath);

    if (deployConnection(radio, client))
      radio->neighbor.push_back(client->getParentModule()->getModuleByPath(".radio")->getId());
  }
}

/*
 * Check and create connection
 */
int World::deployConnection(RadioDriver *x, RadioDriver *y)
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
double World::calculateDistance(RadioDriver *a, RadioDriver *b)
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

void World::registerTransmission(Transmission *tranmission)
{
  if (DEBUG)
    ev << "On air transmision: " << this->onAir.size() << endl;

  RadioDriver* sender = tranmission->getSender();
  RadioDriver* recver = tranmission->getRecver();

  // check receiver turned on
  switch (recver->status)
  {
    case TRANSMITTING:
    case RECEIVING:
    case SLEEPING:
      tranmission->corrupt();
      break;
    case LISTENING:
      recver->status = RECEIVING;
      break;
  }

  this->onAir.push_back(tranmission);

  if (this->onAir.size() == 1)
    return;

//  check collision with activated tranmission
  for (std::list<Transmission*>::iterator otherTranmission = this->onAir.begin(); otherTranmission != this->onAir.end();
      otherTranmission++)
  {
    RadioDriver *otherSender = (*otherTranmission)->getSender();

    // check is same source
    if (otherSender == sender)
      ;
    // check interference
    else
    {
      RadioDriver *otherRecver = (*otherTranmission)->getRecver();

      // at this transmission
      if (tranmission->isCorrupted())
        ;
      else if (calculateDistance((RadioDriver*) otherSender->getParentModule()->getModuleByPath(".radio"),
          (RadioDriver*) recver->getParentModule()->getModuleByPath(".radio"))
          < ((RadioDriver*) otherSender->getParentModule()->getModuleByPath(".radio"))->coRange)
        tranmission->corrupt();

      // at other transmission
      if ((*otherTranmission)->isCorrupted())
        ;
      else if (calculateDistance((RadioDriver*) sender->getParentModule()->getModuleByPath(".radio"),
          (RadioDriver*) otherRecver->getParentModule()->getModuleByPath(".radio"))
          < ((RadioDriver*) sender->getParentModule()->getModuleByPath(".radio"))->coRange)
        (*otherTranmission)->corrupt();
    }
  }

  oss.seekp(0);
  oss << sender->trRange << endl;
  (&sender->getParentModule()->getDisplayString())->setTagArg("r", 0, oss.str().c_str());
}

bool World::isFeasibleTransmission(Transmission* transmission)
{
  RadioDriver* sender = transmission->getSender();
  RadioDriver* recver = transmission->getRecver();

  for (std::list<Transmission*>::iterator otherTranmission = this->onAir.begin(); otherTranmission != this->onAir.end();
      otherTranmission++)
  {
    if (sender == (*otherTranmission)->getSender() && recver == (*otherTranmission)->getRecver()
        && !(*otherTranmission)->isCorrupted())
      return true;
  }

  return false;
}

void World::stopTransmission(Transmission* transmission)
{
  RadioDriver* sender = transmission->getSender();
  RadioDriver* recver = transmission->getRecver();

  for (std::list<Transmission*>::iterator otherTranmission = this->onAir.begin(); otherTranmission != this->onAir.end();
      otherTranmission++)
  {
    if (sender == (*otherTranmission)->getSender() && recver == (*otherTranmission)->getRecver())
    {
      recver->status = LISTENING;
      this->onAir.remove(*otherTranmission);
      (*otherTranmission) = NULL;

      (&sender->getParentModule()->getDisplayString())->setTagArg("r", 0, "0");

      return;
    }
  }

  if (DEBUG)
    ev << "Missing transmission" << endl;
}

bool World::senseBusyTransmission(Transmission *transmission)
{
  RadioDriver* sender = transmission->getSender();

  for (std::list<Transmission*>::iterator otherTranmission = this->onAir.begin(); otherTranmission != this->onAir.end();
      otherTranmission++)
  {
    RadioDriver *otherSender = (*otherTranmission)->getSender();

    if (calculateDistance((RadioDriver*) otherSender->getParentModule()->getModuleByPath(".radio"),
        (RadioDriver*) sender->getParentModule()->getModuleByPath(".radio"))
        < ((RadioDriver*) otherSender->getParentModule()->getModuleByPath(".radio"))->coRange)

      return false;
  }

  if (DEBUG)
    ev << "Clear channel" << endl;

  return true;
}

} /* namespace wsn_energy */
