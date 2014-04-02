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

void RDCdriver::processSelfMessage(cPacket* packet)
{
}

void RDCdriver::processUpperLayerMessage(cPacket* packet)
{
  /* message from MAC layer */
  FrameRDC* frame = new FrameRDC;

  frame->encapsulate(check_and_cast<FrameMAC*>(packet));
  frame->setNote(LAYER_RDC_SEND);

  send(frame, gate("lowerOut"));
  /* message from MAC layer */
}

void RDCdriver::processLowerLayerMessage(cPacket* packet)
{
  /* message from radio layer */
  {
    FrameRDC* frameRdc = check_and_cast<FrameRDC*>(packet);

    switch (frameRdc->getNote())
    {
      case LAYER_RADIO_SEND_OK: /* callback after sending */
      {
        FrameMAC* frameMac = check_and_cast<FrameMAC*>(frameRdc->decapsulate());
        frameMac->setNote(LAYER_RDC_SEND_OK);

        send(frameMac, gate("upperOut"));

        delete frameRdc;
      }
        break; /* callback after sending */

      case LAYER_RADIO_PACKET_OVERSIZE: /* Packet is oversized */
        // WSN Internal error, no need to resend
      {
        FrameMAC* frameMac = check_and_cast<FrameMAC*>(frameRdc->decapsulate());
        frameMac->setNote(LAYER_RDC_SEND_NOT_OK);

        send(frameMac, gate("upperOut"));

        delete frameRdc;
      }
        break; /* Packet is oversized */

      case LAYER_RADIO_CCA_NOT_VALID: /* Packet CCA is not valid */
      {
        FrameMAC* frameMac = check_and_cast<FrameMAC*>(frameRdc->decapsulate());
        frameMac->setNote(LAYER_RDC_SEND_NOT_OK);

        send(frameMac, gate("upperOut"));

        delete frameRdc;
      }
        break; /* Packet CCA is not valid */

      case LAYER_RADIO_NOT_FREE: /* Radio is busy */
      {
        FrameMAC* frameMac = check_and_cast<FrameMAC*>(frameRdc->decapsulate());
        frameMac->setNote(LAYER_RDC_SEND_NOT_OK);

        send(frameMac, gate("upperOut"));

        delete frameRdc;
      }
        break; /* Radio is busy */

      case LAYER_RADIO_RECV_OK: /* Radio received a packet */
      {
        FrameMAC* frameMac = check_and_cast<FrameMAC*>(frameRdc->decapsulate());
        frameMac->setNote(LAYER_RDC_RECV_OK);

        send(frameMac, gate("upperOut"));

        delete frameRdc;
      }
        break; /* Radio received a packet */

      case LAYER_RADIO_RECV_CORRUPT: /* Radio received an incomplete message */
        break; /* Radio received an incomplete message */
    }
  }
  /* message from radio layer */
}

void RDCdriver::on()
{
  FrameRDC *frame = new FrameRDC;
  frame->setNote(LAYER_RDC_LISTEN_ON);

  send(frame, gate("lowerOut"));
}

void RDCdriver::off()
{
  FrameRDC *frame = new FrameRDC;
  frame->setNote(LAYER_RDC_LISTEN_OFF);

  send(frame, gate("lowerOut"));
}

} /* namespace wsn_energy */
