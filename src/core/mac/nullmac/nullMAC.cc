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

void nullMAC::deferPacket(FrameMAC* frameMac)
{
  // WSN dismiss + announce failure duty
  IpPacket* ipPacket = new IpPacket;

  ipPacket = check_and_cast<IpPacket*>(frameMac->decapsulate());
  ipPacket->setNote(LAYER_NET_SEND_NOT_OK);
  send(ipPacket, gate("upperOut"));
  return;
}

void nullMAC::sendPacket(FrameMAC* frameMAC)
{
  send(frameMAC, gate("lowerOut"));
}

void nullMAC::receivePacket(FrameMAC* frame)
{
  send(frame, gate("upperOut"));
}

} /* namespace wsn_energy */
