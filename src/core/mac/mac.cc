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

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

void MACdriver::initialize()
{
}

void MACdriver::handleMessage(cMessage *msg)
{
  switch (msg->getKind())
  {
    case LAYER_MAC: /* control message */
      break; /* control message */

    case LAYER_NET: /* message from NET layer */
    {
      FrameMAC *frame = new FrameMAC;

      // Omnet attribute
      frame->setKind(LAYER_MAC);
      frame->encapsulate((IpPacket*) msg);
      frame->addByteLength(MAC_HEADER_FOOTER_LEN);

      // MAC address
      frame->setSenderMacAddress(this->getId());
      frame->setRecverMacAddress(getModuleByPath("server.mac")->getId());

      if (DEBUG)
        ev << "Frame length: " << frame->getByteLength() << endl;

      sendPacket(frame);
    }
      break; /* message from NET layer */

    case LAYER_RDC: /* message from MAC layer */
    {
      FrameMAC *frameMac = check_and_cast<FrameMAC*>(msg);

      switch (frameMac->getNote())
      {
        case LAYER_RDC_SEND_OK: /* callback after sending */
        {
          IpPacket* ipPacket = new IpPacket;

          ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
          ipPacket->setKind(LAYER_MAC);
          ipPacket->setNote(LAYER_NET_SEND_OK);
          send(ipPacket, gate("upperOut"));
        }
          break; /* callback after sending */

        case LAYER_RDC_SEND_NOT_OK: /* callback if not able to send*/
          deferPacket(frameMac);
          break;

        case LAYER_RDC_RECV_ACK:
          if (DEBUG)
            ev << "ACK received" << endl;
          break; /* recv ACK */

        case LAYER_RDC_RECV_OK:
          if (DEBUG)
            ev << "RECV (MAC)" << endl;

          IpPacket* ipPacket = new IpPacket;

          ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
          ipPacket->setKind(LAYER_MAC);
          ipPacket->setNote(LAYER_MAC_RECV_OK);

          send(ipPacket, gate("upperOut"));
          break; /* okay message */
      }
    }
      break; /* message from MAC layer */
  }
}

void MACdriver::finish()
{
}

} /* namespace wsn_energy */
