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

#ifndef __WSN_ENERGY_COUNT_H_
#define __WSN_ENERGY_COUNT_H_

#include <omnetpp.h>

#ifndef POWER
#define POWER       100000.0 // 100 mJ
#define E_ELEC         0.005 // 50  nJ
#define E_FS         0.00001 // 10 pJ
#define D                 50 // m
#endif

namespace wsn_energy {

class Count : public cSimpleModule
{
  protected:
    virtual void initialize();

  public:
    double residualEnergy;

    void transmit(int numberOfBit);
    void receive(int numberOfBit);

};

} //namespace

#endif
