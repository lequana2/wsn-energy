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
  waitACK = new Frame;
}

void RDCdriver::handleMessage(cMessage *msg)
{

  switch (msg->getKind())
  {
    case LAYER_RDC: /* control message */
    {
      Frame* frame = check_and_cast<Frame*>(msg);

      switch (frame->getTypeMacLayer())
      {
        case LAYER_RDC_WAIT_ACK:
          msg->setKind(LAYER_RDC);
          // NO ACK
          ev << "No ACK" << endl;
          isWaitingACK = false;
          break;
      }
    }
      break; /* control message */

    case LAYER_MAC: /* message from MAC layer */
    {
      Frame* frame = check_and_cast<Frame*>(msg);
      // forward to radio
      frame->setKind(LAYER_RDC);
      frame->setTypeMacLayer(LAYER_RDC_SEND);
      send(frame, gate("lowerOut"));
    }
      break; /* message from MAC layer */

    case LAYER_RADIO: /* message from radio layer */
    {
      Raw *raw = check_and_cast<Raw*>(msg);
      switch (raw->getTypeRadioLayer())
      {
        case LAYER_RADIO_NOT_FREE:
          deferPacket(raw);
          break;

        case LAYER_RADIO_RECV_OK:
          raw->setLen(raw->getLen() - PHY_HEADER);
          receiveSuccess(raw);
          break;
      }
    }
      break; /* message from radio layer */
  }
}

void RDCdriver::finish()
{
}

} /* namespace wsn_energy */
