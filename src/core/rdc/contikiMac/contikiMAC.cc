//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "contikiMAC.h"
#include "packet_m.h"
#include "mac.h"
#include "radio.h"

#ifndef  DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(contikiMAC);

/* command from MAC */
void contikiMAC::beginTransmitting(int command)
{
  switch (command)
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
        isHavingPendingTransmission = true;
        enterMACtransmissonPhase();
      }
      // cancel if on checking cca
      else if (ccaResult->isScheduled())
      {
        cancelEvent(ccaResult);
        isHavingPendingTransmission = true;
        enterMACtransmissonPhase();
      }
      // place holder in case of cca
      else if (ccaTimeOut->isScheduled())
      {
        isHavingPendingTransmission = true;
      }
      else
      {
        std::cout << "unhandled phase " << phase << endl;
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
}

/* send packet */
void contikiMAC::transmitFrame()
{
  return;
}

/* receive success from PHY */
void contikiMAC::receiveFrame(Frame* packet)
{
  if (phase == CHECKING_PHASE)
    phase = FREE_PHASE;

  // if pending, ready for next phase
  if (isHavingPendingTransmission)
    enterMACtransmissonPhase();

  cancelEvent(ccaTimeOut);

  // consider is ACK
  if (check_and_cast<Frame*>(packet)->getHeaderLength() == ACK_LENGTH)
  {
    // only consider in case of unicast transmission
    if (bufferRDC != NULL)
    {
      if (bufferRDC->getAckRequired() && !cca())
      {
        // not itself ACK / false positive
        if (check_and_cast<FrameACK*>(packet)->getDataSequenceNumber()
            != (check_and_cast<MACdriver*>(getModuleByPath("^.mac"))->sequenceNumber))
        {
          // dismiss
        }
        else
        {
          // stop transmission if still in transmission phase
          // inform success
          if (phaseTimeOut->isScheduled())
            quitRDCtransmissionPhase(RDC_SEND_OK);
        }

        // remember phase lock (minus ack transmission time, minus reception time -> wake up time)
      }
    }

    // delete ack
    delete packet;
  }
  else
  {
    // receive DATA in ACK period

    // receive DATA in checking period

    // turn off radio
    if (!ccaResult->isScheduled() && phase != TRANSMITTING_PHASE)
      off();

    switch (check_and_cast<Frame*>(packet)->getFrameType())
    /* Frame type */
    {
      case FRAME_DATA: /* frame data */
      {
        if (getModuleByPath("^.^")->par("usingHDC").boolValue())
        {
          // compress using HC01

          FrameDataCompressed* frame = check_and_cast<FrameDataCompressed*>(packet);

          // consider right address
          int destinationMacAddress = frame->getDestinationMacAddress();
          int sourceMacAddress = frame->getSourceMacAddress();

          // unicast + wrong MAC address
          if (destinationMacAddress != 0
              && destinationMacAddress != this->getParentModule()->getModuleByPath(".mac")->getId())
          {
            // lost packet (not broadcast and wrong mac address) dismiss
            delete packet;
          }
          else
          {
            if (check_and_cast<RadioDriver*>(getModuleByPath("^.radio"))->incomingSignal
                <= 1 && check_and_cast<RadioDriver*>(getModuleByPath("^.radio"))->status != POWER_DOWN)
            {
              // check ACK required
              if (frame->getAckRequired())
              {
                // send ACK
                FrameACK* ack = new FrameACK;
                ack->setKind(DATA);
                ack->setByteLength(ACK_LENGTH);
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

              // consider sequence number (duplicate)
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
                    sendMessageToUpper(frame);
                  }
                  else
                  {
                    // duplicated message, dismiss
                    delete frame;
                  }

                  break;
                }
              }

              // if neighbor not in MAC-IP table, create new and send to upper
              if (!isFound)
              {
                Neighbor* neighbor = new Neighbor;
                neighbor->senderID = sourceMacAddress;
                neighbor->sequence = frame->getDataSequenceNumber();

                this->neighbors.push_back(neighbor);

                sendMessageToUpper(frame);
              }
            }
            else
            {
              delete frame;
            }
          }
        }
        // Normal mode
        else
        {
          FrameDataStandard* frame = check_and_cast<FrameDataStandard*>(packet);

          // consider right address
          int destinationMacAddress = frame->getDestinationMacAddress();
          int sourceMacAddress = frame->getSourceMacAddress();

          // unicast + wrong MAC address
          if (destinationMacAddress != 0
              && destinationMacAddress != this->getParentModule()->getModuleByPath(".mac")->getId())
          {
            // lost packet (not broadcast and wrong mac address) dismiss
            delete packet;
          }
          else
          {
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

            // consider sequence number (duplicate)
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
              Neighbor* neighbor = new Neighbor;
              neighbor->senderID = sourceMacAddress;
              neighbor->sequence = frame->getDataSequenceNumber();

              this->neighbors.push_back(neighbor);

              sendMessageToUpper(frame);
            }
          }
        }

        break;
      } /* frame data */

    } /* Frame type */
  }
  return;
}
} /* namespace wsn_energy */
