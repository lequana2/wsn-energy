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
      this->sequence++;
      this->buffer->setSequenceNumber(this->sequence);

      if (check_and_cast<FrameMAC*>(packet)->getRecverMacAddress() == 0)
        isSendingBroadcast = true;
      else
        isSendingBroadcast = false;

      this->buffer->encapsulate(packet);

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

        isSendingBroadcast = true;
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
      if (!(check_and_cast<FrameRDC*>(packet))->getIsACK())
      {
        // Check MAC address
        FrameMAC *frameMac = check_and_cast<FrameMAC*>(packet->decapsulate());
        frameMac->setKind(DATA);

        int recverMacID = frameMac->getRecverMacAddress();
        int senderMacID = frameMac->getSenderMacAddress();

        if (recverMacID != 0 && recverMacID != this->getParentModule()->getModuleByPath(".mac")->getId())
        {
          // lost packet, dismiss
          delete frameMac;
        }
        else
        {
          bool isFound = false;

          // search through neighbor list
          for (std::list<SequenceChecking*>::iterator it = this->neighbors.begin(); it != this->neighbors.end(); it++)
          {
            // if found
            if ((*it)->senderID == senderMacID)
            {
              isFound = true;

              // consider sequence number
              if ((*it)->sequence < (check_and_cast<FrameRDC*>(packet)->getSequenceNumber()))
              {
                ((*it))->sequence = check_and_cast<FrameRDC*>(packet)->getSequenceNumber();
                sendMessageToUpper(frameMac);
              }
              else
              {
                // duplicated message, dismiss
                delete frameMac;
              }

              break;
            }
          }

          // if not found
          if (!isFound)
          {
            SequenceChecking *neighbor = new SequenceChecking;
            neighbor->senderID = senderMacID;
            neighbor->sequence = check_and_cast<FrameRDC*>(packet)->getSequenceNumber();

            this->neighbors.push_back(neighbor);

            sendMessageToUpper(frameMac);
          }
        }
      }
      else
      {
        cancelAndDelete(waitForACK);
        isSendingBroadcast = false;

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
          // consider just sends broadcast/unicast data
          if (isSendingBroadcast)
          {
            // consider counter
            if (counter < 3)
            {
              sendMessageToLower(buffer->dup());
              sendCommand(RDC_SEND);

              counter++;
            }
            else
            {
              sendResult(RDC_SEND_OK);
              delete buffer;
            }
          }
          else
          {
            // WSN consider just send data/ack
            // WSN need duty cycling trigger here
            // sendMessageToLower(buffer->dup());
            // sendCommand(RDC_SEND);
            // counter++;
            if (counter < 3)
            {
              sendMessageToLower(buffer->dup());
              sendCommand(RDC_SEND);

              counter++;
            }
            else
            {
              sendResult(RDC_SEND_OK);
              delete buffer;
            }
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
