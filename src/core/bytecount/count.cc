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

#include "count.h"
#include "radio.h"

namespace wsn_energy {

Define_Module(Count);

void Count::initialize()
{
  this->residualEnergy = POWER;
}

void Count::transmit(int numberOfBit)
{
  this->residualEnergy -= numberOfBit * E_ELEC + numberOfBit * E_FS * D * D;

  if (this->residualEnergy < 0)
    (check_and_cast<RadioDriver*>(getParentModule()->getModuleByPath(".radio")))->switchOscilatorMode(POWER_DOWN);
}

void Count::receive(int numberOfBit)
{
  this->residualEnergy -= numberOfBit * E_ELEC;

  if (this->residualEnergy < 0)
    (check_and_cast<RadioDriver*>(getParentModule()->getModuleByPath(".radio")))->switchOscilatorMode(POWER_DOWN);
}

} //namespace
