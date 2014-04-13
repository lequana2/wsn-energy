/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to client.h
 */

#include "client.h"
#include "radio.h"
#include "statistic.h"

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  this->numberOfPacket = 0;

  /* Contiki test scheme */
  switch ((int) getModuleByPath("WSN")->par("scheme").doubleValue())
  {
    case 1: /* one event */
    {
      Command *command = new Command;
      command->setKind(COMMAND);
      command->setNote(APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(1, APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(2, APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(3, APP_SENSING_FLAG);

      break;
    } /* one event */

    case 2: /* ignite periodically */
    {
      newData();
      break;
    } /* ignite periodically */

    default:
      ev << "Just construct " << endl;
      break;
  }
}

void Client::handleMessage(cMessage *msg)
{
  /* sensor stops working */
  if (check_and_cast<RadioDriver*>(this->getParentModule()->getModuleByPath(".radio")) == POWER_DOWN)
  {
    delete msg;
    return;
  }

  myModule::handleMessage(msg);
}

void Client::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case APP_SENSING_FLAG: /* new data */
        {
          Data *data = new Data;
          data->setKind(DATA);
          data->setTime(simTime().dbl());

          char buf[30];
          sprintf(buf, "Hello %d from %d", numberOfPacket, this->getId());
          data->setValue(buf); // WSN need to validate

          sendMessageToLower(data);

          /* End to end statistics */
          ((Statistic*) simulation.getModuleByPath("statistic"))->packetRateTracking(APP_SEND);

          if ((int) getModuleByPath("WSN")->par("scheme").doubleValue() == 2)
            if (this->numberOfPacket++ < MAX)  // control maximum number
              newData();
          break; /* new data */
        }

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
      /* Command */
    }

    default:
      ev << "Unknown kind" << endl;
      break;
  }
}

void Client::processUpperLayerMessage(cPacket*)
{
  /* Highest layer */
  return;
}

void Client::processLowerLayerMessage(cPacket*)
{
  return;
}

void Client::newData()
{
  int sendInterval = 4; // second
  int randomness = 4; // second

  // avoid immediately sending + simulate not-synchronized clock
  double time = 0;

  if (getModuleByPath("WSN")->par("rand").doubleValue() == 0)
    time = sendInterval + (rand() % (randomness * 1000)) / 1000.0;
  else if (getModuleByPath("WSN")->par("rand").doubleValue() == 1)
    time = sendInterval + intuniform(0, randomness * 1000) / 1000.0 / 1000;

//  this->getParentModule()->bubble("Data");

  selfTimer(time, APP_SENSING_FLAG);
//  selfTimer(4, APP_SENSING_FLAG);
}

}
;
// namespaces
