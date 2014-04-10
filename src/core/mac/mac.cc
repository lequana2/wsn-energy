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
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getKind())
      {
        case CHANNEL_CCA_REQUEST: /* self request CCA */
        {
          sendMessageToLower(packet);
        }
          break; /* request CCA */

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
      /* Command */
    }

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void MACdriver::processUpperLayerMessage(cPacket* packet)
{
  /* only accept data packet */
  /* create new buffer */
  buffer = new FrameMAC;
  buffer->setKind(DATA);
  buffer->setByteLength(MAC_HEADER_FOOTER_LEN);

  /*  meta data */
  buffer->setNumberTransmission(0);

  /* WSN MAC address */
  buffer->setSenderMacAddress(this->getId());
  buffer->setRecverMacAddress(getModuleByPath("server.mac")->getId());

  /* encapsulate */
  buffer->encapsulate((IpPacket*) packet);

  deferPacket();

  if (DEBUG)
    ev << "Frame length: " << buffer->getByteLength() << endl;
}

void MACdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      receivePacket(check_and_cast<FrameMAC*>(packet)); // received message
      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
    } /* Command */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* channel is clear */
        {
          sendPacket();
          break;
        } /* channel is clear */

        case CHANNEL_BUSY: /* channel is busy */
        {
          deferPacket();
          break;
        } /* channel is busy */

        case RDC_SEND_OK: /* callback after sending */
        {
          Result* result = new Result;
          result->setKind(RESULT);
          result->setNote(MAC_SEND_OK);
          sendMessageToUpper(result);
          break;
        } /* callback after sending */

        case RDC_SEND_NO_ACK: /* callback after sending */
        {
          Result* result = new Result;
          result->setKind(RESULT);
          result->setNote(MAC_SEND_NO_ACK);
          sendMessageToUpper(result);
          break;
        } /* callback after sending */

        case RDC_SEND_FATAL: /* callback after sending */
        {
          Result* result = new Result;
          result->setKind(RESULT);
          result->setNote(MAC_SEND_ERROR);
          sendMessageToUpper(result);
          break;
        } /* callback after sending */

        case RDC_SEND_COL: /* callback after sending */
        {
          Result* result = new Result;
          result->setKind(RESULT);
          result->setNote(MAC_SEND_ERROR);
          sendMessageToUpper(result);
          break;
        } /* callback after sending */

        default:
          ev << "Missing note" << endl;
          break;
      }

      delete packet; // done result
      break;
    } /* Result */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void MACdriver::sendPacket()
{
  if (DEBUG)
    ev << "SEND (MAC)" << endl;

  sendMessageToLower(buffer);
}

void MACdriver::receivePacket(FrameMAC* frameMac)
{
  if (DEBUG)
    ev << "RECV (MAC)" << endl;

  IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
  ipPacket->setKind(DATA);
  sendMessageToUpper(ipPacket);

  delete frameMac;
}

} /* namespace wsn_energy */
