/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rdc.h
 */

#include <rdc.h>
#include "mac.h"
#include "radio.h"
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
  this->bufferRDC = NULL;
  this->isHavingPendingTransmission = false;
  this->isJustSendACK = false;
  this->phase = FREE_PHASE;
  this->ccaCounter = 0;

  // is on way of cca
  ccaResult = new Command;
  ccaResult->setKind(COMMAND);
  ccaResult->setNote(RDC_CCA_RESULT);

  // cca after detecting timer
  ccaTimeOut = new Command;
  ccaTimeOut->setKind(COMMAND);
  ccaTimeOut->setNote(RDC_CCA_TIME_OUT);

  // 1 transmissing phase timeout timer
  phaseTimeOut = new Command;
  phaseTimeOut->setKind(COMMAND);
  phaseTimeOut->setNote(RDC_PHASE_TIME_OUT);

  // start channel check timer
  selfTimer(0, RDC_PERIODICAL_MAJOR_CHECK);
}

void RDCdriver::finish()
{
  if (this->bufferRDC != NULL)
  {
    delete bufferRDC;
    this->bufferRDC = NULL;
  }

  cancelAndDelete(ccaResult);
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
        case RDC_CCA_REQUEST: /* check cca */
        {
          // inform tranceiver
          sendCommand(RDC_CCA_REQUEST);

          scheduleAt(simTime().dbl() + CCA_CHECK_TIME, ccaResult);

          delete packet;

          break;
        } /* check cca */

        case RDC_CCA_RESULT: /* check cca result */
        {
          // hack
          if (false)
          //          if (!this->ccaIsFreeChannel)
//          if ((check_and_cast<RadioDriver*>(getModuleByPath("^.radio")))->incomingSignal > 0) /* Channel busy*/
          {
            if (DEBUG)
              ev << "Channel is busy" << endl;

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

                    // turn off after CCA
                    off();

                    break;
                  } /* MAC CCA */

                  case RDC_TRANS_CCA: // cca on trans
                  {
                    // is reaching maxium number of CCA
                    if (++ccaInOneTurn > CCA_TRANS_MAX)
                    {
                      // stop transmission phase
                      // inform busy channel
                      quitRDCtransmissionPhase(RDC_SEND_COL);
                    }
                    else
                    {
                      // turn off radio
                      off();

                      // wait sleep time and perform another CCA
                      selfTimer(CCA_SLEEP_TIME, RDC_CCA_REQUEST);
                    }
                    break;
                  }

                  case RDC_CHECK_CCA: // cca on check
                  {
                    break;
                  } /* RDC CCA */
                }

                break;
              } /* CCA on transmitting */

              case CHECKING_PHASE: /* CCA on checking */
              {
                // nulltify following cca
                ccaCounter = 0;

                // listen for a period of time
                scheduleAt(simTime().dbl() + LISTEN_AFTER_DETECT, ccaTimeOut);

                break;
              } /* CCA on checking*/

            }
          } /* Channel busy */

          /* Channel clear */
          else
          {
            if (DEBUG)
              ev << "Channel is clear" << endl;

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

                    // Turn off after CCA
                    off();

                    break;
                  } /* MAC CCA */

                  case RDC_TRANS_CCA: // cca on trans
                  {
                    // transmitting
                    sendFrame();

                    break;
                  }

                  case RDC_CHECK_CCA: // cca on check
                  {
                    break;
                  } /* RDC CCA */
                }

                break;
              } /* CCA on transmitting */

              case CHECKING_PHASE: /* CCA on checking*/
              {
                // decrease cca counter
                ccaCounter--;

                // not seen
                off();

                // has pending transmission phase
                if (isHavingPendingTransmission)
                {
                  // release pending
                  isHavingPendingTransmission = false;

                  // enter transmission phase
                  enterMACtransmissonPhase();
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
                  selfTimer(CCA_SLEEP_TIME, RDC_PERIODICAL_MINOR_CHECK);
                }

                break;
              } /* CCA on checking*/

            }
          } /* Channel clear */

          // do not delete cca request for later reuse

          break;
        } /* check cca result */

        case RDC_PERIODICAL_MINOR_CHECK: /* minor channel check */
        {
          if (!ccaTimeOut->isScheduled() && !ccaResult->isScheduled() && phase == CHECKING_PHASE)
          {
            // begin CCA indicator
            ccaCounter--;
            ccaType = RDC_CHECK_CCA;
            selfTimer(0, RDC_CCA_REQUEST);
          }

          delete packet; // done command

          break;
        } /* minor channel check */

        case RDC_PERIODICAL_MAJOR_CHECK: /* major channel check */
        {
          switch (phase)
          {
            case TRANSMITTING_PHASE: /* schedule but not perform checking phase */
            {
              // schedule next checking phase
              selfTimer(CHANNEL_CHECK_INTERVAL, RDC_PERIODICAL_MAJOR_CHECK);

              break;
            } /* schedule but not perform checking phase */

            case FREE_PHASE: /* begin a checking phase */
            {
              // acquire checking phase
              phase = CHECKING_PHASE;

              // reset cca counter
              ccaCounter = CCA_COUNT_MAX;

              // schedule next checking phase
              selfTimer(CHANNEL_CHECK_INTERVAL, RDC_PERIODICAL_MAJOR_CHECK);

              // begin CCA indicator
              selfTimer(0, RDC_PERIODICAL_MINOR_CHECK);

              break;
            } /* begin a checking phase*/

            case CHECKING_PHASE: /* is on checking phase */
            {
              // already in checking phase
              selfTimer(CHANNEL_CHECK_INTERVAL, RDC_PERIODICAL_MAJOR_CHECK);

              break;
            } /* is on checking phase */
          }

          delete packet; // done command

          break;
        } /* major channel check*/

        case RDC_BEGIN_TRANS_TURN: /* begin a transmission turn */
        {
          enterRDCtransmissionPhase();

          delete packet; // done command

          break;
        } /* begin a transmission turn */

        case RDC_PHASE_TIME_OUT: /* phase time out */
        {
          if (bufferRDC->getAckRequired()) // if unicast + NO ACK
          {
            // stop transmission
            // inform failure
            quitRDCtransmissionPhase(RDC_SEND_NO_ACK);
          }
          else // broadcast is always success
          {
            // stop transmission
            // inform success
            quitRDCtransmissionPhase(RDC_SEND_OK);
          }

          // do not delete phase time out for later reuse

          break;
        } /* phase time out  */

        case RDC_CCA_TIME_OUT: /* cca time out */
        {
          // time out
          phase = FREE_PHASE;

          // turn off radio
          off();

          // if pending, ready for next phase
          if (isHavingPendingTransmission)
          {
            // release pending
            isHavingPendingTransmission = false;

            enterMACtransmissonPhase();
          }

          // do not delete cca time out for later reuse

          break;
        }/* cca time out */

        default:
          ev << "Unknown command" << endl;
          delete packet; // done command
          break;
      }
      break;
    } /* Command */

    default:
      delete packet;
      ev << "Unknown kind" << endl;
      delete packet;
      break;
  }
}

