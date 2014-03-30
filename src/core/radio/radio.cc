#include "radio.h"

#include "world.h"
#include "statistic.h"
#include "battery.h"

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

void RadioDriver::initialize()
{
  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->broadcastMessage = NULL;

  listen_on();
}

void RadioDriver::handleMessage(cMessage* msg)
{
  switch (msg->getKind())
  {
    case LAYER_RADIO: /* control message */
    {
      Raw *raw = check_and_cast<Raw*>(msg);

      switch (raw->getNote())
      {
        case LAYER_RADIO_SWITCH_TRANSMIT:
          // show packet length (bytes)
          if (DEBUG)
            ev << "Radio length " << raw->getByteLength() << endl;

          // WSN check packet length (127 + 6 bytes)
          if (raw->getByteLength() > PACKET_802154 + PHY_HEADER)
          {
            if (DEBUG)
              ev << "Packet is too large" << endl;

            /* Feedback to RDC */
            FrameRDC *frame = new FrameRDC;
            frame->setKind(LAYER_RDC);
            frame->setNote(LAYER_RADIO_PACKET_OVERSIZE);
            send(frame, gate("upperOut"));
          }

          // perform CCA
          else if (!isClearChannel())
          {
            /* Feedback to RDC */
            FrameRDC *frame = new FrameRDC;
            frame->setKind(LAYER_RDC);
            frame->setNote(LAYER_RADIO_CCA_NOT_VALID);
            send(frame, gate("upperOut"));
          }

          // check radio duty
          else if (this->status == RECEIVING || this->status == TRANSMITTING)
          {
            /* Feedback to RDC*/
            FrameRDC *frame = new FrameRDC;
            frame->setKind(LAYER_RDC);
            frame->setNote(LAYER_RADIO_NOT_FREE);
            send(frame, gate("upperOut"));
          }

          // feasible
          else
          {
            raw->setNote(LAYER_RADIO_BEGIN_TRANSMIT);

            switch (this->status)
            {
              case SLEEPING:
                scheduleAt(simTime() + SWITCH_MODE_DELAY_SLEEP_TO_TRANS, raw);
                break;

              case LISTENING:
                listen_off();
                scheduleAt(simTime() + SWITCH_MODE_DELAY_LISTEN_TO_TRANS, raw);
                break;

              case TRANSMITTING:
                scheduleAt(simTime(), raw);
                break;
            }
            this->status = TRANSMITTING;
          }
          break; /* switch to transmit */

        case LAYER_RADIO_SWITCH_LISTEN:
          // check radio duty
          if (this->status == TRANSMITTING)
          {
            /* Feedback to RDC*/
            FrameRDC *frame = new FrameRDC;
            frame->setKind(LAYER_RDC);
            frame->setNote(LAYER_RADIO_NOT_FREE);
            send(frame, gate("upperOut"));
          }
          // feasible
          else
          {
            raw->setNote(LAYER_RADIO_BEGIN_LISTEN);

            switch (this->status)
            {
              case SLEEPING:
                scheduleAt(simTime() + SWITCH_MODE_DELAY_SLEEP_TO_LISTEN, raw);
                break;

              case LISTENING:
                listen_off();
                scheduleAt(simTime(), raw);
                break;

              case TRANSMITTING:
                scheduleAt(simTime() + SWITCH_MODE_DELAY_TRANS_TO_LISTEN, raw);
                break;
            }
            this->status = LISTENING;
          }
          break; /* switch to listen */

        case LAYER_RADIO_SWITCH_SLEEP:
          this->status = SLEEPING;
          break; /* switch to sleep */

        case LAYER_RADIO_BEGIN_TRANSMIT:
          transmit_on(raw);
          break; /* begin transmit */

        case LAYER_RADIO_END_TRANSMIT: {
          transmit_off();

          /* Feedback */
          FrameRDC *frame = new FrameRDC;

          frame->setKind(LAYER_RADIO);
          frame->setNote(LAYER_RADIO_SEND_OK);

          send(frame, gate("upperOut"));
        }
          break; /* end transmitting*/

        case LAYER_RADIO_BEGIN_LISTEN:
          listen_on();
          break; /* begin listening */

        case LAYER_RADIO_END_LISTENING:
          listen_off();
          break; /* end listening */

        case LAYER_RADIO_RECV_OK: {
          /* Decapsulate */
          FrameRDC *frame = new FrameRDC;

          frame = check_and_cast<FrameRDC*>(raw->decapsulate());
          frame->setKind(LAYER_RADIO);
          frame->setNote(LAYER_RADIO_RECV_OK);

          send(frame, gate("upperOut"));
        }
          break; /* receie a OK message */

        case LAYER_RADIO_RECV_CORRUPT:
          /* Dismiss message */
          break; /* receie a corrupt message */
      }
    }
      break; /* control message */

    case LAYER_RDC:
      /* message from MAC layer */
    {
      FrameRDC *frame = check_and_cast<FrameRDC*>(msg);

      switch (frame->getNote())
      {
        case LAYER_RDC_LISTEN_ON: {
          Raw* raw = new Raw;

          raw->setKind(LAYER_RADIO);
          raw->setNote(LAYER_RADIO_SWITCH_LISTEN);

          scheduleAt(simTime(), raw);
        }
          break; /* turn on listening */

        case LAYER_RDC_LISTEN_OFF: {
          Raw* raw = new Raw;

          raw->setKind(LAYER_RADIO);
          raw->setNote(LAYER_RADIO_SWITCH_SLEEP);
        }
          break; /* turn off listening */

        case LAYER_RDC_SEND:
          switch (this->status)
          {
            case RECEIVING:
            case TRANSMITTING: { /* Feedback */
              FrameRDC* frame = new FrameRDC;

              frame->setKind(LAYER_RADIO);
              frame->setNote(LAYER_RADIO_NOT_FREE);
              send(frame, gate("upperOut"));
            }
              break; /* radio is on duty */

            case LISTENING:
            case SLEEPING: { /* Ignite transmitting */
              Raw* raw = new Raw;

              raw->encapsulate(frame);
              raw->setKind(LAYER_RADIO);
              raw->setNote(LAYER_RADIO_SWITCH_TRANSMIT);
              raw->addByteLength(PHY_HEADER);

              scheduleAt(simTime(), raw);
            }
              break; /* radio is free to operate */
          } /* checking radio status */

          break; /* sending a MAC message*/
      }
    }
      break; /* message from MAC layer */
  } /* Consider message layer*/
}

