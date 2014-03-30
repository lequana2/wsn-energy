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

void nullRDC::deferPacket(FrameRDC* msg)
{
  // WSN If not sending ack
//  msg->setKind(LAYER_RDC);
//  ((Frame*) msg)->setTypeMacLayer(LAYER_RDC_RADIO_NOT_FREE);
//  send(msg, gate("upperOut"));
}

void nullRDC::sendPacket(FrameRDC* frame)
{
  // send data and wait ack
//  if (frame->getByteLength() != ACK_HEADER_FOOTER_LEN)
//  {
//    frame->setKind(LAYER_RDC);
//    frame->setTypeMacLayer(LAYER_RDC_TURN_RADIO_);
//    send(frame, gate("lowerOut"));

// WSN After transmitting
//    waitACK->setKind(LAYER_RDC);
//    waitACK->setTypeMacLayer(LAYER_RDC_WAIT_ACK);
//    scheduleAt(simTime() + WAIT_FOR_ACK, waitACK);
//    isWaitingACK = true;
//  }
  // send ack
//  else
//  {
//    msg->setKind(LAYER_RDC);
//    ((Frame*) msg)->setTypeMacLayer(LAYER_RDC_TURN_RADIO_TRANS);
//    send(msg, gate("lowerOut"));
//  }
}

void nullRDC::sendSuccess(FrameRDC* frame)
{
  // Turn on to waiting for ACK
  //  if (((Frame*) msg)->getLen() != ACK_HEADER_FOOTER_LEN)
  on();
  return;
}

void nullRDC::sendFailure()
{
  return;
}

void nullRDC::receiveSuccess(FrameMAC* frame)
{
  // WSN receive ACK
//  if (frame->getByteLength() == ACK_HEADER_FOOTER_LEN)
//  {
//    // process ACK
//    ev << "Receive ACK" << endl;
//
//    // omit pending
//    if (waitACK != NULL)
//      cancelEvent(waitACK);
//    isWaitingACK = false;
//
//    // Turn off upon receiving ACK
//    off();
//  }
  // WSN receive data = send ACK + process to upper layer
//  else
//  {
  // send ACK
  //    Frame* ack = new Frame;
  //    ack->setKind(LAYER_RDC);
  //    ack->setLen(ACK_LEN);
  //    ack->setTypeMacLayer(LAYER_RDC_CHECK_FREE);
  //    send(ack, gate("lowerOut"));
//
  // process to upper layer
//    frame->setKind(LAYER_RDC);
//    frame->setCommandMacLayer(LAYER_RDC_RECV_OK);
//    send(frame, gate("upperOut"));
//
  // turn on to listening
//    on();
//  }
}

void nullRDC::receiveFailure()
{
  return;
}

void nullRDC::on()
{
  FrameRDC *frame = new FrameRDC;
  frame->setKind(LAYER_RDC);
  frame->setNote(LAYER_RDC_LISTEN_ON);

  send(frame, gate("lowerOut"));
}

void nullRDC::off()
{
  FrameRDC *frame = new FrameRDC;
  frame->setKind(LAYER_RDC);
  frame->setNote(LAYER_RDC_LISTEN_OFF);

  send(frame, gate("lowerOut"));
}

} /* namespace wsn_energy */
