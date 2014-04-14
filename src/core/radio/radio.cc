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
  this->trRange = par("trRange");
  this->coRange = par("coRange");
  this->incomingSignal = 0;

  // Turn on in initializing phase
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

void RadioDriver::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case PHY_END_CCA: /* ending of CCA */
//          if (this->incomingSignal > 0) /* Channel not free*/
          if (false)  // WSN hack channel always free
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

        case PHY_SWITCH_TRANSMIT: /* switch to transmit */
        {
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
            switch (this->status)
            {
              case IDLE:
                selfTimer(SWITCH_MODE_DELAY_IDLE_TO_TRANS, PHY_BEGIN_TRANSMIT);
                break;

              case LISTENING:
                selfTimer(SWITCH_MODE_DELAY_LISTEN_TO_TRANS, PHY_BEGIN_TRANSMIT);
                break;

              case TRANSMITTING:
                selfTimer(0, PHY_BEGIN_TRANSMIT);
                break;
            }
          }
          break;
        } /* switch to transmit */

        case PHY_SWITCH_LISTEN: /* switch to listen */
        {
          switch (this->status)
          {
            case IDLE:
              selfTimer(SWITCH_MODE_DELAY_IDLE_TO_LISTEN, PHY_LISTENING);
              break;

            case TRANSMITTING:
              selfTimer(SWITCH_MODE_DELAY_TRANS_TO_LISTEN, PHY_LISTENING);
              break;

            case LISTENING:
              selfTimer(0, PHY_LISTENING);
              break;
          }
          break;
        }/* switch to listen */

        case PHY_SWITCH_IDLE: /* switch to sleep */
        {
          switch (this->status)
          {
            case IDLE:
              selfTimer(0, PHY_IDLING);
              break;

            case TRANSMITTING:
              selfTimer(SWITCH_MODE_DELAY_TRANS_TO_IDLE, PHY_IDLING);
              break;

            case LISTENING:
              selfTimer(SWITCH_MODE_DELAY_LISTEN_TO_IDLE, PHY_IDLING);
              break;
          }
          break;
        }/* switch to sleep */

        case PHY_BEGIN_TRANSMIT:
          /* end transmitting */
        {
          transmit_begin();
          break;
        }/* begin transmit */

        case PHY_END_TRANSMIT:
          /* end transmitting */
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

        case PHY_LISTENING:
          /* begin listening*/
        {
          listen();
          break;
        }/* begin listening */

        case PHY_IDLING:
          /* idling */
        {
          sleep();
          break;
        }/* idling */

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

void RadioDriver::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      this->bufferTXFIFO = new Raw;
      this->bufferTXFIFO->setKind(DATA);
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

        case RDC_LISTEN:/* turn on listening */
          selfTimer(0, PHY_SWITCH_LISTEN);
          break; /* turn on listening */

        case RDC_IDLE: /* turn off listening */
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

  selfTimer(finishTime, PHY_END_TRANSMIT);
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
    ev << "LISTEN (PHY)" << endl;

  switchOscilatorMode(LISTENING);
}

/*
 *   Callback after receiving
 */
void RadioDriver::received(Raw* raw)
{
  if (true)   // WSN hack receive a complete message
//  if (!raw->hasBitError())
  {
    if (DEBUG)
      ev << "Received !!!" << endl;

    /* okay message from begin to end */
    sendMessageToUpper(raw->decapsulate());
  }
  /* WSN receie a corrupt message */
  /* WSN receie an incompleted message */
  else
  {
    if (DEBUG)
      ev << "Nonsense signal !!!" << endl;

    sendResult(PHY_RECV_CORRUPTED);
  }

  delete raw;
}

/*
 *   Idle
 */
void RadioDriver::sleep()
{
  if (DEBUG)
    ev << "IDLE (PHY)" << endl;

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
