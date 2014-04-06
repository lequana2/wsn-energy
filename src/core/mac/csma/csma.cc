/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to csma.h
 */

#include "csma.h"
#include "packet_m.h"

#define BACKOFF_PERIOD                0.00032 // second
#define MAC_MIN_BE                    3 // min backoff exponent
#define MAC_MAX_BE                    5 // max backoff exponent
#define MAXIMUM_BACKOFF_TRANSMISSION  3 // 3 tries per packet

namespace wsn_energy {

Define_Module(csma);

void csma::deferPacket()
{
  // dismiss + announce failure duty
  if (buffer->getNumberTransmission() > MAXIMUM_BACKOFF_TRANSMISSION)
  {
    IpPacket* ipPacket = new IpPacket;
    ipPacket->setNote(LAYER_NET_SEND_NOT_OK);
    sendMessageToUpper(ipPacket);
  }
  // unslotted csma
  else
  {
    double backoff;
    int backoff_transmission, backoff_exponent;

    backoff_exponent = MAC_MIN_BE + buffer->getNumberTransmission();
    if (backoff_exponent > MAC_MAX_BE)
      backoff_exponent = MAC_MAX_BE;

    backoff_transmission = 1 << backoff_exponent;

    backoff = (rand()%(backoff_transmission)) * BACKOFF_PERIOD;

    ev << "Random " << backoff << endl;

    buffer->setNumberTransmission(buffer->getNumberTransmission() + 1);

    /* request to perform CCA */
    FrameMAC *requestCCA = new FrameMAC;
    requestCCA->setNote(CHANNEL_CCA_REQUEST);
    scheduleAt(simTime() + backoff, requestCCA);
  }
}

} /* namespace wsn_energy */
