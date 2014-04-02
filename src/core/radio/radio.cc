#include "radio.h"

#include "world.h"
#include "statistic.h"
#include "energest.h"

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

void RadioDriver::initialize()
{
  this->bufferTXFIFO = NULL;
  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->status = IDLE;
  this->incomingSignal = 0;

  // Turn on
  listen();
}

void RadioDriver::handleMessage(cMessage* msg)
{
  // stop working
  if (this->status == POWER_DOWN)
    return;

  myModule::handleMessage(msg);

  if (msg->arrivedOn("radioIn"))
  {
    if (DEBUG)
      ev << this->getFullName() << " received message from outside world" << endl;
    this->receive(check_and_cast<Raw*>(msg));
  }
}

void RadioDriver::finish()
{
}

void RadioDriver::processSelfMessage(cPacket* packet)
{
  /* control message */
  Raw *raw = check_and_cast<Raw*>(packet);

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
        FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
        frame->setKind(LAYER_RDC);
        frame->setNote(LAYER_RADIO_PACKET_OVERSIZE);

        send(frame, gate("upperOut"));

        delete raw;
      }

      // perform CCA
//      else if (false)
//      {
//        /* Feedback to RDC */
//        FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
//        frame->setKind(LAYER_RDC);
//        frame->setNote(LAYER_RADIO_CCA_NOT_VALID);
//
//        send(frame, gate("upperOut"));
//
//        delete raw;
//      }

// check radio duty
      else if (this->status == TRANSMITTING)
      {
        /* Feedback to RDC*/
        FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
        frame->setKind(LAYER_RDC);
        frame->setNote(LAYER_RADIO_NOT_FREE);

        send(frame, gate("upperOut"));

        delete raw;
      }

      // feasible
      else
      {
        raw->setNote(LAYER_RADIO_BEGIN_TRANSMIT);

        switch (this->status)
        {
          case IDLE:
            scheduleAt(simTime() + SWITCH_MODE_DELAY_IDLE_TO_TRANS, raw);
            break;

          case LISTENING:
            scheduleAt(simTime() + SWITCH_MODE_DELAY_LISTEN_TO_TRANS, raw);
            break;

          case TRANSMITTING:
            scheduleAt(simTime(), raw);
            break;
        }
      }
      break; /* switch to transmit */

    case LAYER_RADIO_SWITCH_LISTEN:
      // check radio duty
      if (this->status == TRANSMITTING)
      {
        /* Feedback to RDC*/
        FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
        frame->setKind(LAYER_RDC);
        frame->setNote(LAYER_RADIO_NOT_FREE);

        send(frame, gate("upperOut"));

        delete raw;
      }
      // feasible
      else
      {
        raw->setNote(LAYER_RADIO_BEGIN_LISTEN);

        switch (this->status)
        {
          case IDLE:
            scheduleAt(simTime() + SWITCH_MODE_DELAY_IDLE_TO_LISTEN, raw);
            break;

          case LISTENING:
            scheduleAt(simTime(), raw);
            break;

          case TRANSMITTING:
            scheduleAt(simTime() + SWITCH_MODE_DELAY_TRANS_TO_LISTEN, raw);
            break;
        }
      }
      break; /* switch to listen */

    case LAYER_RADIO_SWITCH_SLEEP:
      // check radio duty
      if (this->status == TRANSMITTING)
      {
        /* Feedback to RDC*/
        FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
        frame->setKind(LAYER_RDC);
        frame->setNote(LAYER_RADIO_NOT_FREE);

        send(frame, gate("upperOut"));

        delete raw;
      }
      // feasible
      else
      {
        sleep();
      }
      break; /* switch to sleep */

    case LAYER_RADIO_BEGIN_TRANSMIT:
      transmit_on(raw);
      break; /* begin transmit */

    case LAYER_RADIO_END_TRANSMIT: {
      transmit_off();

      /* Feedback */
//      FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
//      frame->setKind(LAYER_RADIO);
//      frame->setNote(LAYER_RADIO_SEND_OK);
//
//      send(frame, gate("upperOut"));
//
//      listen();
//
//      delete raw;
    }
      break; /* end transmitting*/

    case LAYER_RADIO_BEGIN_LISTEN:
      listen();
      delete packet;
      break; /* begin listening */

    case LAYER_RADIO_END_LISTENING:
      delete packet;
      break; /* end listening */
  }
  /* control message */
}

