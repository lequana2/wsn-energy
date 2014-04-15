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
#include "statistic.h"

namespace wsn_energy {

Define_Module(Count);

void Count::initialize()
{
  this->residualEnergy = POWER;
}

void Count::transmit(int numberOfBit)
{
  if (this->residualEnergy > 0)
  {
    this->residualEnergy -= numberOfBit * E_ELEC + numberOfBit * E_FS * D * D;

    if (this->residualEnergy <= 0)
    {
      this->residualEnergy = 0;

      (check_and_cast<RadioDriver*>(getParentModule()->getModuleByPath(".radio")))->switchOscilatorMode(POWER_DOWN);

      char outConnectionName[20];

      int hostID = this->getParentModule()->getId();
      int serverID = simulation.getModuleByPath("server")->getId();

      sprintf(outConnectionName, "out %d to %d", hostID, serverID);

      if (this->getParentModule()->hasGate(outConnectionName)) // has connection to server
      {
        check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->packetRateTracking(
        LIFE_TIME_DECREASE_SERVER_NEIGHBOR);
        std::cout << "Dead node transmits @ " << hostID << endl;
      }
    }
  }
}

void Count::receive(int numberOfBit)
{
  if (this->residualEnergy > 0)
  {
    this->residualEnergy -= numberOfBit * E_ELEC;

    if (this->residualEnergy <= 0)
    {
      this->residualEnergy = 0;

      (check_and_cast<RadioDriver*>(getParentModule()->getModuleByPath(".radio")))->switchOscilatorMode(POWER_DOWN);

      char outConnectionName[20];

      int hostID = this->getParentModule()->getId();
      int serverID = simulation.getModuleByPath("server")->getId();

      sprintf(outConnectionName, "out %d to %d", hostID, serverID);

      if (this->getParentModule()->hasGate(outConnectionName)) // has connection to server
      {
        check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->packetRateTracking(
        LIFE_TIME_DECREASE_SERVER_NEIGHBOR);
        std::cout << "Dead node receives @ " << hostID << endl;
      }
    }
  }
}

} //namespace
