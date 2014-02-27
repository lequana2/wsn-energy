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

#include "Core.h"

namespace wsn_energy {

Define_Module(Core);

void Core::initialize()
{
  this->numberClient = par("numberClient");
  this->trRange = par("trRange");
  this->ssRange = par("ssRange");
  this->redundancy = par("redundancy");
  this->axisX = par("axisX");
  this->axisY = par("axisY");

  this->hasConnection = new bool[this->numberClient];
  for(int i = 0; i < this->numberClient; i++)
    this->hasConnection = false;

  this->createConnection();
}

void Core::createConnection()
{
//  for(int i = 0; i < this->numberClient; i++){
//    Core *c = (Core*) simulation.getModuleByPath("client");
//    EV << "Neighbour " << c->size() << endl;
//  }
//  for(int i = 3; i <= this->numOfSensors + 2; i++)
//      {
//          Sensor *s = (Sensor *)simulation.getModule(i);
//          double distance = CalculateDistance(this->xPos, this->yPos, s->xPos, s->yPos);
//          if(distance <= trRange)
//          {
//              idNeighbor[numOfNeighbors] = i;
//              numOfNeighbors ++;
//
//              //ket noi
//              char outName[50];
//              char inName[50];
//              cGate *outGate;
//              cGate *inGate;
//              sprintf(outName, "out %d to %d", this->getId(), i);
//              sprintf(inName, "in %d to %d", this->getId(), i);
//              outGate = this->addGate(outName, cGate::OUTPUT);
//              inGate = s->addGate(inName, cGate::INPUT);
//              outGate->connectTo(inGate);
//
//              //hidden connection
//              outGate->setDisplayString("ls=,0");;
//          }
//      }
//      ev << "num neighbor = " << numOfNeighbors << endl;
}

} /* namespace wsn_energy */
