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
  Frame *frame = check_and_cast<Frame*>(msg);

  switch (frame->getKind())
  {
    case LAYER_MAC: /* control message */
      break; /* control message */

    case LAYER_NET: /* message from NET layer */
      sendPacket(frame);
      break; /* message from NET layer */

    case LAYER_RDC: /* message from MAC layer */
      switch(frame->getTypeMacLayer()){
        case LAYER_RDC_RECV_ACK:
          ev << "No ACK received" << endl;
          break; /* recv ACK */

        case LAYER_RDC_RECV_OK:
          frame->setKind(LAYER_MAC);
          frame->setTypeMacLayer(LAYER_MAC_RECV_OK);
          send(frame, gate("upperOut"));
          break; /* okay message */
      }

      break; /* message from MAC layer */
  }
}

void MACdriver::finish()
{
}

} /* namespace wsn_energy */
