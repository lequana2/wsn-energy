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

#include <mac.h>
#include "packet_m.h"

namespace wsn_energy {

void MACdriver::initialize()
{
}

void MACdriver::handleMessage(cMessage *msg)
{
  // Control message
  if (msg->getKind() == LAYER_MAC)
  {
  }
  // From net layer
  else if (msg->getKind() == LAYER_NET)
  {
    ((Frame*) msg)->setLen(((Frame*) msg)->getLen() + 25);
    sendPacket(msg);
  }
  // From rdc layer
  else if (msg->getKind() == LAYER_RDC)
  {
    if (((Frame*) msg)->getTypeMacLayer() == LAYER_MAC_NO_ACK)
    {
      // No ACK
      ev << "No ACK received" << endl;
    }
//    else if (((Frame*) msg)->getTypeMacLayer() != LAYER_RDC_RADIO_NOT_FREE)
//      receivePacket(msg);
  }
}

void MACdriver::finish()
{
}

} /* namespace wsn_energy */
