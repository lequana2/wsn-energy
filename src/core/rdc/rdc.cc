/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rdc.h
 */

#include <rdc.h>
#include "mac.h"
#include "packet_m.h"
#include "signal_m.h"
#include "count.h"

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

void RDCdriver::initialize()
{
  // intitialisation
  this->buffer = NULL;
  this->isHavingPendingTransmission = false;
  this->isJustSendACK = false;

  this->phase = FREE_PHASE;
  this->ccaCounter = 0;

  ccaTimeOut = new Command;
  ccaTimeOut->setKind(COMMAND);
  ccaTimeOut->setNote(RDC_CCA_TIME_OUT);

  phaseTimeOut = new Command;
  phaseTimeOut->setKind(COMMAND);
  phaseTimeOut->setNote(RDC_PHASE_TIME_OUT);

  // start channel check timer
  selfTimer(0, RDC_CHANNEL_CHECK);
}

void RDCdriver::finish()
{
  if (this->buffer != NULL)
  {
    delete buffer;
    this->buffer = NULL;
  }

  cancelAndDelete(ccaTimeOut);
  cancelAndDelete(phaseTimeOut);
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
          switch (phase)
          {
            case TRANSMITTING_PHASE: /* schedule but not perform checking phase */
            {
              // schedule next checking phase
              selfTimer(CHANNEL_CHECK_INTERVAL, RDC_CHANNEL_CHECK);
              break;
            } /* schedule but not perform checking phase */

            case FREE_PHASE: /* begin a checking phase */
            {
              // acquire checking phase
              phase = CHECKING_PHASE;

              // reset cca counter
              ccaCounter = CCA_COUNT_MAX;

              // start checking phase
              selfTimer(0, RDC_CHANNEL_CHECK);

              // schedule next checking phase
              selfTimer(CHANNEL_CHECK_INTERVAL, RDC_CHANNEL_CHECK);

              break;
            } /* begin a checking phase*/

            case CHECKING_PHASE: /* is on checking phase */
            {
              // decrease cca counter
              ccaCounter--;

              // turn on radio
              on();

              // begin CCA indicator
              ccaType = MAC_CCA;
              sendCommand(RDC_CCA_REQUEST);

              break;
            } /* is on checking phase */
          }
          break;
        } /* channel check*/

        case RDC_READY_TRANS_PHASE: /* enter transmission phase */
        {
          // release pending
          isHavingPendingTransmission = false;

          // acquire transmitting phase
          phase = TRANSMITTING_PHASE;

          // inform MAC RDC is free
          sendResult(RDC_READY_TRANS_PHASE);

          // WSN FUCK ME !!!
          // create time out
          scheduleAt(simTime().dbl() + MAX_PHASE_STROBE, phaseTimeOut);

          if (DEBUG)
            ev << "Enter transmission phase" << endl;

          break;
        } /* enter transmission phase*/

        case RDC_BEGIN_TRANS_TURN: /* begin a transmission turn */
        {
          if (phase == TRANSMITTING_PHASE)
          {
            // RDC CCA
            ccaType = RDC_CCA;
            sendCommand(RDC_CCA_REQUEST);
          }
          break;
        } /* begin a transmission turn */

        case RDC_PHASE_TIME_OUT: /* phase time out */
        {
          // Release
          phase = FREE_PHASE;

          if (!buffer->getAckRequired()) // broadcast is always success
          {
            // stop transmission
            selfTimer(0, RDC_STOP_TRANS_PHASE);

            // inform success
            sendResult(RDC_SEND_OK);
          }
          else // if unicast + NO ACK
          {
            // stop transmission
            selfTimer(0, RDC_STOP_TRANS_PHASE);

            // inform failure
            sendResult(RDC_SEND_NO_ACK);
          }

          break;
        } /* phase time out  */

        case RDC_STOP_TRANS_PHASE: /* stop a transmission phase */
        {
          // stop timeout transmission phase
          cancelEvent(phaseTimeOut);

          // end all transmission command
          phase = FREE_PHASE;

          // turn off radio
          off();

          break;
        } /* stop a transmission phase */

        case RDC_SEND_FRAME: /* send frame */
        {
          if (phase != FREE_PHASE && phaseTimeOut->isScheduled()) /* if timer does not stop */
            sendFrame();

          break;
        } /* send frame */

        case RDC_CCA_TIME_OUT: /* cca time out */
        {
          // time out
          phase = FREE_PHASE;
          break;
        }/* cca time out */

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
      // clear old buffer
      if (buffer != NULL)
        delete this->buffer;

      // assign new frame
      this->buffer = check_and_cast<Frame*>(packet);

      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case MAC_ASK_SEND_FRAME: /* register a transmission phase */
        {
          // does not aquire transmission phase at this stage
          if (this->phase == FREE_PHASE) // is free
          {
            selfTimer(0, RDC_READY_TRANS_PHASE);
          }
          else // wait
          {
            // wait this CCA complete
            isHavingPendingTransmission = true;
          }
          break;
        } /* register a transmission phase */

        case MAC_BEGIN_SEND_TURN: /* begin a turn in a transmission phase */
        {
          // acquire phase lock (if possible)
          double phaseLock = 0;

//          int recverID = 0;
//          if (getModuleByPath("^.^")->par("usingHDC").boolValue())
//          {
//            // compress using HC01
//          }
//          else
//          {
//            recverID = (check_and_cast<FrameDataStandard*>(buffer))->getDestinationMacAddress();
//          }
//          for (std::list<Neighbor*>::iterator it = this->neighbors.begin(); it != this->neighbors.end(); it++)
//          {
//            if ((*it)->senderID == recverID)
//            {
//              phaseLock = (*it)->phaseOptimization;
//              break;
//            }
//          }

          // reset number of cca
          ccaInOneTurn = 0;

          // phase lock wait
          selfTimer(phaseLock, RDC_BEGIN_TRANS_TURN);

          break;
        } /* begin a transmission phase */

        case MAC_CCA_REQUEST: /* request CCA */
        {
          ccaType = MAC_CCA;
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
    case DATA: /* Data */
    {
      // consider is ACK
      if (check_and_cast<Frame*>(packet)->getHeaderLength() == ACK_LENGTH)
      {

        // only consider in case of unicast transmission
        if (buffer->getAckRequired())
        {
          // not itself ACK
          if (check_and_cast<FrameACK*>(packet)->getDataSequenceNumber()
              != check_and_cast<MACdriver*>(getModuleByPath("^.mac"))->sequenceNumber)
          {
            delete packet;
            return;
          }

          // cancel phase timeout
          cancelEvent(phaseTimeOut);

          // stop transmission
          selfTimer(0, RDC_STOP_TRANS_PHASE);

          // inform success
          sendResult(RDC_SEND_OK);

          // remember phase lock (minus ack transmission time, minus reception time -> wake up time)
        }

        // delete ack
        delete packet;
      }
      else
      {
        // cancel cca time out
        cancelEvent(ccaTimeOut);

        switch (check_and_cast<Frame*>(packet)->getFrameType())
        /* Frame type */
        {
          case FRAME_DATA: /* frame data */
          {
            if (getModuleByPath("^.^")->par("usingHDC").boolValue())
            {
              // WSN compress using HC01
            }
            else
            {
              FrameDataStandard* frame = check_and_cast<FrameDataStandard*>(packet);

              // consider right address
              int destinationMacAddress = frame->getDestinationMacAddress();

              // unicast + wrong MAC address
              if (destinationMacAddress != 0
                  && destinationMacAddress != this->getParentModule()->getModuleByPath(".mac")->getId())
              {
                // lost packet (not broadcast and wrong mac address) dismiss
                delete packet;
              }
              else
              {
                // consider sequence number (duplicate)
                bool isFound = false;

                // search through neighbor list
                for (std::list<Neighbor*>::iterator it = this->neighbors.begin(); it != this->neighbors.end(); it++)
                {
                  // if neighbor in MAC-IP table
                  if ((*it)->senderID == destinationMacAddress)
                  {
                    isFound = true;

                    if ((*it)->sequence < frame->getDataSequenceNumber())
                    {
                      // not duplicated, send to upper
                      ((*it))->sequence = frame->getDataSequenceNumber();

                      // check ACK required
                      if (frame->getAckRequired())
                      {
                        // send ACK
                        FrameACK* ack = new FrameACK;
                        ack->setKind(DATA);
                        ack->setByteLength(ack->getHeaderLength());
                        ack->setDataSequenceNumber(frame->getDataSequenceNumber());

                        isJustSendACK = true;

                        // Simulate AUTO-ACK
                        Raw* ackRaw = new Raw;
                        ackRaw->setKind(DATA);
                        ackRaw->setByteLength(ackRaw->getHeaderLength());
                        ackRaw->encapsulate(ack);

                        sendDirect(ackRaw,
                            simulation.getModule(frame->getSourceMacAddress())->getModuleByPath("^.radio")->gate(
                                "radioIn"));
                      }

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

                // if neighbor not in MAC-IP table, create new and send to upper
                if (!isFound)
                {
                  Neighbor *neighbor = new Neighbor;
                  neighbor->senderID = destinationMacAddress;
                  neighbor->sequence = frame->getDataSequenceNumber();

                  this->neighbors.push_back(neighbor);

                  // check ACK required
                  if (frame->getAckRequired())
                  {
                    // send ACK
                    FrameACK* ack = new FrameACK;
                    ack->setKind(DATA);
                    ack->setByteLength(ack->getHeaderLength());

                    // Simulate AUTO-ACK
                    Raw* ackRaw = new Raw;
                    ackRaw->setKind(DATA);
                    ackRaw->setByteLength(ackRaw->getHeaderLength());
                    ackRaw->encapsulate(ack);

                    sendDirect(ackRaw,
                    simulation.getModule(frame->getSourceMacAddress())->getModuleByPath("^.radio")->gate("radioIn"));
                  }

                  sendMessageToUpper(frame);
                }
              }
            }

            break;
          } /* frame data */

        } /* Frame type */
      }

      break;
    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* Channel is clear */
        {
          switch (phase)
          {
            case TRANSMITTING_PHASE: /* CCA on transmitting */
            {
              // distingush MAC CCA and RDC CCA
              switch (ccaType)
              {
                case MAC_CCA: /* MAC CCA */
                {
                  sendResult(CHANNEL_CLEAR);
                  break;
                } /* MAC CCA */

                case RDC_CCA: /* RDC CCA */
                {
                  // send
                  sendFrame();
                  break;
                } /* RDC CCA */
              }

              break;
            } /* CCA on transmitting */

            case CHECKING_PHASE: /* CCA on checking*/
            {
              // not seen
              off();

              // switch to transmission phase ?
              if (isHavingPendingTransmission)
              {
                // enter transmisson phase
                selfTimer(0, RDC_READY_TRANS_PHASE);
              }
              // consider if last cca
              else if (ccaCounter == 0)
              {
                // release checking phase
                phase = FREE_PHASE;
              }
              else
              {
                // schedule next cca
                selfTimer(CCA_SLEEP_TIME, RDC_CHANNEL_CHECK);
              }

              break;
            } /* CCA on checking*/

          }
          break;
        } /* Channel is clear */

        case CHANNEL_BUSY: /* Channel is busy */
        {
          switch (phase)
          {
            case TRANSMITTING_PHASE: /* CCA on transmitting */
            {
              // distingush MAC CCA and RDC CCA
              switch (ccaType)
              {
                case MAC_CCA: /* MAC CCA */
                {
                  sendResult(CHANNEL_BUSY);
                  break;
                } /* MAC CCA */

                case RDC_CCA: /* RDC CCA */
                {
                  // is reaching maxium number of CCA
                  if (++ccaInOneTurn > CCA_TRANS_MAX)
                  {
                    // release transmitting phase
                    phase = FREE_PHASE;

                    // inform busy
                    sendResult(RDC_SEND_COL);
                  }
                  else
                  {
                    // wait sleep time and perform another CCA
                    selfTimer(CCA_SLEEP_TIME, RDC_CCA_REQUEST);
                  }
                  break;
                } /* RDC CCA */
              }

              break;
            } /* CCA on transmitting */

            case CHECKING_PHASE: /* CCA on checking */
            {
              if (isHavingPendingTransmission)
              {
                // inform MAC that channel is busy
                isHavingPendingTransmission = false;
                sendResult(RDC_SEND_COL);
              }

              // listen but have time out, dismiss in case of receiving
              if (ccaTimeOut->isScheduled())
                cancelEvent(ccaTimeOut);

              scheduleAt(simTime() + LISTEN_AFTER_DETECT, ccaTimeOut);

              break;
            } /* CCA on checking*/
          }
          break;
        }/* Channel is busy */

        case PHY_TX_OK: /* callback after transmitting */
        {
          if (isJustSendACK)
          {
            isJustSendACK = false;
          }
          else
          {
            if (this->buffer->getAckRequired())
            {
              // Unicast

              // listen
              on();

              // check time-out
              if (phaseTimeOut->isScheduled())
                selfTimer(INTER_FRAME_INTERVAL, RDC_BEGIN_TRANS_TURN);
            }
            else
            {
              // Broadcast

              // sleep
              off();

              // check-time out
              if (phaseTimeOut->isScheduled())
                selfTimer(INTER_FRAME_INTERVAL, RDC_BEGIN_TRANS_TURN);
            }
          }
          break;
        }/* callback after transmitting */

        case PHY_TX_ERR: /* Internal error */
        {
          selfTimer(0, RDC_STOP_TRANS_PHASE);
          sendResult(RDC_SEND_FATAL);
          break;
        }/* Internal error */

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

void RDCdriver::sendFrame()
{
  sendMessageToLower(buffer->dup());
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
