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

#include "mySignal.h"

namespace wsn_energy {

mySignal::mySignal()
{
  this->incompleted = false;
  this->interferred = false;
  this->success = true;
}

mySignal::mySignal(int radioSenderID, int radioRecverID)
{
  mySignal();
  this->radioSenderID = radioSenderID;
  this->radioRecverID = radioRecverID;
}

void mySignal::setInterferred()
{
  this->interferred = true;
  this->success = false;
}

void mySignal::setIncompleted()
{
  this->incompleted = true;
  this->success = false;
}

bool mySignal::isInterferred()
{
  return this->interferred;
}

bool mySignal::isIncomplete()
{
  return this->incompleted;
}

bool mySignal::isSuccess()
{
  return this->success;
}

} /* namespace wsn_energy */
