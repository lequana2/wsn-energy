/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to nullMac.h
 */

#include "nullMAC.h"
#include "packet_m.h"

namespace wsn_energy {

Define_Module(nullMAC);

void nullMAC::deferPacket()
{
  if (buffer->getNumberTransmission() > 1)
  {
    IpPacket* ipPacket = check_and_cast<IpPacket*>(buffer->decapsulate());
    ipPacket->setNote(LAYER_NET_SEND_NOT_OK);
    sendMessageToUpper(ipPacket);
  }
  else
  {
    buffer->setNumberTransmission(buffer->getNumberTransmission() + 1);

    /* request to perform CCA */
    scheduleAt(simTime(), requestCCA);
  }
}

} /* namespace wsn_energy */
