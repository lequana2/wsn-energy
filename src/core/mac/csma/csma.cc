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

#define MAXIMUM_TRANSMISSION     3 // 3 tries per packet
#define MAXIMUM_BACKOFF_EXPONENT 3 // maxium backoff exponent

namespace wsn_energy {

Define_Module(csma);

void csma::deferPacket(FrameMAC* frameMAC)
{
  // WSN dismiss + announce failure duty
  if (frameMAC->getNumberTransmission() > MAXIMUM_TRANSMISSION)
  {
    IpPacket* ipPacket = new IpPacket;

    ipPacket = check_and_cast<IpPacket*>(frameMAC->decapsulate());
    ipPacket->setKind(LAYER_MAC);
    ipPacket->setNote(LAYER_NET_SEND_NOT_OK);
    send(ipPacket, gate("upperOut"));
  }
  else
  {
    sendPacket(frameMAC);
  }
}

void csma::sendPacket(FrameMAC* frameMAC)
{
  frameMAC->setNumberTransmission(frameMAC->getNumberTransmission() + 1);

  int sendTime, backoff_transmission, backoff_exponent;

  sendTime = 16; // 1 symbol

  backoff_exponent = frameMAC->getNumberTransmission();

  // Truncate the exponent if needed
  if (backoff_exponent > MAXIMUM_BACKOFF_EXPONENT)
    backoff_exponent = MAXIMUM_BACKOFF_EXPONENT;

  backoff_transmission = 1 << backoff_exponent;

  // Pick a time for next transmission, within the interval
  // [time, time + 2^backoff_exponent * time]
  sendTime = sendTime + (rand() % (backoff_transmission * sendTime));

  // Convert from nanosecond to second
  double backoff = sendTime / 1000000.0;

  ev << "Random " << backoff << endl;

  sendDelayed(frameMAC, simTime() + backoff, gate("lowerOut"));
}

void csma::receivePacket(FrameMAC* frame)
{
  frame->setKind(LAYER_MAC);
  send(frame, gate("upperOut"));
}

} /* namespace wsn_energy */