void RDCdriver::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      // assign new frame
      this->bufferRDC = check_and_cast<Frame*>(packet);

      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case MAC_CCA_REQUEST: /* request CCA */
        {
          ccaType = MAC_CCA;
          selfTimer(0, RDC_CCA_REQUEST);
          break;
        } /* request CCA */

        case MAC_ASK_SEND_FRAME: /* register a transmission phase */
        {
          // does not aquire transmission phase at this stage
          if (this->phase == FREE_PHASE) // is free
          {
            // release pending
            isHavingPendingTransmission = false;

            enterMACtransmissonPhase();
          }
          else // in checking phase
          {
            // wait this CCA complete
            isHavingPendingTransmission = true;
          }
          break;
        } /* register a transmission phase */

        case MAC_END_SEND_FRAME: /* end a transmission phase */
        {
          quitMACtransmissonPhase();

          break;
        }/* end a transmission phase */

        case MAC_IGNITE_RDC: /* begin a turn in a transmission phase */
        {
          // acquire phase lock (if possible)
          double phaseLock = 0;

          // reset number of cca
          ccaInOneTurn = 0;

          // create time out
          scheduleAt(simTime().dbl() + MAX_PHASE_STROBE, phaseTimeOut);

          // phase lock wait
          selfTimer(phaseLock, RDC_BEGIN_TRANS_TURN);

          break;
        } /* begin a transmission phase */

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
      // cancel cca timeout
      cancelEvent(ccaTimeOut);

      // consider is ACK
      if (check_and_cast<Frame*>(packet)->getHeaderLength() == ACK_LENGTH)
      {
        // only consider in case of unicast transmission
        if (bufferRDC->getAckRequired())
        {
          // not itself ACK ?
          if (check_and_cast<FrameACK*>(packet)->getDataSequenceNumber()
              != (check_and_cast<MACdriver*>(getModuleByPath("^.mac"))->sequenceNumber))
          {
            if (DEBUG)
              std::cout << "WRONG ACK ?" << endl;

            delete packet;
            return;
          }

          // stop transmission
          // inform success
          quitRDCtransmissionPhase(RDC_SEND_OK);

          // remember phase lock (minus ack transmission time, minus reception time -> wake up time)
        }

        // delete ack
        delete packet;
      }
      else
      {
        // cancel cca time out
        cancelEvent(ccaTimeOut);

        // time out
        phase = FREE_PHASE;

        // turn off radio
        off();

        // if pending, ready for next phase
        if (isHavingPendingTransmission)
        {
          isHavingPendingTransmission = false;

          enterMACtransmissonPhase();
        }

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
                int sourceMacAddress = frame->getSourceMacAddress();

                bool isFound = false;

                // search through neighbor list
                for (std::list<Neighbor*>::iterator it = this->neighbors.begin(); it != this->neighbors.end(); it++)
                {
                  // if neighbor in ARP table
                  if ((*it)->senderID == sourceMacAddress)
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

                        // Simulate AUTO-ACK
                        Raw* ackRaw = new Raw;
                        ackRaw->setKind(DATA);
                        ackRaw->setByteLength(ackRaw->getHeaderLength());

                        ackRaw->encapsulate(ack);

                        sendDirect(ackRaw,
                        simulation.getModule(sourceMacAddress)->getModuleByPath("^.radio")->gate("radioIn"));

//                        isJustSendACK = true;
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
                  neighbor->senderID = sourceMacAddress;
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
                    simulation.getModule(sourceMacAddress)->getModuleByPath("^.radio")->gate("radioIn"));

//                    isJustSendACK = true;
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

    case RESULT:
      /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case PHY_TX_OK: /* callback after transmitting */
        {
          if (isJustSendACK)
          {
            isJustSendACK = false;
          }
          else if (phaseTimeOut->isScheduled())
          {
            if (this->bufferRDC->getAckRequired())
            {
              // listen
              on();

              // check time-out
              if (phase == TRANSMITTING_PHASE && phaseTimeOut->isScheduled())
                selfTimer(INTER_FRAME_INTERVAL, RDC_BEGIN_TRANS_TURN);
            }
            else
            {
              // sleep
              off();

              // check-time out
              if (phase == TRANSMITTING_PHASE && phaseTimeOut->isScheduled())
                selfTimer(INTER_FRAME_INTERVAL, RDC_BEGIN_TRANS_TURN);
            }
          }
          break;
        }/* callback after transmitting */

        case PHY_TX_ERR: /* Internal error */
        {
          // stop transmission
          // inform fatal
          quitRDCtransmissionPhase(RDC_SEND_FATAL);

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
      delete packet;
      ev << "Unknown kind" << endl;
      break;
  }
}

