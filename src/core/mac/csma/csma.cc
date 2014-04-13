/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to csma.h
 */

#include "csma.h"
#include "packet_m.h"

#define BACKOFF_PERIOD                0.00032 // second, 20 symbols
#define MAC_MIN_BE                    3 // min backoff exponent
#define MAC_MAX_BE                    5 // max backoff exponent
#define MAX_BACKOFF_TRANSMISSION      3 // 3 tries per packet

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(csma);

void csma::deferPacket()
{
  /* dismiss + announce failure duty */
  if (buffer->getNumberTransmission() > MAX_BACKOFF_TRANSMISSION)
  {
    sendResult(MAC_SEND_ERROR);
    delete buffer;     // clear buffer
  }
  /* unslotted csma */
  else
  {
    double backoff;
    int backoff_transmission, backoff_exponent;

    backoff_exponent = MAC_MAX_BE < buffer->getNumberTransmission() + MAC_MIN_BE ? MAC_MAX_BE : buffer->getNumberTransmission() + MAC_MIN_BE; // truncate

    backoff_transmission = 1 << backoff_exponent;

    if (getModuleByPath("WSN")->par("rand").doubleValue() == 0)
      backoff = (rand() % (backoff_transmission)) * BACKOFF_PERIOD;
    else if (getModuleByPath("WSN")->par("rand").doubleValue() == 1)
      backoff = (intuniform(0,backoff_transmission)) * BACKOFF_PERIOD;

    if (DEBUG)
      ev << "Random " << backoff_exponent << "/" << backoff_transmission << "/" << backoff << endl;

    buffer->setNumberTransmission(buffer->getNumberTransmission() + 1);

    /* request to perform CCA */
    selfTimer(backoff, CHANNEL_CCA_REQUEST);
  }
}

} /* namespace wsn_energy */
