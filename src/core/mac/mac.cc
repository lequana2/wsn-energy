/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to mac.h
 */

#include <mac.h>
#include "packet_m.h"
#include "statistic.h"

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
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case MAC_CHECK_BUFFER: /* Check buffer */
        {
          if (DEBUG)
            ev << "SEND (MAC) remaining: " << this->buffer.size() << endl;

          if (this->buffer.size() == 0) // empty
          {
            isHavingPendingPacket = false;
          }
          else if (!isHavingPendingPacket) // In-turn
          {
            this->frameBuffer = this->buffer.front();
            deferPacket(); // begin sending

            isHavingPendingPacket = true;
          }
          break;
        } /* Check buffer */

        case CHANNEL_CCA_REQUEST: /* perform CCA*/
        {
          sendCommand(CHANNEL_CCA_REQUEST);
          break;
        } /* perform CCA */

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
  FrameMAC *frame = new FrameMAC;
  frame->setKind(DATA);
  frame->setByteLength(MAC_HEADER_FOOTER_LEN);

  /*  meta data */
  frame->setNumberTransmission(0);

  /* WSN MAC address */
  frame->setSenderMacAddress(this->getId());
  frame->setRecverMacAddress(getModuleByPath("server.mac")->getId());

  /* encapsulate */
  frame->encapsulate((IpPacket*) packet);

  /* insert into buffer */
  this->buffer.push_back(frame);

  /* check buffer */
  selfTimer(0, MAC_CHECK_BUFFER);

  if (DEBUG)
    ev << "Frame length: " << frame->getByteLength() << endl;
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

        case RDC_SEND_OK: /* WSN callback after sending */
        {
          this->buffer.pop_front();
          isHavingPendingPacket = false;
          selfTimer(0, MAC_CHECK_BUFFER);

          break;
        } /* callback after sending */

        case RDC_SEND_NO_ACK: /* WSN callback after sending */
        {
          // WSN need considering dead neighbor
          sendResult(MAC_SEND_DEAD_NEIGHBOR);

          this->buffer.pop_front();
          isHavingPendingPacket = false;
          selfTimer(0, MAC_CHECK_BUFFER);

          break;
        } /* callback after sending */

        case RDC_SEND_FATAL: /* WSN callback after sending */
        {
          this->buffer.pop_front();
          isHavingPendingPacket = false;
          selfTimer(0, MAC_CHECK_BUFFER);

          break;
        } /* callback after sending */

        case RDC_SEND_COL: /* WSN busy radio, callback after sending */
        {
          this->buffer.pop_front();
          isHavingPendingPacket = false;
          selfTimer(0, MAC_CHECK_BUFFER);

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

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->packetRateTracking(MAC_SEND));

  sendMessageToLower(frameBuffer);
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
