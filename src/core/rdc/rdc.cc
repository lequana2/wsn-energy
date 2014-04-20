/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rdc.h
 */

#include <rdc.h>
#include "packet_m.h"
#include "count.h"

#ifndef CONTIKI_MAC_REDUNDANCY
#define CONTIKI_MAC_REDUNDANCY 1
#endif

namespace wsn_energy {

void RDCdriver::initialize()
{
  isSendingBroadcast = true;
  isWaitingACK = false;
  sequence = 0;
}

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
          // WSN reset parameter, prepare for new transmitting
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
      counter = 0;

      this->buffer = check_and_cast<Frame*>(packet->dup()); // duplicate buffer
      this->buffer->setKind(DATA);
      this->buffer->setIsACK(false);
      this->sequence++;
      this->buffer->setSequenceNumber(this->sequence);

      // consider broadcast or unicast
      if (this->buffer->getRecverMacAddress() == 0)
      {
        isSendingBroadcast = true;
      }
      else
      {
        isSendingBroadcast = false;

        // WSN expire time to receive ACK
//        waitForACK = new Command;
//        waitForACK->setKind(COMMAND);
//        waitForACK->setNote(RDC_WAIT_FOR_ACK);
//        scheduleAt(0, waitForACK);
      }

      // send to lower
      sendMessageToLower(buffer->dup());
      sendCommand(RDC_TRANSMIT);

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
      Frame *frame = check_and_cast<Frame*>(packet);

      // not an ACK, packet must be ICMP (broadcast) or data (unicast)
      if (!frame->getIsACK())
      {
        // Check MAC address
        int recverMacID = frame->getRecverMacAddress();
        int senderMacID = frame->getSenderMacAddress();

        // unicast + wrong MAC address
        if (recverMacID != 0 && recverMacID != this->getParentModule()->getModuleByPath(".mac")->getId())
        {
          // lost packet (! broadcast and wrong mac address) dismiss
          delete packet;
        }
        else
        {
          // check if receiving duplicated package
          bool isFound = false;

          // search through neighbor list
          for (std::list<Neighbor*>::iterator it = this->neighbors.begin(); it != this->neighbors.end(); it++)
          {
            // if neighbor in MAC-IP table
            if ((*it)->senderID == senderMacID)
            {
              isFound = true;

              // consider sequence number
              if ((*it)->sequence < frame->getSequenceNumber())
              {
                ((*it))->sequence = frame->getSequenceNumber();
                sendMessageToUpper(frame);
              }
              else
              {
                // duplicated message, dismiss
                delete packet;
              }

              break;
            }
          }

          // if neighbor not in MAC-IP table, create new
          if (!isFound)
          {
            Neighbor *neighbor = new Neighbor;
            neighbor->senderID = senderMacID;
            neighbor->sequence = frame->getSequenceNumber();

            this->neighbors.push_back(neighbor);

            sendMessageToUpper(frame);
          }
        }
      }
      // is ACK
      else
      {
        // WSN consider ACK, delete before cancel ?
        delete packet;

        sendResult(RDC_SEND_OK); // send success
      }
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
          // consider just sends broadcast data
          if (isSendingBroadcast)
          {
            // consider counter
            if (++counter < CONTIKI_MAC_REDUNDANCY)
            {
              // WSN hack need implementing duty cycling here
              sendMessageToLower(buffer->dup());
              sendCommand(RDC_TRANSMIT);
            }
            // hack
            else
            {
              // broadcast message always succeed !!!
              sendResult(RDC_SEND_OK);
              on();
              delete buffer;
            }
          }
          // WSN consider just send unicast (data/ack)
          else
          {
            if (++counter < CONTIKI_MAC_REDUNDANCY)
            {
              // WSN hack need implementing duty cycling here
              sendMessageToLower(buffer->dup());
              sendCommand(RDC_TRANSMIT);
            }
            else
            {
              // WSN hack, given the TX range 100%, ACK only lost if the sender node energy is too low
              if (check_and_cast<Count*>(
                  simulation.getModule(
                      check_and_cast<IpPacket*>(this->buffer->getEncapsulatedPacket())->getRecverIpAddress())->getModuleByPath(
                      "^.count"))->residualEnergy == 0)
                sendResult(RDC_SEND_NO_ACK);
              else
                sendResult(RDC_SEND_OK);

              on();
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
