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

#include <transmission.h>

namespace wsn_energy {
Transmission::Transmission(Mote*sender, Mote*recver)
{
  this->sender = sender;
  this->recver = recver;
  this->collision = false;
}
Mote* Transmission::getSender()
{
  return this->sender;
}
Mote* Transmission::getRecver()
{
  return this->recver;
}
void Transmission::collide()
{
  this->collision = true;
}
bool Transmission::isCollided()
{
  return this->collision;
}
} /* namespace wsn_energy */
