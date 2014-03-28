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
  waitACK = new FrameRDC;
}

void RDCdriver::handleMessage(cMessage *msg)
{
  switch (msg->getKind())
  {
    case LAYER_RDC: /* control message */
    {
//      FrameRDC* frame = check_and_cast<FrameRDC*>(msg);
//      // WSN ACK
//      switch (frame->getCommandRdcLayer())
//      {
//        case LAYER_RDC_WAIT_ACK:
//          msg->setKind(LAYER_RDC);
//          // NO ACK
//          ev << "No ACK" << endl;
//          isWaitingACK = false;
//          break;
//      }
    }
      break; /* control message */

    case LAYER_MAC: /* message from MAC layer */
    {
      FrameRDC* frame = new FrameRDC;

      frame->encapsulate(check_and_cast<FrameMAC*>(msg));
      frame->setKind(LAYER_RDC);
      frame->setNote(LAYER_RDC_SEND);

      send(frame, gate("lowerOut"));
    }
      break; /* message from MAC layer */

    case LAYER_RADIO: /* message from radio layer */
    {
      FrameRDC* frameRdc = check_and_cast<FrameRDC*>(msg);
      frameRdc->setKind(LAYER_RDC);

      switch (frameRdc->getNote())
      {
        case LAYER_RADIO_SEND_OK: /* callback after sending */
//          raw->setKind(LAYER_RDC);
//          ((Frame*) raw)->setTypeMacLayer(LAYER_RDC_SEND_OK);
//          send(raw, gate("upperOut"));
          break; /* callback after sending */

        case LAYER_RADIO_CCA_NOT_VALID: /* Packet CCA is not valid */
          break; /* Packet CCA is not valid */

        case LAYER_RADIO_PACKET_OVERSIZE: /* Packet is oversized */
          break; /* Packet is oversized */

        case LAYER_RADIO_NOT_FREE: /* Radio is busy */
//          deferPacket(raw);
          break; /* Radio is busy */

        case LAYER_RADIO_RECV_OK: /* Radio received a packet */
        {
          FrameMAC* frameMac = new FrameMAC;

          frameMac = check_and_cast<FrameMAC*>(frameRdc->decapsulate());
          frameMac->setKind(LAYER_RDC);
          frameMac->setNote(LAYER_RDC_RECV_OK);

//          receiveSuccess(frame);
          send(frameMac, gate("upperOut"));
        }
          break; /* Radio received a packet */

        case LAYER_RADIO_RECV_CORRUPT:
          break;
      }
    }
      break; /* message from radio layer */
  }
}

void RDCdriver::finish()
{
  cancelAndDelete(waitACK);
}

} /* namespace wsn_energy */