void RadioDriver::processUpperLayerMessage(cPacket* packet)
{
  /* message from MAC layer */
  FrameRDC *frame = check_and_cast<FrameRDC*>(packet);

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

      scheduleAt(simTime(), raw);
    }
      break; /* turn off listening */

    case LAYER_RDC_SEND:
      switch (this->status)
      {
        case TRANSMITTING: /* Feedback */
        {
          frame->setKind(LAYER_RADIO);
          frame->setNote(LAYER_RADIO_NOT_FREE);
          send(frame, gate("upperOut"));
        }
          break; /* radio is on duty */

        case LISTENING:
        case IDLE: /* Ignite transmitting */
        {
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
  /* message from MAC layer */
}

void RadioDriver::processLowerLayerMessage(cPacket* packet)
{
  /* It is the lowest layer */
  return;
}

/*
 * Turn on to transmit
 */
void RadioDriver::transmit_on(Raw *raw)
{
  if (DEBUG)
    ev << "Start transmitting" << endl;

  bufferTXFIFO = raw;

  ((World*) simulation.getModuleByPath("world"))->registerHost(this, bufferTXFIFO);

  double finishTime = bufferTXFIFO->getByteLength() * 8 / DATA_RATE;
  bufferTXFIFO->setNote(LAYER_RADIO_END_TRANSMIT);
  scheduleAt(simTime() + finishTime, bufferTXFIFO);

//  this->status = TRANSMITTING;
//  ((World*) simulation.getModuleByPath("world"))->changeStatus(this);
//  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_LISTEN);
//  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_IDLE);
//  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_TRANSMIT,
//      getTxPower());
}

/*
 *   Turn off transmitting
 */
void RadioDriver::transmit_off()
{
  if (DEBUG)
    ev << "End transmitting" << endl;

  ((World*) simulation.getModuleByPath("world"))->releaseHost(this);

//  ((World*) simulation.getModuleByPath("world"))->changeStatus(this);
//  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_LISTEN);
//  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
//  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_IDLE,
//      getIdPower());
}

/*
 *   Turn on receiving
 */
void RadioDriver::listen()
{
  if (DEBUG)
    ev << "Recv on" << endl;
  this->status = LISTENING;

//  ((World*) simulation.getModuleByPath("world"))->changeStatus(this);
  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_IDLE);
  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_LISTEN,
      getRxPower());
}

/*
 *   Callback after receiving
 */
void RadioDriver::receive(Raw* raw)
{
  switch (raw->getNote())
  {
    case LAYER_RADIO_RECV_OK: {
      /* Decapsulate */
      FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
      frame->setKind(LAYER_RADIO);
      frame->setNote(LAYER_RADIO_RECV_OK);

      send(frame, gate("upperOut"));

      // WSN sendACK
      listen();

      delete raw;
    }
      break; /* receie a OK message */

    case LAYER_RADIO_RECV_CORRUPT:
      /* WSN Dismiss message and sleep */
      listen();
      break; /* receie a corrupt message */
  }
}

/*
 *   Idle
 */
void RadioDriver::sleep()
{
  if (DEBUG)
    ev << "Recv off" << endl;
  this->status = IDLE;

//  ((World*) simulation.getModuleByPath("world"))->changeStatus(this);
  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_LISTEN);
  (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_IDLE,
      getIdPower());
}

/*
 * Switch oscilator mode
 */
void RadioDriver::switchOscilatorMode(int type)
{
//  void World::changeStatus(RadioDriver *mote)
//  {
//    switch (mote->status)
//    {
//      case IDLE:
//        (&mote->getParentModule()->getDisplayString())->setTagArg("i", 1, IDLE_COLOR);
//        break;
//
//      case LISTENING:
//        (&mote->getParentModule()->getDisplayString())->setTagArg("i", 1, LISTEN_COLOR);
//        break;
//
//      case RECEIVING:
//        (&mote->getParentModule()->getDisplayString())->setTagArg("i", 1, RECEIVE_COLOR);
//        break;
//
//      case TRANSMITTING:
//        (&mote->getParentModule()->getDisplayString())->setTagArg("i", 1, TRANSMIT_COLOR);
//        break;
//
//      default:
//        (&mote->getParentModule()->getDisplayString())->setTagArg("i", 1, OFF_COLOR);
//        break;
//    }
//
//  }
}

}  // namespace wsn_energy
