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

void MACdriver::initialize()
{
  buffer = new FrameMAC;
  buffer->setNote(LAYER_MAC_SEND);
}

void MACdriver::finish()
{
  cancelAndDelete(buffer);
}

void MACdriver::processSelfMessage(cPacket* packet)
{
  switch (check_and_cast<FrameMAC*>(packet)->getNote())
  {
    case CHANNEL_CCA_REQUEST: /* self request CCA */
      sendMessageToLower(packet);
      break; /* request CCA */
  }
}

void MACdriver::processUpperLayerMessage(cPacket* packet)
{
  // free old buffer
  delete buffer->decapsulate();

  // Omnet attribute
  buffer->encapsulate((IpPacket*) packet);
  buffer->setByteLength(packet->getByteLength() + MAC_HEADER_FOOTER_LEN);

  // meta data
  buffer->setNumberTransmission(0);

  // MAC address
  buffer->setSenderMacAddress(this->getId());
  buffer->setRecverMacAddress(getModuleByPath("server.mac")->getId()); // WSN ???

  deferPacket();

  if (DEBUG)
    ev << "Frame length: " << buffer->getByteLength() << endl;
}

void MACdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (check_and_cast<FrameMAC*>(packet)->getNote())
  {
    case CHANNEL_CLEAR: /* channel is clear */
      sendPacket();
      delete packet;
      break; /* channel is clear */

    case CHANNEL_BUSY: /* channel is busy */
      deferPacket();
      delete packet;
      break; /* channel is busy */

    case LAYER_RDC_SEND_OK: /* callback after sending */
    {
      IpPacket* ipPacket = new IpPacket;
      ipPacket->setNote(LAYER_MAC_SEND_OK);
      sendMessageToUpper(ipPacket);

      delete packet;
    }
      break; /* callback after sending */

    case LAYER_RDC_SEND_ERR: /* callback after sending */
    {
      IpPacket* ipPacket = new IpPacket;
      ipPacket->setNote(LAYER_MAC_SEND_ERR);
      sendMessageToUpper(ipPacket);

      delete packet;
    }
      break; /* callback after sending */

    case LAYER_RDC_RECV_OK: /* callback upon reception of a frame */
      receivePacket(check_and_cast<FrameMAC*>(packet));
      break; /* callback upon reception of a frame */
  }
}

void MACdriver::sendPacket()
{
  if (DEBUG)
    ev << "SEND (MAC)" << endl;

  sendMessageToLower(buffer->dup());
}

void MACdriver::receivePacket(FrameMAC* frameMac)
{
  if (DEBUG)
    ev << "RECV (MAC)" << endl;

  IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
  ipPacket->setNote(LAYER_NET_RECV_OK);
  sendMessageToUpper(ipPacket);

  delete frameMac;
}

} /* namespace wsn_energy */
