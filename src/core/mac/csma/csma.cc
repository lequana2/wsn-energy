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

void csma::deferPacket(FrameMAC* frameMAC)
{
  // dismiss + announce failure duty
  if (frameMAC->getNumberTransmission() > MAXIMUM_BACKOFF_TRANSMISSION)
  {
    IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMAC->decapsulate());
    ipPacket->setNote(LAYER_NET_SEND_NOT_OK);

    send(ipPacket, gate("upperOut"));
  }
  else
  {
    double backoff;
    int backoff_transmission, backoff_exponent;

    backoff_exponent = MAC_MIN_BE + frameMAC->getNumberTransmission();
    if (backoff_exponent > MAC_MAX_BE)
      backoff_exponent = MAC_MAX_BE;

    backoff_transmission = 1 << backoff_exponent;

    backoff = (intrand(backoff_transmission)) * BACKOFF_PERIOD;

    ev << "Random " << backoff << endl;

    sendDelayed(frameMAC, backoff, gate("lowerOut"));

    frameMAC->setNumberTransmission(frameMAC->getNumberTransmission() + 1);
  }
}

void csma::sendPacket(FrameMAC* frameMAC)
{
  frameMAC->setNumberTransmission(0);

  deferPacket(frameMAC);
}

void csma::receivePacket(FrameMAC* frameMAC)
{
  // WSN decapsule ???
  send(frameMAC, gate("upperOut"));
}

} /* namespace wsn_energy */
