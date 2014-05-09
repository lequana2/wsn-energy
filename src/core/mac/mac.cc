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

  /* backoff and CCA */
  deferPacket();

  if (DEBUG)
    ev << "Frame length: " << buffer->getByteLength() << endl;
}

void MACdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      receivePacket(check_and_cast<Frame*>(packet)); // received message
      break;
    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* channel is clear */
        {
          sendPacket();
          break;
        } /* channel is clear */

        case CHANNEL_BUSY: /* channel is busy */
        {
          deferPacket();
          break;
        } /* channel is busy */

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

        case RDC_SEND_NO_ACK: /* transmitting unicast but no ACK received */
        {
          // WSN need considering dead neighbor
          sendResult(MAC_SEND_DEAD_NEIGHBOR);

          selfTimer(SIFS, MAC_EXPIRE_IFS);

          delete this->buffer;
          break;
        } /* callback after sending */

        case RDC_SEND_FATAL: /* fatal error, abort message */
        {
          selfTimer(0, MAC_EXPIRE_IFS);

          delete this->buffer;
          break;
        } /* callback after sending */

        case RDC_SEND_COL: /* busy radio, defer packet */
        {
          if (DEBUG)
            std::cout << "PHY busy" << endl;
          deferPacket();
          break;
        } /* callback after sending */

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

void MACdriver::sendPacket()
{
  // WSN prepare a transmission phase
  // WSN wait until RDC is not busy then process
  // WSN if RDC is busy (receiving) then defer

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_SEND));

  sendMessageToLower(buffer);
}

void MACdriver::receivePacket(Frame* frameMac)
{
  if (DEBUG)
    ev << "RECEIVE (MAC)" << endl;

  /* statistics */
  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_RECV));

  sendMessageToUpper(check_and_cast<IpPacketInterface*>(frameMac->decapsulate()));

  delete frameMac;
}

} /* namespace wsn_energy */
