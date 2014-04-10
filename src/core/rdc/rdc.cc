/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to rdc.h
 */

#include <rdc.h>
#include "packet_m.h"

namespace wsn_energy {

void RDCdriver::initialize()
{
}

void RDCdriver::finish()
{
}

void RDCdriver::processSelfMessage(cPacket* packet)
{
}

void RDCdriver::processUpperLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      this->buffer = new FrameRDC;
      this->buffer->setKind(DATA);

      this->buffer->encapsulate(packet);

      // WSN need duty cycling trigger here
      sendMessageToLower(buffer);
      sendCommand(RDC_SEND);

      break;
    } /* Data */

    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case CHANNEL_CCA_REQUEST: /* request CCA */
        {
          sendCommand(CHANNEL_CCA_REQUEST);
          break;
        } /* request CCA */

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

void RDCdriver::processLowerLayerMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case DATA: /* Data */
    {
      FrameMAC *frameMac = check_and_cast<FrameMAC*>(packet->decapsulate());
      frameMac->setKind(DATA);
      sendMessageToUpper(frameMac);

      // delete header
      delete packet;
      break;
    } /* Data */

    case RESULT: /* Result */
    {
      switch (check_and_cast<Result*>(packet)->getNote())
      {
        case CHANNEL_CLEAR: /* Channel is clear */
        {
          sendResult(CHANNEL_CLEAR);
          break;
        } /* Channel is busy */

        case CHANNEL_BUSY: /* Channel is clear */
        {
          sendResult(CHANNEL_BUSY);
          break;
        }/* Channel is busy */

        case PHY_TX_ERR: /* Internal error */
        {
          sendResult(PHY_TX_ERR);
          break;
        }/* Internal error */

        case PHY_TX_OK: /* callback after sending */
        {
          sendResult(PHY_TX_OK);
          break;
        }/* callback after sending */

        default:
          ev << "Unknown result" << endl;
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

void RDCdriver::on()
{
  sendCommand(RDC_LISTEN);
}

void RDCdriver::off()
{
  sendCommand(RDC_IDLE);
}

} /* namespace wsn_energy */
