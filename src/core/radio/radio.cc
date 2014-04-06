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
  this->command = new Raw;
  this->bufferTXFIFO = new Raw;

  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->status = IDLE;
  this->incomingSignal = 0;

  // WSN Turn on at first
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
    this->received(check_and_cast<Raw*>(msg));
  }
}

void RadioDriver::finish()
{
  cancelAndDelete(command);
  cancelAndDelete(bufferTXFIFO);
}

void RadioDriver::processSelfMessage(cPacket* packet)
{
  switch (check_and_cast<Raw*>(packet)->getNote())
  {
    case LAYER_RADIO_END_CCA: /* ending of CCA */
      if (this->incomingSignal > 0) /* Channel not free*/
      {
        if (DEBUG)
          ev << "Channel is busy" << endl;

        /* Feedback to RDC */
        FrameRDC *frame = new FrameRDC;
        frame->setNote(CHANNEL_BUSY);
        sendMessageToUpper(frame);
      } /* Channel not free*/
      else /* Channel clear */
      {
        if (DEBUG)
          ev << "Channel is clear" << endl;

        /* Feedback to RDC */
        FrameRDC *frame = new FrameRDC;
        frame->setNote(CHANNEL_CLEAR);
        sendMessageToUpper(frame);
      } /* Channel clear */
      break; /* ending of CCA */

    case LAYER_RADIO_SWITCH_TRANSMIT:
      /* show packet length (bytes) */
      if (DEBUG)
        ev << "Radio length " << bufferTXFIFO->getByteLength() << endl;

      /* check packet length (127 + 6 bytes) */
      if (bufferTXFIFO->getByteLength() > PACKET_802154 + PHY_HEADER)
      {
        if (DEBUG)
          ev << "Packet is too large" << endl;

        /* Feedback to RDC */
        FrameRDC *frame = new FrameRDC;
        frame->setNote(LAYER_RADIO_PACKET_OVERSIZE);
        sendMessageToUpper(frame);
      }
      /* Prepare transmitting */
      else
      {
        command->setNote(LAYER_RADIO_BEGIN_TRANSMIT);
        switch (this->status)
        {
          case IDLE:
            scheduleAt(simTime() + SWITCH_MODE_DELAY_IDLE_TO_TRANS, command);
            break;

          case LISTENING:
            scheduleAt(simTime() + SWITCH_MODE_DELAY_LISTEN_TO_TRANS, command);
            break;

          case TRANSMITTING:
            scheduleAt(simTime(), command);
            break;
        }
      }
      break; /* switch to transmit */

    case LAYER_RADIO_SWITCH_LISTEN: /* switch to listen */
      command->setNote(LAYER_RADIO_LISTENING);
      switch (this->status)
      {
        case IDLE:
          scheduleAt(simTime() + SWITCH_MODE_DELAY_IDLE_TO_LISTEN, command);
          break;

        case TRANSMITTING:
          scheduleAt(simTime() + SWITCH_MODE_DELAY_TRANS_TO_LISTEN, command);
          break;

        case LISTENING:
          scheduleAt(simTime(), command);
          break;
      }
      break; /* switch to listen */

    case LAYER_RADIO_SWITCH_IDLE: /* switch to sleep */
      command->setNote(LAYER_RADIO_IDLING);
      switch (this->status)
      {
        case IDLE:
          scheduleAt(simTime(), command);
          break;

        case TRANSMITTING:
          scheduleAt(simTime() + SWITCH_MODE_DELAY_TRANS_TO_IDLE, command);
          break;

        case LISTENING:
          scheduleAt(simTime() + SWITCH_MODE_DELAY_LISTEN_TO_IDLE, command);
          break;
      }
      break; /* switch to sleep */

    case LAYER_RADIO_BEGIN_TRANSMIT:
      transmit_begin();
      break; /* begin transmit */

    case LAYER_RADIO_END_TRANSMIT: {
      transmit_end();

      // WSN after sending, switch to listen
      listen();

      /* Feedback */
      FrameRDC *frame = new FrameRDC;
      frame->setNote(LAYER_RADIO_SEND_OK);
      sendMessageToUpper(frame);
    }
      break; /* end transmitting*/

    case LAYER_RADIO_LISTENING:
      listen();
      break; /* begin listening */

    case LAYER_RADIO_IDLING:
      sleep();
      break; /* end listening */
  }
  /* control message */
}