void RDCdriver::enterMACtransmissonPhase()
{
  if (!ccaTimeOut->isScheduled() && !ccaResult->isScheduled())
  {
    if (DEBUG)
      ev << "RDC: Enter transmission phase" << endl;

    // acquire transmitting phase
    phase = TRANSMITTING_PHASE;

    // inform MAC RDC is free
    sendResult(RDC_READY_TRANS_PHASE);
  }
}

void RDCdriver::quitMACtransmissonPhase()
{
  // release lock
  phase = FREE_PHASE;

  // clear last buffer
  if (this->bufferRDC != NULL)
  {
    delete this->bufferRDC;
    this->bufferRDC = NULL;
  }
}

void RDCdriver::sendFrame()
{
  if (phase == TRANSMITTING_PHASE && phaseTimeOut->isScheduled() && bufferRDC != NULL)
  {
    sendMessageToLower(bufferRDC->dup());
    sendCommand(RDC_TRANSMIT);
  }
}

void RDCdriver::enterRDCtransmissionPhase()
{
  if (phaseTimeOut->isScheduled()) // still not time-out
  {
    // RDC CCA in order to make sure channel is clear
    ccaType = RDC_TRANS_CCA;
    selfTimer(0, RDC_CCA_REQUEST);
  }
}

void RDCdriver::quitRDCtransmissionPhase(int result)
{
  // stop transmission phase
  if (DEBUG)
    ev << "RDC: Quit 1 turn in transmission phase" << endl;

  // stop timeout transmission phase
  cancelEvent(phaseTimeOut);

  // stop another turn
  cancelEvent(ccaResult);

  // turn off radio
  off();

  sendResult(result);
}

void RDCdriver::on()
{
  sendCommand(RDC_LISTEN);
}

void RDCdriver::off()
{
  // Server never sleep after listening/receiving and transmitting phase either
  if (getId() == simulation.getModuleByPath("server.rdc")->getId())
    return;

  sendCommand(RDC_IDLE);
}

} /* namespace wsn_energy */
