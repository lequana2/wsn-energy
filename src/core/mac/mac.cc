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
#include "ipv6.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

void MACdriver::initialize()
{
  this->bufferMAC = NULL;
  this->sequenceNumber = 0;
  this->linkLocalAddress = 0;
  this->defaultRoute = 0;
}

void MACdriver::finish()
{
  if (this->bufferMAC != NULL)
  {
    delete this->bufferMAC;
    this->bufferMAC = NULL;
  }
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
          // clear buffer
          if (this->bufferMAC != NULL)
          {
            delete this->bufferMAC;
            this->bufferMAC = NULL;
          }
//          std::cout << this->getFullPath() << " end mac " << simTime().dbl()
//              << " " << check_and_cast<IPv6*>(getModuleByPath("^.net"))->ipPacketQueue.size() << endl;
          sendResult(MAC_FINISH_PHASE);

          break;
        } /* expire IFS*/

        default:
          if (DEBUG)
            std::cout << "Unknown command" << endl;
          break;
      }
      break;
      /* Command */
    }

    default:
      if (DEBUG)
        std::cout << "Unknown kind" << endl;
      break;
  }

  delete packet;
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
    bufferMAC = new FrameDataStandard;
    bufferMAC->setKind(DATA);
    bufferMAC->setByteLength(bufferMAC->getHeaderLength());

    /*  meta data */
    bufferMAC->setNumberTransmission(0);

    // FCF
    bufferMAC->setFrameType(FRAME_DATA);
    bufferMAC->setPanIdCompression(false);

    // increase sequence number
    this->sequenceNumber++;

    // sequence number
    (check_and_cast<FrameDataStandard*>(bufferMAC))->setDataSequenceNumber(this->sequenceNumber);

    // address fields
    if (check_and_cast<IpPacketStandard*>(packet)->getDestinationIpAddress() == 0)
    {
      (check_and_cast<FrameDataStandard*>(bufferMAC))->setSourceMacAddress(this->getId());
      (check_and_cast<FrameDataStandard*>(bufferMAC))->setDestinationMacAddress(0);

      bufferMAC->setAckRequired(false);
    }
    else
    {
      // using default route
      int netDefaultRoute = (check_and_cast<IPv6*>(getModuleByPath("^.net")))->defaultRoute;

      if (netDefaultRoute == 0)
      {
        // fatal error, abort message
        std::cout << "FATAL NET ERROR" << endl;
        selfTimer(0, MAC_EXPIRE_IFS);
        return;
      }
      else
      {
        // using ARP
        defaultRoute = simulation.getModule(netDefaultRoute)->getModuleByPath("^.mac")->getId();

        (check_and_cast<FrameDataStandard*>(bufferMAC))->setSourceMacAddress(this->getId());
        (check_and_cast<FrameDataStandard*>(bufferMAC))->setDestinationMacAddress(defaultRoute);
      }

      bufferMAC->setAckRequired(true);
    }
  }

  bufferMAC->encapsulate(packet);

  /* statistics */
  if (bufferMAC->getAckRequired())
    (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_SEND));

  // prepare a MAC transmission phase
  sendMessageToLower(bufferMAC->dup());
  sendCommand(MAC_ASK_SEND_FRAME);
//  std::cout << this->getFullPath() << " begin mac" << simTime().dbl() << endl;
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
          // ready to enter a RDC phase
          igniteRDCphase();

          break;
        } /* channel is clear */

        case CHANNEL_BUSY: /* channel is busy */
        {
          // not ready enter a RDC phase
          deferPacket();

          break;
        } /* channel is busy */

        case RDC_READY_TRANS_PHASE: /* successfully set up a transmission phase */
        {
          // success enter a transmission phase, start by deferring packet
          deferPacket();

          break;
        }/* successfully set up a transmission phase */

        case RDC_SEND_OK: /* successful transmitting and receive ACK if needed */
        {
          // end MAC phase
          endMACphase();

          // consider IFS
          if (bufferMAC->getByteLength() > MAX_SIFS_FRAME_SIZE)
            selfTimer(LIFS, MAC_EXPIRE_IFS);
          else
            selfTimer(SIFS, MAC_EXPIRE_IFS);

          break;
        } /* successful transmitting and receive ACK if needed */

        case RDC_SEND_NO_ACK: /* unicast but no ACK received */
        {
          // no ack is considered dead neighbor
          sendResult(MAC_SEND_DEAD_NEIGHBOR);

          //std::cout << "NO ACK !!!" << endl;

          // end MAC phase
          endMACphase();

          // consider IFS
          if (bufferMAC->getByteLength() > MAX_SIFS_FRAME_SIZE)
            selfTimer(LIFS, MAC_EXPIRE_IFS);
          else
            selfTimer(SIFS, MAC_EXPIRE_IFS);

          break;
        } /* unicast but no ACK received */

        case RDC_SEND_FATAL: /* fatal error, abort message */
        {
          // end MAC phase
          endMACphase();
          std::cout << "FATAL ERROR" << endl;
          selfTimer(0, MAC_EXPIRE_IFS);

          break;
        } /* fatal error, abort message */

        case RDC_SEND_COL: /* busy radio */
        {
          // radio/channel is busy, defer packet
          deferPacket();

          break;
        } /* busy radio */

        default:
          delete packet;
          if (DEBUG)
            std::cout << "Missing note" << endl;
          break;
      }

      delete packet; // done result
      break;
    } /* Result */

    default:
      delete packet;
      if (DEBUG)
        std::cout << "Unknown kind" << endl;
      break;
  }
}

void MACdriver::igniteRDCphase()
{
  if (DEBUG)
    std::cout << "MAC: ignite RDC" << endl;

  /* begin a transmission turn */
  sendCommand(MAC_IGNITE_RDC);
}

void MACdriver::endMACphase()
{
  if (DEBUG)
    std::cout << "MAC: end transmission phase" << endl;

  /* told RDC end a transmission phase */
  sendCommand(MAC_END_SEND_FRAME);
}

void MACdriver::receiveFrame(Frame* frameMac)
{
  if (DEBUG)
    std::cout << "MAC: received" << endl;

  if (getModuleByPath("^.^")->par("usingHDC").boolValue())
  {
    // WSN compress using HC01
  }
  else
  {
    if (check_and_cast<FrameDataStandard*>(frameMac)->getDestinationMacAddress() == 0
        || check_and_cast<FrameDataStandard*>(frameMac)->getDestinationMacAddress() == getId())
    {
      // right MAC destination
      sendMessageToUpper(check_and_cast<IpPacketInterface*>(frameMac->decapsulate()));

      /* statistics */
      if (check_and_cast<FrameDataStandard*>(frameMac)->getDestinationMacAddress() == getId())
        (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_RECV));
    }
  }

  delete frameMac;
}

} /* namespace wsn_energy */
