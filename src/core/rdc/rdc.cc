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

#include <rdc.h>

#include "packet_m.h"

namespace wsn_energy {

void RDCdriver::initialize()
{
}

void RDCdriver::handleMessage(cMessage *msg)
{
  // Control message
  if (msg->getKind() == LAYER_RDC)
  {
  }
  // From upper
  else if (msg->getSenderModule()->getId() == getParentModule()->getModuleByPath(".mac")->getId())
  {
    msg->setKind(LAYER_RDC);
    sendPacket(msg);
  }
  // From radio layer
  else if (msg->getKind() == LAYER_RADIO)
  {
    switch (((Raw*) msg)->getTypeRadioLayer())
    {
      case LAYER_RADIO_COL:
        break;

      case LAYER_RADIO_OK:
        recvPacket((Frame*) msg);
        break;
    }
  }
}

void RDCdriver::finish()
{
}

} /* namespace wsn_energy */
