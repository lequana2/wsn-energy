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
  this->command = new Command;
  this->command->setKind(COMMAND);

  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->incomingSignal = 0;

  // WSN Turn on at first
  listen();
}

void RadioDriver::handleMessage(cMessage* msg)
{
  // stop working
  if (this->status == POWER_DOWN)
  {
    delete msg;
    return;
  }

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
}

void RadioDriver::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case PHY_END_CCA: /* ending of CCA */
          if (this->incomingSignal > 0) /* Channel not free*/
          {
            if (DEBUG)
              ev << "Channel is busy" << endl;

            /* Feedback to RDC */
            sendResult(CHANNEL_BUSY);
          } /* Channel not free*/
          else /* Channel clear */
          {
            if (DEBUG)
              ev << "Channel is clear" << endl;

            /* Feedback to RDC */
            sendResult(CHANNEL_CLEAR);
          } /* Channel clear */
          break; /* ending of CCA */

        case PHY_SWITCH_TRANSMIT:
          /* show packet length (bytes) */
          if (DEBUG)
            ev << "Radio length " << bufferTXFIFO->getByteLength() << endl;

          /* check packet length (127 + 6 bytes) */
          if (bufferTXFIFO->getByteLength() > PACKET_802154 + PHY_HEADER)
          {
            if (DEBUG)
              ev << "Packet is too large" << endl;

            /* Feedback to RDC */
            sendResult(PHY_TX_ERR);
          }
          /* Prepare transmitting */
          else
          {
            command->setNote(PHY_BEGIN_TRANSMIT);
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

        case PHY_SWITCH_LISTEN: /* switch to listen */
          command->setNote(PHY_LISTENING);
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

        case PHY_SWITCH_IDLE: /* switch to sleep */
          command->setNote(PHY_IDLING);
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

        case PHY_BEGIN_TRANSMIT: /* end transmitting */
        {
          transmit_begin();
          break;
        }/* begin transmit */

        case PHY_END_TRANSMIT: /* end transmitting */
        {
          transmit_end();

          // clear buffer
          delete this->bufferTXFIFO;

          // WSN after sending, switch immediately to listen
          listen();

          /* Feedback to RDC */
          sendResult(PHY_TX_OK);
          break;
        } /* end transmitting*/

        case PHY_LISTENING: /* begin listening*/
        {
          listen();
          break;
        }/* begin listening */

        case PHY_IDLING: /* idling */
        {
          sleep();
          break;
        }/* idling */

        default:
          ev << "Unknown command" << endl;
          break;
      }

      // delete packet; // reuse command
      break;
    } /* Command */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void RadioDriver::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      this->bufferTXFIFO = new Raw;
      this->bufferTXFIFO->setByteLength(PHY_HEADER);

      this->bufferTXFIFO->encapsulate(packet);
      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case CHANNEL_CCA_REQUEST: /* CCA request */
          selfTimer(intervalCCA(), PHY_END_CCA);
          break; /* CCA request */

        case RDC_SEND: /* transmitting */
          switch (this->status)
          {
            case TRANSMITTING: /* radio is transmitting */
              break; /* radio is transmitting */

            case LISTENING: /* Ignite transmitting */
            case IDLE: /* Ignite transmitting */
              selfTimer(0, PHY_SWITCH_TRANSMIT);
              break; /* Ignite transmitting */
          }
          break; /* transmitting */

        case PHY_LISTENING:/* turn on listening */
          selfTimer(0, PHY_SWITCH_LISTEN);
          break; /* turn on listening */

        case PHY_IDLING: /* turn off listening */
          selfTimer(0, PHY_SWITCH_IDLE);
          break; /* turn off listening */

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
  command->setNote(PHY_END_TRANSMIT);
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

  /* WSN hack receive a complete message */
  if (!raw->getError())
//  if (true)
  {
    FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
//    frame->setNote(LAYER_RADIO_RECV_OK);
    sendMessageToUpper(frame);

    delete raw;
  }
  /* WSN receie a corrupt message */
  else
  {
    FrameRDC *frame = check_and_cast<FrameRDC*>(raw->decapsulate());
//    frame->setNote(LAYER_RADIO_RECV_NOT_OK);
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
