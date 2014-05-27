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
#define DEBUG 0
#endif

namespace wsn_energy {

void RDCdriver::initialize()
{
  // intitialisation
  this->bufferRDC = NULL;
  this->isHavingPendingTransmission = false;
  this->isSentACK = false;
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

          if (DEBUG)
            std::cout << getFullPath() << "cca: " << ccaType << " @ " << simTime().dbl() << endl;

          // need to consider overlap CCA ???
          cancelEvent(ccaResult);
          scheduleAt(simTime().dbl() + CCA_CHECK_TIME, ccaResult);

          delete packet;

          break;
        } /* check cca */

        case RDC_CCA_RESULT: /* check cca result */
        {
          if (cca()) /* Channel busy*/
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
                    ccaInOneTurn--;

                    // is reaching maxium number of CCA
                    if (phaseTimeOut->isScheduled())
                    {
                      if (ccaInOneTurn < 0)
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
                        selfTimer(CCA_SLEEP_TIME, RDC_BEGIN_TRANS_TURN);
                      }
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

                // if has pending phase, wait for cca time out cancel it

                break;
              } /* CCA on checking*/

              case FREE_PHASE: // ???
              {
                break;
              }

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
                    // reset cca in one turn
                    ccaInOneTurn = CCA_TRANS_MAX;

                    // transmitting
                    sendFrame();

                    break;
                  }

                  case RDC_CHECK_CCA: // rdc check on transmitting ???
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

                // has pending transmission phase
                if (isHavingPendingTransmission)
                {
                  // enter transmission phase
                  enterMACtransmissonPhase();
                }
                // consider if last cca
                else if (ccaCounter == 0)
                {
                  // release checking phase
                  phase = FREE_PHASE;

                  // not seen
                  off();
                }
                else
                {
                  // schedule next cca
                  selfTimer(CCA_SLEEP_TIME, RDC_PERIODICAL_MINOR_CHECK);

                  // not seen
                  off();
                }

                break;
              } /* CCA on checking*/

              case FREE_PHASE: // free phase
              {
                break;
              }
            }
          } /* Channel clear */

          // do not delete cca request for later reuse

          break;
        } /* check cca result */

        case RDC_PERIODICAL_MINOR_CHECK: /* minor channel check */
        {
          if (!ccaTimeOut->isScheduled() && !ccaResult->isScheduled() && !isHavingPendingTransmission && phase == CHECKING_PHASE)
          {
            // begin CCA indicator
            ccaCounter--;
            ccaType = RDC_CHECK_CCA;
            selfTimer(0, RDC_CCA_REQUEST);
          }
          else
          {
            enterMACtransmissonPhase();
          }

          delete packet; // done command

          break;
        } /* minor channel check */

        case RDC_PERIODICAL_MAJOR_CHECK: /* major channel check */
        {
          // schedule next checking phase
          selfTimer(CHANNEL_CHECK_INTERVAL, RDC_PERIODICAL_MAJOR_CHECK);

          switch (phase)
          {
            case TRANSMITTING_PHASE: /* schedule but not perform checking phase */
            {
              break;
            } /* schedule but not perform checking phase */

            case CHECKING_PHASE: /* is on checking phase */
            {
              break;
            } /* is on checking phase */

            case FREE_PHASE: /* begin a checking phase */
            {
              if (!isHavingPendingTransmission)
              {
                enterMACtransmissonPhase();
              }
              else
              {
                // acquire checking phase
                phase = CHECKING_PHASE;

                // reset cca counter
                ccaCounter = CCA_COUNT_MAX;

                // begin CCA indicator
                selfTimer(0, RDC_PERIODICAL_MINOR_CHECK);
              }

              break;
            } /* begin a checking phase*/
          }

          delete packet; // done command

          break;
        } /* major channel check*/

        case RDC_BEGIN_TRANS_TURN:
          /* begin a transmission turn */
        {
          enterRDCtransmissionPhase();

          delete packet; // done command

          break;
        } /* begin a transmission turn */

        case RDC_PHASE_TIME_OUT:
          /* phase time out */
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

        case RDC_CCA_TIME_OUT:
          /* cca time out */
        {
          // time out
          if (phase == CHECKING_PHASE)
            phase = FREE_PHASE;

          // turn off radio
          off();

          // if pending, ready for next phase
          if (isHavingPendingTransmission)
            enterMACtransmissonPhase();

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
      this->beginTransmitting(check_and_cast<Command*>(packet)->getNote());
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
      this->receiveFrame(check_and_cast<Frame*>(packet));
      break;
    } /* Data */

    case RESULT:
      /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case PHY_TX_OK: /* callback after transmitting */
        {
          if (isSentACK)
          {
            isSentACK = false;
          }
          else if (phaseTimeOut->isScheduled())
          {
            if (this->bufferRDC->getAckRequired())
            {
              // listen to ACK
              on();

              // refresh CCA in one turn
              ccaInOneTurn = CCA_TRANS_MAX;

              // check time-out
              selfTimer(INTER_FRAME_INTERVAL, RDC_BEGIN_TRANS_TURN);
            }
            else
            {
              // sleep
              off();

              // refresh CCA in one turn
              ccaInOneTurn = CCA_TRANS_MAX;

              // check-time out
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
          delete packet;
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

void RDCdriver::sendFrame()
{
  if (phase == TRANSMITTING_PHASE && phaseTimeOut->isScheduled() && bufferRDC != NULL)
  {
    sendMessageToLower(bufferRDC->dup());
    sendCommand(RDC_TRANSMIT);
  }
}

void RDCdriver::enterMACtransmissonPhase()
{
  if (isHavingPendingTransmission)
  {
    if (DEBUG)
      ev << "RDC: Enter transmission phase" << endl;

    // release pending
    isHavingPendingTransmission = false;

    // acquire transmitting phase
    phase = TRANSMITTING_PHASE;

    sendResult(RDC_READY_TRANS_PHASE);

    cancelEvent(ccaTimeOut);
    cancelEvent(ccaResult);
  }
}

void RDCdriver::quitMACtransmissonPhase()
{
  // release lock
  phase = FREE_PHASE;

  cancelEvent(phaseTimeOut);
  cancelEvent(ccaTimeOut);
  cancelEvent(ccaResult);

  // clear last buffer
  if (this->bufferRDC != NULL)
  {
    delete this->bufferRDC;
    this->bufferRDC = NULL;
  }
}

void RDCdriver::enterRDCtransmissionPhase()
{
  if (phaseTimeOut->isScheduled()) // still not time-out
  {
    cancelEvent(ccaResult);
    cancelEvent(ccaTimeOut);

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
  cancelEvent(ccaResult);
  cancelEvent(ccaTimeOut);

  // turn off radio, just in case
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

bool RDCdriver::cca()
{
  if ((check_and_cast<RadioDriver*>(getModuleByPath("^.radio")))->incomingSignal > 0)
    return true;
  else
    return false;
}

} /* namespace wsn_energy */
