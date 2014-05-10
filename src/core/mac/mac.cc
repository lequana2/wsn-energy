/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to mac.h
 */

#include <mac.h>
#include "packet_m.h"
#include "statistic.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef IFS
#define IFS
#define MAX_SIFS_FRAME_SIZE 18 // octets
#define SIFS 0.000192          // 12 symbols
#define LIFS 0.00064           // 40 symbols
#endif

namespace wsn_energy {

void MACdriver::finish()
{
  cancelAndDelete(buffer);
}

void MACdriver::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case MAC_CCA_REQUEST: /* perform CCA*/
        {
          sendCommand(MAC_CCA_REQUEST);
          break;
        } /* perform CCA */

        case MAC_EXPIRE_IFS: /* expire IFS */
        {
          sendResult(MAC_FINISH_PHASE);
          break;
        } /* expire IFS*/

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
      /* Command */
    }

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void MACdriver::processUpperLayerMessage(cPacket* packet)
{
  /* only process data packet */

  if (getModuleByPath("^.^")->par("usingHDC").boolValue())
  {
    // WSN compress using HC01
  }
  else
  {
    // intialisation
    buffer = new FrameDataStandard;
    buffer->setKind(DATA);
    buffer->setByteLength(buffer->getHeaderLength());

    /*  meta data */
    buffer->setNumberTransmission(0);

    // FCF
    buffer->setFrameType(FRAME_DATA);
    buffer->setPanIdCompression(false);

    // sequence number
    (check_and_cast<FrameDataStandard*>(buffer))->setDataSequenceNumber(this->sequenceNumber++);

    // address fields
    (check_and_cast<FrameDataStandard*>(buffer))->setSourceMacAddress(this->getId());

    if (check_and_cast<IpPacketStandard*>(packet)->getDestinationIpAddress() == 0)
    {
      (check_and_cast<FrameDataStandard*>(buffer))->setDestinationMacAddress(0);
      buffer->setAckRequired(false);
    }
    else
    {
      // using default route
      (check_and_cast<FrameDataStandard*>(buffer))->setDestinationMacAddress(
          simulation.getModule(check_and_cast<IpPacketStandard*>(packet)->getDestinationIpAddress())->getParentModule()->getModuleByPath(
              ".mac")->getId());
      buffer->setAckRequired(true);
    }
  }

  buffer->encapsulate(packet);

  // prepare a transmission phase
  sendMessageToLower(buffer->dup());
  sendCommand(MAC_ASK_SEND_FRAME);
}

void MACdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      receiveFrame(check_and_cast<Frame*>(packet)); // received message
      break;
    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* channel is clear */
        {
          sendFrame();
          break;
        } /* channel is clear */

        case CHANNEL_BUSY: /* channel is busy */
        {
          deferPacket();
          break;
        } /* channel is busy */

        case RDC_READY_TRANS_PHASE: /* successfully set up a transmission phase */
        {
          deferPacket();
          break;
        }/* successfully set up a transmission phase */

        case RDC_SEND_OK: /* successful transmitting and receive ACK if needed */
        {
          // consider IFS
          if (this->buffer->getByteLength() > MAX_SIFS_FRAME_SIZE)
            selfTimer(LIFS, MAC_EXPIRE_IFS);
          else
            selfTimer(SIFS, MAC_EXPIRE_IFS);

          delete this->buffer;
          break;
        } /* successful transmitting and receive ACK if needed */

        case RDC_SEND_NO_ACK: /* unicast but no ACK received */
        {
          // no ack is considered dead neighbor
          sendResult(MAC_SEND_DEAD_NEIGHBOR);

          selfTimer(SIFS, MAC_EXPIRE_IFS);

          delete this->buffer;
          break;
        } /* unicast but no ACK received */

        case RDC_SEND_FATAL: /* fatal error, abort message */
        {
          selfTimer(0, MAC_EXPIRE_IFS);

          delete this->buffer;
          break;
        } /* fatal error, abort message */

        case RDC_SEND_COL: /* busy radio */
        {
          deferPacket();
          break;
        } /* busy radio, defer packet */

        default:
          ev << "Missing note" << endl;
          break;
      }

      delete packet; // done result
      break;
    } /* Result */

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void MACdriver::sendFrame()
{
  if (DEBUG)
    ev << "MAC: begin 1 transmitting turn" << endl;

  /* begin a transmission turn */
  sendCommand(MAC_BEGIN_SEND_TURN);

  /* statistics */
  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_SEND));
}

void MACdriver::receiveFrame(Frame* frameMac)
{
  if (DEBUG)
    ev << "MAC: received" << endl;

  sendMessageToUpper(check_and_cast<IpPacketInterface*>(frameMac->decapsulate()));

  /* statistics */
  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_RECV));

  delete frameMac;
}

} /* namespace wsn_energy */
