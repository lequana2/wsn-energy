/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to mac.h
 */

#include <mac.h>
#include "packet_m.h"

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

void MACdriver::processSelfMessage(cPacket* packet)
{
}

void MACdriver::processUpperLayerMessage(cPacket* packet)
{
  FrameMAC *frame = new FrameMAC;

  // Omnet attribute
  frame->encapsulate((IpPacket*) packet);
  frame->addByteLength(MAC_HEADER_FOOTER_LEN);

  // MAC address
  frame->setSenderMacAddress(this->getId());
  frame->setRecverMacAddress(getModuleByPath("server.mac")->getId());

  sendPacket(frame);

  if (DEBUG)
    ev << "Frame length: " << frame->getByteLength() << endl;
}

void MACdriver::processLowerLayerMessage(cPacket* packet)
{
  FrameMAC *frameMAC = check_and_cast<FrameMAC*>(packet);

  switch (frameMAC->getNote())
  {
    case LAYER_RDC_SEND_OK: /* callback after sending */
    {
      IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMAC->decapsulate());
      ipPacket->setNote(LAYER_NET_SEND_OK);

      send(ipPacket, gate("upperOut"));

      delete frameMAC;
    }
      break; /* callback after sending */

    case LAYER_RDC_SEND_NOT_OK: /* callback if not able to send*/
    {
      deferPacket(frameMAC);
    }
      break; /* callback if not able to send*/

    case LAYER_RDC_RECV_ACK:
      if (DEBUG)
        ev << "ACK received" << endl;
      break; /* recv ACK */

    case LAYER_RDC_RECV_OK: /* okay message */
      if (DEBUG)
        ev << "RECV (MAC)" << endl;

      IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMAC->decapsulate());
      ipPacket->setNote(LAYER_NET_RECV_OK);

      send(ipPacket, gate("upperOut"));

      delete frameMAC;
      break; /* okay message */
  }
}
} /* namespace wsn_energy */
