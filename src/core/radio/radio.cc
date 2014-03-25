#include "radio.h"
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
      switch (raw->getTypeRadioLayer())
      {
        case LAYER_RADIO_SWITCH_TRANSMIT:
          // framer
          raw->setLen(raw->getLen() + PHY_HEADER);

          // show packet length (bytes)
          if (DEBUG)
            ev << "Packet length " << raw->getLen() << endl;

          // check packet length (127 + 6 bytes)
          if (raw->getLen() > PACKET_802154 + PHY_HEADER)
          {
            if (DEBUG)
              ev << "Packet is too large" << endl;

            raw->setTypeRadioLayer(LAYER_RADIO_PACKET_OVERSIZE);
            send(raw, gate("upperOut"));
          }

          // perform CCA
          else if (isClearChannel())
          {
            raw->setTypeRadioLayer(LAYER_RADIO_CCA_NOT_VALID);
            send(raw, gate("upperOut"));
          }

          // check radio duty
          else if (this->status == RECEIVING || this->status == TRANSMITTING)
          {
            raw->setTypeRadioLayer(LAYER_RADIO_NOT_FREE);
            send(raw, gate("upperOut"));
          }

          // feasible
          else
          {
            // packet is not over head
            raw->setTypeRadioLayer(LAYER_RADIO_BEGIN_TRANSMIT);

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
                scheduleAt(simTime() + SWITCH_MODE_DELAY, raw);
                break;
            }
            this->status = TRANSMITTING;
          }
          break; /* switch to transmit */

        case LAYER_RADIO_SWITCH_LISTEN:
          this->status = LISTENING;
          break; /* switch to listen */

        case LAYER_RADIO_SWITCH_SLEEP:
          this->status = SLEEPING;
          break; /* switch to sleep */

        case LAYER_RADIO_BEGIN_TRANSMIT:
          transmit_on(raw);
          break; /* begin transmit */

        case LAYER_RADIO_END_TRANSMIT:
          transmit_off();
          break; /* end transmitting*/

        case LAYER_RADIO_BEGIN_LISTEN:
          listen_on();
          break; /* begin listening */

        case LAYER_RADIO_END_LISTENING:
          listen_off();
          break; /* end listening */

        case LAYER_RADIO_RECV_OK:
          send(raw, gate("upperOut"));
          break; /* receie a OK message */

        case LAYER_RADIO_RECV_CORRUPT:
          // Abort ???
          break; /* receie a corrupt message */
      }
    }
      break; /* control message */

    case LAYER_RDC: /* message from MAC layer */
    {
      Frame *frame = check_and_cast<Frame*>(msg);
      switch (frame->getTypeMacLayer())
      {
        case LAYER_RDC_LISTEN_ON:
          frame->setTypeRadioLayer(LAYER_RADIO_SWITCH_LISTEN);
          this->status = LISTENING;
          break; /* turn on listening */

        case LAYER_RDC_LISTEN_OFF:
          frame->setTypeRadioLayer(LAYER_RADIO_SWITCH_SLEEP);
          this->status = SLEEPING;
          break; /* turn off listening */

        case LAYER_RDC_SEND:
          switch (this->status)
          {
            case RECEIVING:
            case TRANSMITTING:
              frame->setTypeRadioLayer(LAYER_RADIO_NOT_FREE);
              send(frame, gate("upperOut"));
              break; /* radio is on duty */

            case LISTENING:
            case SLEEPING:
              Raw *raw2 = check_and_cast<Raw*>(frame);
              raw2->setKind(LAYER_RADIO);
              raw2->setTypeRadioLayer(LAYER_RADIO_SWITCH_TRANSMIT);
              scheduleAt(simTime(), raw2);
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
 *   Turn on receiving
 */
void RadioDriver::listen_on()
{
  if (DEBUG)
    ev << "Recv on" << endl;
  this->status = LISTENING;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_LISTEN);
}

/*
 *   Turn off receiving
 */
void RadioDriver::listen_off()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  this->status = SLEEPING;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_LISTEN, getRxPower());
}

}  // namespace wsn_energy
