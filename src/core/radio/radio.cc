#include "radio.h"

#include "world.h"
#include "statistic.h"
#include "energest.h"
#include "ipv6.h"
#include "math.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

void RadioDriver::initialize()
{
  // Transmission power, programabble
  this->txPower = TXPOWER_MAX;

  // Range
  // d = d0*pow(10,(PL(d0) - PL(d))/(10*path_loss_exponent))
  //
  // indoor
  // d0 = 1m
  // PL(d0) = -37 dBm
  //
  // fluctuate     +- 10dBm
  // rssi accuracy +- 6dBm

  double d0 = 1.0;   // fixed
  double pl0 = -37.0; // fixed
  double pathLossExponent = 2.8;
  int signalFluctuate = 10;
  int rssiAccuracy = 6;

  // expected Transmission range
  this->trRange = d0 * pow(10, (pl0 - (RX_SENSITIVITY + signalFluctuate)) / (10 * pathLossExponent));

  // expected Collision range
  this->coRange = d0 * pow(10, (pl0 - (RSSI_SENSITIVITY + rssiAccuracy)) / (10 * pathLossExponent));

  if (DEBUG)
    std::cout << "Transmission range: " << this->trRange << " and Collision range: " << this->coRange << endl;

  this->par("trRange").setDoubleValue(trRange);
  this->par("coRange").setDoubleValue(coRange);

  // already turned on
  this->status = IDLE;
}

void RadioDriver::handleMessage(cMessage* msg)
{
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
        {
          if (!this->ccaIsFreeChannel)
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
          break;
        }/* ending of CCA */

        case PHY_SWITCH_TRANSMIT: /* switch to transmit */
        {
          /* show packet length (bytes) */
          if (DEBUG)
            ev << "Radio length " << bufferTXFIFO->getByteLength() << endl;

          /* check packet length (127 + 6 bytes) */
          if (bufferTXFIFO->getByteLength() > bufferTXFIFO->getHeaderLength() + bufferTXFIFO->getMaxPayloadLength())
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

        case PHY_BEGIN_TRANSMIT: /* begin transmitting*/
        {
          transmit_begin();
          break;
        }/* begin transmit */

        case PHY_END_TRANSMIT: /* end transmitting */
        {
          transmit_end();

          // Feedback to RDC
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
      this->bufferTXFIFO->setByteLength(this->bufferTXFIFO->getHeaderLength());

      this->bufferTXFIFO->encapsulate(packet);
      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RDC_CCA_REQUEST: /* CCA request */
          selfTimer(intervalCCA(), PHY_END_CCA);
          break; /* CCA request */

        case RDC_TRANSMIT: /* transmitting */
          selfTimer(0, PHY_SWITCH_TRANSMIT);
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
}

/*
 * Begin transmitting
 */
void RadioDriver::transmit_begin()
{
  if (DEBUG)
    ev << "PHY: begin transmitting" << endl;

  // register
  check_and_cast<World*>(simulation.getModuleByPath("world"))->registerHost(this, bufferTXFIFO);

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
    ev << "PHY: end transmitting" << endl;

  (check_and_cast<World*>(simulation.getModuleByPath("world")))->releaseHost(this);

  // switch mode
  switchOscilatorMode(IDLE);

  // clear buffer
  delete this->bufferTXFIFO;
}

/*
 *   Turn on receiving
 */
void RadioDriver::listen()
{
  if (DEBUG)
    ev << "PHY: LISTEN" << endl;

  (check_and_cast<World*>(simulation.getModuleByPath("world")))->beginListening(this);
  switchOscilatorMode(LISTENING);
}

/*
 *   Callback after receiving
 */
void RadioDriver::received(Raw* raw)
{
  // consider bit error
//   if (!raw->hasBitError())
  {
    if (DEBUG)
      ev << "PHY: RECEIVED" << endl;

    sendMessageToUpper(raw->decapsulate());
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
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_LISTEN);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOn(ENERGEST_TYPE_IDLE,
          getIdPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, IDLE_COLOR);
      break;

    case LISTENING:
      this->status = LISTENING;
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_IDLE);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOn(ENERGEST_TYPE_LISTEN,
          getRxPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, LISTEN_COLOR);
      break;

    case RECEIVING:
      this->status = RECEIVING;
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_IDLE);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_TRANSMIT);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOn(ENERGEST_TYPE_LISTEN,
          getRxPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, RECEIVING_COLOR);
      break;

    case TRANSMITTING:
      this->status = TRANSMITTING;
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_IDLE);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOff(ENERGEST_TYPE_LISTEN);
      (check_and_cast<Energest*>(getParentModule()->getSubmodule("energest")))->energestOn(ENERGEST_TYPE_TRANSMIT,
          getTxPower());
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, TRANSMIT_COLOR);
      break;

    case POWER_DOWN: {
      this->status = POWER_DOWN;
      (&getParentModule()->getDisplayString())->setTagArg("i", 1, OFF_COLOR);

      // remove preferred parent connection
      IPv6* net = check_and_cast<IPv6*>(getParentModule()->getSubmodule("net"));
      if (net->rpl->rplDag.preferredParent != NULL)
      {
        char channelParent[20];
        sprintf(channelParent, "out %d to %d", this->getParentModule()->getId(),
        simulation.getModule(net->rpl->rplDag.preferredParent->neighborID)->getParentModule()->getId());
        getParentModule()->gate(channelParent)->setDisplayString("ls=,0");
      }

      break;
    }
  }
}
}  // namespace wsn_energy
