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

#include <radio.h>

namespace wsn_energy {

Define_Module(Radio)

void Radio::initialize()
{
  this->trRange = par("trRange");
  this->coRange = par("coRange");
}

void Radio::handleMessage(cMessage* msg)
{
  if (msg->getKind() == TRX_BROADCAST)
  {
    ev << "Trans on" << endl;
  }
  else if (msg->getKind() == RCX_BROADCAST)
  {
    ev << "Recv on" << endl;
  }
  else if (msg->getKind() == END_BROADCAST)
  {
    ev << "Turn off" << endl;
  }
}

void Radio::finish()
{
}

void Radio::transmit_on()
{
}

void Radio::receive_on()
{
}
void Radio::transmit_off()
{
}

void Radio::receive_off()
{
}
}
/* namespace wsn_energy */
