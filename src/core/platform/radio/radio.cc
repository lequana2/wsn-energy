#include "radio.h"
#include "battery.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

void RadioDriver::initialize()
{
  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->broadcastMessage = NULL;

  this->isReceiving = false;
  this->isPending = false;

  listen_on();
}

void RadioDriver::handleMessage(cMessage* msg)
{
  // demand to transmit from upper layer
  if (msg->getKind() == LAYER_RDC)
  {
    switch (((Frame*) msg)->getTypeMacLayer())
    {
      case LAYER_RDC_TURN_RADIO_ON:
        listen_on();
        break;

      case LAYER_RDC_TURN_RADIO_OFF:
        listen_off();
        break;

      case LAYER_RDC_CHECK_FREE:
        msg->setKind(LAYER_RADIO);

        if (isReceiving || isPending)
        {
          ((Raw*) msg)->setTypeRadioLayer(LAYER_RADIO_NOT_FREE);
        }
        else
        {
          ((Raw*) msg)->setTypeRadioLayer(LAYER_RADIO_FREE);
        }
        send(msg, gate("upperOut"));
        break;

      case LAYER_RDC_TURN_RADIO_TRANS:
        transmit_on((Raw*) msg);
        break;
    }
  }
  // callback when finishing transmitted
  else if (msg->getKind() == LAYER_RADIO_END_TRANS)
  {
    transmit_off();
  }
  // callback when receiving a packet
  else if (msg->getKind() == LAYER_RADIO_END_RECV)
  {
    // to upper layer
    msg->setKind(LAYER_RADIO);
    send(msg, gate("upperOut"));
  }
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
  this->isListening = true;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOn(ENERGEST_TYPE_LISTEN);
}

/*
 *   Turn off receiving
 */
void RadioDriver::listen_off()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  this->isListening = false;
  ((Battery*) getParentModule()->getModuleByPath(".battery"))->energestOff(ENERGEST_TYPE_LISTEN, getRxPower());
}

}  // namespace wsn_energy
