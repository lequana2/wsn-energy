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

  this->hasConnection = new bool[this->numberClient + 1];
  for (int i = 0; i < this->numberClient + 1; i++)
    this->hasConnection[i] = false;

  this->createConnection();
}

//---------------------------------------------------------------------------//
void Core::createConnection()
{
  // Check with server
  Core *module = (Core*) simulation.getModuleByPath("server");
  if(checkConnection(this, module))
    this->hasConnection[0] = true;

  // Check with client(s)
  for (int i = 0; i < this->numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    Core *module = (Core*) simulation.getModuleByPath(modulePath);

    if (checkConnection(this, module))
      this->hasConnection[i + 1] = true;
  }
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

  sprintf(setOutConnectionCommand, "out %d to %d", x->getId(), y->getId());
  sprintf(setInConnectionCommand, "in %d to %d", x->getId(), y->getId());

  cGate *outGate;
  cGate *inGate;

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
