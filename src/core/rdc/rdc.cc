/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rdc.h
 */

#include <rdc.h>
#include "packet_m.h"

namespace wsn_energy {

void RDCdriver::initialize()
{
  this->buffer = new FrameRDC;
  buffer->setNote(LAYER_RDC_SEND);
}

void RDCdriver::finish()
{
  cancelAndDelete(buffer);
}

void RDCdriver::processSelfMessage(cPacket* packet)
{
}

void RDCdriver::processUpperLayerMessage(cPacket* packet)
{
  switch (check_and_cast<FrameMAC*>(packet)->getNote())
  {
    case CHANNEL_CCA_REQUEST: /* request CCA */
    {
      FrameRDC *requestCCA = new FrameRDC;
      requestCCA->setNote(CHANNEL_CCA_REQUEST);
      sendMessageToLower(requestCCA);

      delete packet;
    } /* request CCA */
      break;

    case LAYER_MAC_SEND: /* forward data */
    {
      // Clean old buffer
      delete buffer->decapsulate();
      buffer->encapsulate(packet);

      // WSN need duty cycling trigger here
      sendMessageToLower(buffer->dup());
    }
      break; /* forward data */
  }
}

void RDCdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (check_and_cast<FrameRDC*>(packet)->getNote())
  {
    case CHANNEL_CLEAR: /* Channel is clear */
    {
      FrameMAC* frameMac = new FrameMAC;
      frameMac->setNote(CHANNEL_CLEAR);
      sendMessageToUpper(frameMac);

      delete packet;
    }
      break; /* Channel is busy */

    case CHANNEL_BUSY: /* Channel is clear */
    {
      FrameMAC* frameMac = new FrameMAC;
      frameMac->setNote(CHANNEL_BUSY);
      sendMessageToUpper(frameMac);

      delete packet;
    }
      break; /* Channel is busy */

    case LAYER_RADIO_PACKET_OVERSIZE: /* Packet is oversized */
    {
      // WSN Internal error, no need to resend
      FrameMAC* frameMac = new FrameMAC;
      frameMac->setNote(LAYER_RDC_SEND_ERR);
      sendMessageToUpper(frameMac);

      delete packet;
    }
      break; /* Packet is oversized */

    case LAYER_RADIO_SEND_OK: /* callback after sending */
    {
      FrameMAC* frameMac = new FrameMAC;
      frameMac->setNote(LAYER_RDC_SEND_OK);
      sendMessageToUpper(frameMac);

      delete packet;
    }
      break; /* callback after sending */

    case LAYER_RADIO_RECV_OK: /* Radio received a packet */
    {
      FrameMAC* frameMac = check_and_cast<FrameMAC*>(packet->decapsulate());
      frameMac->setNote(LAYER_RDC_RECV_OK);
      sendMessageToUpper(frameMac);

      delete packet;
    }
      break; /* Radio received a packet */

    case LAYER_RADIO_RECV_NOT_OK: /* Radio received an incomplete message */
      break; /* Radio received an incomplete message */
  }
}

void RDCdriver::on()
{
  FrameRDC *frame = new FrameRDC;
  frame->setNote(LAYER_RDC_LISTEN_ON);
  sendMessageToLower(frame);
}

void RDCdriver::off()
{
  FrameRDC *frame = new FrameRDC;
  frame->setNote(LAYER_RDC_LISTEN_OFF);
  sendMessageToLower(frame);
}

} /* namespace wsn_energy */
