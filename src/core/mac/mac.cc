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
#define SIFS 0.000192 // 12 symbols
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
        case MAC_EXPIRE_IFS: /* expire IFS */
        {
          sendResult(MAC_FINISH_PHASE);
          break;
        } /* expire IFS*/

        case CHANNEL_CCA_REQUEST: /* perform CCA*/
        {
          sendCommand(CHANNEL_CCA_REQUEST);
          break;
        } /* perform CCA */

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

  /* create new buffer */
  frameBuffer = new Frame;
  frameBuffer->setKind(DATA);
  frameBuffer->setByteLength(frameBuffer->getHeaderLength());

  /*  meta data */
  frameBuffer->setNumberTransmission(0);

  /* WSN hack */
//  frameBuffer->setSenderMacAddress(this->getId());

  /* MAC - IP address */
//  if (check_and_cast<IpPacket*>(packet)->getRecverIpAddress() == 0)
//    frameBuffer->setRecverMacAddress(0);
//  else
//    frameBuffer->setRecverMacAddress(
//        simulation.getModule(check_and_cast<IpPacket*>(packet)->getRecverIpAddress())->getParentModule()->getModuleByPath(
//            ".mac")->getId());

  /* encapsulate */
  frameBuffer->encapsulate((IpPacket*) packet);

  /* backoff and CCA */
  deferPacket();

  if (DEBUG)
    ev << "Frame length: " << frameBuffer->getByteLength() << endl;
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
          // consider just send DIO
//          if ((check_and_cast<IpPacket*>(frameBuffer->getEncapsulatedPacket()))->getMessageCode() == NET_ICMP_RPL)
//          {
//            if ((check_and_cast<IpPacket*>(frameBuffer->getEncapsulatedPacket()))->getIcmpCode() == NET_ICMP_DIO)
//              sendResult(NET_DIO_SENT);
//            else if ((check_and_cast<IpPacket*>(frameBuffer->getEncapsulatedPacket()))->getIcmpCode() == NET_ICMP_DIS)
//              sendResult(NET_DIS_SENT);
//          }

          selfTimer(SIFS, MAC_EXPIRE_IFS);

          delete this->frameBuffer;
          break;
        } /* successful transmitting and receive ACK if needed */

        case RDC_SEND_NO_ACK:
          /* transmitting unicast but no ACK received */
        {
          // WSN need considering dead neighbor
          sendResult(MAC_SEND_DEAD_NEIGHBOR);

          selfTimer(SIFS, MAC_EXPIRE_IFS);

          delete this->frameBuffer;
          break;
        } /* callback after sending */

        case RDC_SEND_FATAL:
          /* fatal error, abort message */
        {
          selfTimer(0, MAC_EXPIRE_IFS);

          delete this->frameBuffer;
          break;
        } /* callback after sending */

        case RDC_SEND_COL:
          /* busy radio, defer packet */
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
  if (DEBUG)
    ev << "READY & SEND (MAC)" << endl;

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_SEND));

  sendMessageToLower(frameBuffer);
}

void MACdriver::receivePacket(Frame* frameMac)
{
  if (DEBUG)
    ev << "RECEIVE (MAC)" << endl;

  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(MAC_RECV));

  IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
  ipPacket->setKind(DATA);

  sendMessageToUpper(ipPacket);

  delete frameMac;
}

} /* namespace wsn_energy */