void RadioDriver::processUpperLayerMessage(cPacket* packet)
{
  switch (check_and_cast<FrameRDC*>(packet)->getNote())
  {
    case CHANNEL_CCA_REQUEST: /* CCA request */
    {
      command->setNote(LAYER_RADIO_END_CCA);
      scheduleAt(simTime() + intervalCCA(), command);
      delete packet;
    }
      break; /* CCA request */

    case LAYER_RDC_SEND: /* transmitting */
      switch (this->status)
      {
        case TRANSMITTING: /* radio is transmitting */
          break; /* radio is transmitting */

        case LISTENING: /* Ignite transmitting */
        case IDLE: /* Ignite transmitting */
        {
          delete bufferTXFIFO->decapsulate();
          bufferTXFIFO->encapsulate(packet);
          bufferTXFIFO->setByteLength(PHY_HEADER + packet->getByteLength());

          command->setNote(LAYER_RADIO_SWITCH_TRANSMIT);
          scheduleAt(simTime(), command);
        }
          break; /* Ignite transmitting */
      }
      break; /* transmitting */

    case LAYER_RDC_LISTEN_ON:/* turn on listening */
    {
      command->setNote(LAYER_RADIO_SWITCH_LISTEN);
      scheduleAt(simTime(), command);
      delete packet;
    }
      break; /* turn on listening */

    case LAYER_RDC_LISTEN_OFF: /* turn off listening */
    {
      command->setNote(LAYER_RADIO_SWITCH_IDLE);
      scheduleAt(simTime(), command);
      delete packet;
    }
      break; /* turn off listening */
  }
  /* message from MAC layer */
}

void RadioDriver::processLowerLayerMessage(cPacket* packet)
{
  /* It is the lowest layer */
  return;
}

/*
 * Begin transmitting
 */
void RadioDriver::transmit_begin()
{
  if (DEBUG)
    ev << "Start transmitting" << endl;

  // register
  ((World*) simulation.getModuleByPath("world"))->registerHost(this, bufferTXFIFO);

  // switch mode
  switchOscilatorMode(TRANSMITTING);

  // calculate finish time
  double finishTime = bufferTXFIFO->getByteLength() * 8 / DATA_RATE;
  command->setNote(LAYER_RADIO_END_TRANSMIT);
  scheduleAt(simTime() + finishTime, command);
}

/*
 *  End transmitting
 */
void RadioDriver::transmit_end()
{
  if (DEBUG)
    ev << "End transmitting" << endl;

  ((World*) simulation.getModuleByPath("world"))->releaseHost(this);
}

/*
 *   Turn on receiving
 */
void RadioDriver::listen()
{
  if (DEBUG)
    ev << "Recv on" << endl;

  switchOscilatorMode(LISTENING);
}

/*
 *   Callback after receiving
 */
void RadioDriver::received(Raw* raw)
{
  if (DEBUG)
    ev << "Received !!!" << endl;

  /* receie a complete message */
  if (!raw->getError())
  {
    FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
    frame->setNote(LAYER_RADIO_RECV_OK);
    sendMessageToUpper(frame);

    delete raw;
  }
  /* receie a corrupt message */
  else
  {
    FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
    frame->setNote(LAYER_RADIO_RECV_NOT_OK);
    sendMessageToUpper(frame);

    delete raw;
  }
}

/*
 *   Idle
 */
void RadioDriver::sleep()
{
  if (DEBUG)
    ev << "Recv off" << endl;

  ((World*) simulation.getModuleByPath("world"))->stopListening(this);
  switchOscilatorMode(IDLE);
}

/*
 * Switch oscilator mode
 */
void RadioDriver::switchOscilatorMode(int type)
{
  switch (type)
  {
    case IDLE:
      this->status = IDLE;
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_LISTEN);
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_IDLE,
          getIdPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, IDLE_COLOR);
      break;

    case LISTENING:
      this->status = LISTENING;
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_IDLE);
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_LISTEN,
          getRxPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, LISTEN_COLOR);
      break;

    case TRANSMITTING:
      this->status = TRANSMITTING;
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_IDLE);
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOff(ENERGEST_TYPE_LISTEN);
      (check_and_cast<Energest*>(getParentModule()->getModuleByPath(".energest")))->energestOn(ENERGEST_TYPE_TRANSMIT,
          getTxPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, TRANSMIT_COLOR);
      break;

    case POWER_DOWN:
      this->status = POWER_DOWN;
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, OFF_COLOR);
      break;
  }
}
}  // namespace wsn_energy
