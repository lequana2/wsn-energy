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
  requestCCA = new FrameMAC;
  requestCCA->setNote(CHANNEL_CCA_REQUEST);

  buffer = new FrameMAC;
  buffer->setNote(LAYER_MAC_SEND);
}

void MACdriver::finish()
{
//  cancelAndDelete(buffer);
//  cancelAndDelete(requestCCA);
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
  // WSN free old buffer (delete after using)
  delete (buffer->decapsulate());

  // Omnet attribute
  buffer->encapsulate((IpPacket*) packet);
  buffer->addByteLength(MAC_HEADER_FOOTER_LEN);

  // meta data
  buffer->setNumberTransmission(0);

  // MAC address
  buffer->setSenderMacAddress(this->getId());
  buffer->setRecverMacAddress(getModuleByPath("server.mac")->getId());

  deferPacket();

  if (DEBUG)
    ev << "Frame length: " << buffer->getByteLength() << endl;
}

void MACdriver::processLowerLayerMessage(cPacket* packet)
{
  FrameMAC *frameMAC = check_and_cast<FrameMAC*>(packet);

  switch (frameMAC->getNote())
  {
    case CHANNEL_CLEAR: /* channel is clear */
      sendPacket();
      break; /* channel is clear */

    case CHANNEL_BUSY: /* channel is busy */
      deferPacket();
      break; /* channel is busy */

    case LAYER_RDC_SEND_OK: /* callback after sending */
    {
      IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMAC->decapsulate());
      ipPacket->setNote(LAYER_NET_SEND_OK);

      send(ipPacket, gate("upperOut"));

      delete frameMAC;
    }
      break; /* callback after sending */

    case LAYER_RDC_RECV_OK: /* callback upon reception of a frame */
      receivePacket(frameMAC);
      break; /* callback upon reception of a frame */
  }
}

void MACdriver::sendPacket()
{
  if (DEBUG)
    ev << "Start transmitting " << endl;

  sendMessageToLower(buffer);
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
