//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
  // WSN dismiss + announce failure duty
  if (frameMAC->getNumberTransmission() > MAXIMUM_BACKOFF_TRANSMISSION)
  {
    IpPacket* ipPacket = check_and_cast<IpPacket*>(frameMAC->decapsulate());
    ipPacket->setKind(LAYER_MAC);
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

    backoff = (rand() % backoff_transmission) * BACKOFF_PERIOD;

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
  frameMAC->setKind(LAYER_MAC);
  send(frameMAC, gate("upperOut"));
}

} /* namespace wsn_energy */
