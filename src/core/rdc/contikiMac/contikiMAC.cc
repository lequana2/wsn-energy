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

#include "contikiMAC.h"
#include "packet_m.h"

#ifndef  DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(contikiMAC);

void contikiMAC::sendPacket(Frame* frame)
{
  return;
}

void contikiMAC::sendSuccess(Frame* frame)
{
  return;
}

void contikiMAC::sendFailure()
{
  return;
}

void contikiMAC::receiveSuccess(Frame* frame)
{
  return;
}

void contikiMAC::receiveFailure()
{
  return;
}

} /* namespace wsn_energy */
