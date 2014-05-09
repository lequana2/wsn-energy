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

namespace wsn_energy {

void RDCdriver::initialize()
{
  // intitialisation
  isOnAnTranssmissionPhase = false;
  isOnAnCheckingPhase = false;
  ccaCounter = 0;

  // start channel check timer
  if (getParentModule()->getId() != simulation.getModuleByPath("server")->getId())
    selfTimer(0, RDC_CHANNEL_CHECK);
}

void RDCdriver::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RDC_CHANNEL_CHECK: /* channel check */
        {
          if (ccaCounter == 0) // starting a new checking phase
          {
            // WSN consider is on old checking session
            // WSN consider is on transmission session

            // acquire checking phase
            isOnAnCheckingPhase = true;
            ccaCounter = CCA_COUNT_MAX;

            // start checking phase
            selfTimer(0, RDC_CHANNEL_CHECK);
          }
          else // next cca
          {
            // decrease cca counter
            ccaCounter--;

            // turn on radio
            on();

            // begin CCA indicator
            sendCommand(RDC_CCA_REQUEST);
          }
          break;
        } /* channel check*/

        case RDC_SEND_FRAME: /* send frame */
        {
          send();
          break;
        } /* send frame */

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
      switch ((check_and_cast<Frame*>(packet))->getFrameType())
      {
        case FRAME_DATA:
          // WSN begin a transmission phase
          this->buffer = check_and_cast<Frame*>(packet->dup()); // write to buffer

          // WSN acquire transmitting phases
          isOnAnTranssmissionPhase = true;

          // WSN begin transmission phase
          // WSN acquire phase lock
          // WSN cca
          // WSN send frame

          break;
      }
      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case MAC_CCA_REQUEST: /* request CCA */
        {
          sendCommand(RDC_CCA_REQUEST);
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
//    case DATA: /* Data */
//    {
//      Frame *frame = check_and_cast<Frame*>(packet);
//
//      // not an ACK, packet must be ICMP (broadcast) or data (unicast)
//      if (!frame->getIsACK())
//      {
//        // Check MAC address
//        int recverMacID = frame->getRecverMacAddress();
//        int senderMacID = frame->getSenderMacAddress();
//
//        // unicast + wrong MAC address
//        if (recverMacID != 0 && recverMacID != this->getParentModule()->getModuleByPath(".mac")->getId())
//        {
//          // lost packet (! broadcast and wrong mac address) dismiss
//          delete packet;
//        }
//        else
//        {
//          // check if receiving duplicated package
//          bool isFound = false;
//
//          // search through neighbor list
//          for (std::list<Neighbor*>::iterator it = this->neighbors.begin(); it != this->neighbors.end(); it++)
//          {
//            // if neighbor in MAC-IP table
//            if ((*it)->senderID == senderMacID)
//            {
//              isFound = true;
//
//              // consider sequence number
//              if ((*it)->sequence < frame->getSequenceNumber())
//              {
//                ((*it))->sequence = frame->getSequenceNumber();
//                sendMessageToUpper(frame);
//              }
//              else
//              {
//                // duplicated message, dismiss
//                delete packet;
//              }
//
//              break;
//            }
//          }
//
//          // if neighbor not in MAC-IP table, create new
//          if (!isFound)
//          {
//            Neighbor *neighbor = new Neighbor;
//            neighbor->senderID = senderMacID;
//            neighbor->sequence = frame->getSequenceNumber();
//
//            this->neighbors.push_back(neighbor);
//
//            sendMessageToUpper(frame);
//          }
//        }
//      }
//      // is ACK
//      else
//      {
//        // WSN consider ACK, delete before cancel ?
//        delete packet;
//
//        sendResult(RDC_SEND_OK); // send success
//      }
//      break;
//    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* Channel is clear */
        {
          // consider is on checking phase/MAC request
          if (isOnAnCheckingPhase)
          {
            // WSN is switch to transmission phase ?

            // not seen
            off();

            // consider if last cca
            if (ccaCounter == 0)
            {
              // release checking phase
              isOnAnCheckingPhase = false;

              // schedule next checking phase
              selfTimer(CHANNEL_CHECK_INTERVAL, RDC_CHANNEL_CHECK);
            }
            else
            {
              // schedule next cca
              selfTimer(CCA_SLEEP_TIME, RDC_CHANNEL_CHECK);
            }
          }
          else if (isOnAnTranssmissionPhase)
          {
            // WSN clear
            // WSN send
          }
          else
          {
            // send result back to MAC layer
            sendResult(CHANNEL_CLEAR);

            // turn off radio
            off();
          }
          break;
        } /* Channel is busy */

        case CHANNEL_BUSY: /* Channel is clear */
        {
          // consider is on checking phase/MAC request
          if (isOnAnCheckingPhase)
          {
            // WSN is switch to transmission phase ?
            // WSN seen
            // WSN continue listening
            // WSN if listening to message, then receive and off and send ACK
            // WSN if listening to noise, then after timeout then perform new interval
          }
          else if (isOnAnTranssmissionPhase)
          {
            // WSN seen
            // WSN backoff
          }
          else
          {
            // send result back to MAC layer
            sendResult(CHANNEL_BUSY);

            // turn off radio
            off();
          }
          break;
        }/* Channel is busy */

        case PHY_TX_ERR: /* Internal error */
        {
          sendResult(RDC_SEND_FATAL);
          break;
        }/* Internal error */

        case PHY_TX_OK: /* callback after transmitting */
        {
          // WSN consider just sends broadcast data
          if (true)
          {
            // consider counter
//            if (++selfSequenceNumber < CONTIKI_MAC_REDUNDANCY)
//            {
//              // WSN hack need implementing duty cycling here
//              sendMessageToLower(buffer->dup());
//              sendCommand(RDC_TRANSMIT);
//            }
//            // hack
//            else
//            {
//              // broadcast message always succeed !!!
//              sendResult(RDC_SEND_OK);
//              // WSN intermediate switch to listen mode
//              on();
//              delete buffer;
//            }
          }
          // WSN consider just send unicast (data/ack)
          else
          {
//            if (++selfSequenceNumber < CONTIKI_MAC_REDUNDANCY)
//            {
//              // WSN hack need implementing duty cycling here
//              sendMessageToLower(buffer->dup());
//              sendCommand(RDC_TRANSMIT);
//            }
//            else
//            {
//              // WSN hack, given the TX range 100%, ACK only lost if the sender node energy is too low
////              if (check_and_cast<Count*>(
////                  simulation.getModule(
////                      check_and_cast<IpPacket*>(this->buffer->getEncapsulatedPacket())->getRecverIpAddress())->getModuleByPath(
////                      "^.count"))->residualEnergy == 0)
////                sendResult(RDC_SEND_NO_ACK);
////              else
////                sendResult(RDC_SEND_OK);
////
////              on();
//              delete buffer;
//            }
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

void RDCdriver::send()
{
  sendMessageToLower(this->buffer->dup());
  sendCommand(RDC_TRANSMIT);
}

void RDCdriver::on()
{
  sendCommand(RDC_LISTEN);
}

void RDCdriver::off()
{
  // Server never sleep after listening/receiving and transmittingsession either
  if (getId() == simulation.getModuleByPath("server.rdc")->getId())
    return;

  sendCommand(RDC_IDLE);
}

} /* namespace wsn_energy */
