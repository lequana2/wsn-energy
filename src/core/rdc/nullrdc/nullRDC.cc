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

#include "nullRDC.h"
#include "packet_m.h"

#ifndef  DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(nullRDC);

void nullRDC::deferPacket(cMessage* msg)
{
  msg->setKind(LAYER_RDC);
  ((Frame*) msg)->setTypeMacLayer(LAYER_RDC_RADIO_NOT_FREE);
  send(msg, gate("upperOut"));
}

void nullRDC::sendPacket(cMessage *msg)
{
  msg->setKind(LAYER_RDC);
  ((Frame*) msg)->setTypeMacLayer(LAYER_RDC_TURN_RADIO_TRANS);
  send(msg, gate("lowerOut"));
}

void nullRDC::sendSuccess()
{
  return;
}

void nullRDC::sendFailure()
{
  return;
}

void nullRDC::receiveSuccess(cMessage* msg)
{
  msg->setKind(LAYER_RDC);
  send(msg, gate("upperOut"));
  on(); // turn on listening upon receving success
}

void nullRDC::receiveFailure()
{
  return;
}

void nullRDC::on()
{
  Frame *msg = new Frame;
  msg->setKind(LAYER_RDC);
  msg->setTypeMacLayer(LAYER_RDC_TURN_RADIO_ON);

  send(msg, gate("lowerOut"));
}

void nullRDC::off()
{
  Frame *msg = new Frame;
  msg->setKind(LAYER_RDC);
  msg->setTypeMacLayer(LAYER_RDC_TURN_RADIO_OFF);

  send(msg, gate("lowerOut"));
}

} /* namespace wsn_energy */
