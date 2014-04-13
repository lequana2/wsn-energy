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
  // WSN send + recv ACK
  // RDC_SEND_OK     = 0; // send + receive ACK (if needed)
  // RDC_SEND_NO_ACK = 1; // sent + no ACK (if needed)
  // RDC_SEND_FATAL  = 2; // fatal error, abort message
  // RDC_SEND_COL    = 3; // collision with PHY

  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RDC_WAIT_FOR_ACK: /*no ACK*/
        {
          isWaitingACK = false;
          sendResult(RDC_SEND_NO_ACK);

          break;
        }/* no ACK */

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
    } /* Command */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void RDCdriver::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      this->buffer = new FrameRDC;
      this->buffer->setKind(DATA);
      this->buffer->setIsACK(false);

      this->buffer->encapsulate(packet);

      // WSN need duty cycling trigger here
      sendMessageToLower(buffer->dup());
      sendCommand(RDC_SEND);

      counter = 0;

      // WSN unicast = waiting for ACK
      if (false)
      {
        waitForACK = new Command;
        waitForACK->setKind(COMMAND);
        waitForACK->setNote(RDC_WAIT_FOR_ACK);
        scheduleAt(0, waitForACK);

        isWaitingACK = true;
      }

      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case CHANNEL_CCA_REQUEST: /* request CCA */
        {
          sendCommand(CHANNEL_CCA_REQUEST);
          break;
        } /* request CCA */

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
    } /* Command */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void RDCdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      // WSN consider ACK or not
      if (true)
      {
        FrameMAC *frameMac = check_and_cast<FrameMAC*>(packet->decapsulate());
        frameMac->setKind(DATA);
        sendMessageToUpper(frameMac);
      }
      else
      {
        cancelAndDelete(waitForACK);
        isWaitingACK = false;

        sendResult(RDC_SEND_OK); // send success
      }

      delete packet;
      break;
    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* Channel is clear */
        {
          sendResult(CHANNEL_CLEAR);
          break;
        } /* Channel is busy */

        case CHANNEL_BUSY: /* Channel is clear */
        {
          sendResult(CHANNEL_BUSY);
          break;
        }/* Channel is busy */

        case PHY_TX_ERR: /* Internal error */
        {
          sendResult(RDC_SEND_FATAL);
          break;
        }/* Internal error */

        case PHY_TX_OK: /* callback after transmitting */
        {
          // WSN consider just sends data or ACK
          if (true)
          {
            sendResult(RDC_SEND_OK);
            delete buffer;
          }
          else
          {
            // WSN need duty cycling trigger here
            sendMessageToLower(buffer->dup());
            sendCommand(RDC_SEND);
            counter++;
          }
          break;
        }/* callback after transmitting */

        default:
          ev << "Unknown result" << endl;
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

void RDCdriver::on()
{
  sendCommand(RDC_LISTEN);
}

void RDCdriver::off()
{
  sendCommand(RDC_IDLE);
}

} /* namespace wsn_energy */