void RadioDriver::finish()
{
  this->neighbor.clear();
  this->broadcastMessage = NULL;
}

/*
 * Turn on to transmit
 */
void RadioDriver::transmit_on(Raw *raw)
{
  if (DEBUG)
    ev << "Start transmitting" << endl;

  broadcastMessage = raw;

  // register transmission to world
  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    RadioDriver *recver = (RadioDriver*) simulation.getModule(neighbor.at(i));
    // register transmission
    ((World*) simulation.getModuleByPath("world"))->registerTransmission(new Transmission(this, recver));
  }

  double finishTime = broadcastMessage->getByteLength() / DATA_RATE;
  broadcastMessage->setNote(LAYER_RADIO_END_TRANSMIT);

  scheduleAt(simTime() + finishTime, broadcastMessage);

  // turn off listening and transmitting
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_TRANSMIT, getTxPower());
}

/*
 *   Turn off transmitting
 */
void RadioDriver::transmit_off()
{
  if (DEBUG)
    ev << "End transmitting" << endl;

  //  Color here
  broadcastMessage->setRadioSendId(this->getParentModule()->getId());

  for (unsigned int i = 0; i < neighbor.size(); i++)
  {
    RadioDriver* recver = (RadioDriver*) simulation.getModule(neighbor.at(i));

    Transmission *completeTranmission = new Transmission(this, recver);

    // check feasible
    if (((World*) simulation.getModuleByPath("world"))->isFeasibleTransmission(completeTranmission))
    {
      // EV << "Received" << endl;
      broadcastMessage->setBitError(true);
      broadcastMessage->setNote(LAYER_RADIO_RECV_OK);

      ((Statistic*) simulation.getModuleByPath("statistic"))->incRecvPacket();
    }
    else
    {
      // EV << "Corrupted" << endl;
      if (DEBUG)
        recver->getParentModule()->bubble("Corrupted");
      broadcastMessage->setBitError(false);
      broadcastMessage->setNote(LAYER_RADIO_RECV_CORRUPT);
      // WSN hack !!!
      // broadcastMessage->setNote(LAYER_RADIO_RECV_OK);

      ((Statistic*) simulation.getModuleByPath("statistic"))->incLostPacket();
    }

    broadcastMessage->setRadioRecvId(recver->getParentModule()->getId());
    cGate* gate = simulation.getModule(neighbor.at(i))->gate("radioIn");
    sendDirect(broadcastMessage->dup(), gate);

    // Turn receiving mote off
    ((World*) simulation.getModuleByPath("world"))->stopTransmission(completeTranmission);
  }

  this->status = SLEEPING;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_TRANSMIT);
}

/*
 *   Turn on receiving
 */
void RadioDriver::listen_on()
{
  if (DEBUG)
    ev << "Recv on" << endl;
  this->status = LISTENING;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_LISTEN, getRxPower());
}

/*
 *   Turn off receiving
 */
void RadioDriver::listen_off()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  this->status = SLEEPING;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_LISTEN);
}

}  // namespace wsn_energy
