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

#include "nullRadio.h"

#include "world.h"
#include "statistic.h"
#include "energest.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(nullRadio);

bool nullRadio::isClearChannel()
{
  return true;
}

double nullRadio::getTxPower()
{
  return 1;
}

double nullRadio::getRxPower()
{
  return 1;
}

double nullRadio::getIdPower(){
  return 1;
}

} /* namespace wsn_energy */
