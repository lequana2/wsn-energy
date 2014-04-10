/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to myModule.h
 */

#include "myModule.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

void myModule::initialize()
{
}

void myModule::handleMessage(cMessage *msg)
{
  if (msg->isSelfMessage())
  {
    if (DEBUG)
      ev << this->getClassName() << " received a self-message" << endl;
    this->processSelfMessage(check_and_cast<cPacket*>(msg));
  }
  else if (msg->arrivedOn("upperIn"))
  {
    if (DEBUG)
      ev << this->getClassName() << " received an upper-layer-message" << endl;
    this->processUpperLayerMessage(check_and_cast<cPacket*>(msg));
  }
  else if (msg->arrivedOn("lowerIn"))
  {
    if (DEBUG)
      ev << this->getClassName() << " received a lower-layer-message" << endl;
    this->processLowerLayerMessage(check_and_cast<cPacket*>(msg));
  }
}

void myModule::finish()
{
}

void myModule::sendMessageToUpper(cPacket* packet)
{
  send(packet, gate("upperOut"));
}

void myModule::sendMessageToLower(cPacket* packet)
{
  send(packet, gate("lowerOut"));
}

void myModule::sendCommand(int commandCode)
{
  Command *command = new Command;
  command->setNote(commandCode);
  sendMessageToLower(command);
}

void myModule::sendResult(int resultCode)
{
  Result *result = new Result;
  result->setNote(resultCode);
  sendMessageToUpper(result);
}

void myModule::selfTimer(int countdownSeconds, int commandCode)
{
  Command *command = new Command;
  command->setNote(commandCode);
  scheduleAt(simTime() + countdownSeconds, command);
}

} //namespace
