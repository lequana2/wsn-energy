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

//#define MAX 900

#ifndef SET_UP_DELAY_TIME
#define SET_UP_DELAY_TIME 65
#endif

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  this->numberOfPacket = 0;

  /* Contiki test scheme */
  switch ((int) getModuleByPath("^.^")->par("scheme").doubleValue())
  {
    case 1: /* one event */
    {
      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(SET_UP_DELAY_TIME + 10, APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(SET_UP_DELAY_TIME + 20, APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(SET_UP_DELAY_TIME + 30, APP_SENSING_FLAG);

      break;
    } /* one event */

    case 2: /* ignite periodically */
    {
      selfTimer(SET_UP_DELAY_TIME, RPL_SET_UP_DELAY);
      break;
    } /* ignite periodically */

    default:
      ev << "Just construct " << endl;
      break;
  }
}

void Client::processSelfMessage(cPacket* packet)
{
  switch (packet->getKind())
  {
    case COMMAND: /* Command */
    {
      switch (check_and_cast<Command*>(packet)->getNote())
      {
        case RPL_SET_UP_DELAY: /* set up delay */
        {
          newData();
          break;
        }/* set up delay*/

        case APP_SENSING_FLAG: /* new data */
        {
          Data *data = new Data;
          data->setKind(DATA);
          data->setTime(simTime().dbl());

          // WSN data to send
          char buf[30];
          sprintf(buf, "Hello %d from %d", numberOfPacket, this->getId());
          data->setValue(buf);
          data->setByteLength(8);

          sendMessageToLower(data);

          /* End to end statistics */
          (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(APP_SEND));

          if ((int) getModuleByPath("^.^")->par("scheme").doubleValue() == 2)
          {
#ifdef MAX
            if (this->numberOfPacket++ < MAX)  // control maximum number
#else
            this->numberOfPacket++;
#endif
            newData();
          }

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

  // avoid immediately sending + simulate not-synchronized clock
  double time = 0;

  if (getModuleByPath("^.^")->par("rand").doubleValue() == 0)
    time = sendInterval / 2 + (rand() % 1000000) / 2000000.0 * sendInterval;
  else if (getModuleByPath("^.^")->par("rand").doubleValue() == 1)
    time = sendInterval / 2 + intuniform(0, 1000000) / 2000000.0 * sendInterval;

//  this->getParentModule()->bubble("Data");

  selfTimer(time, APP_SENSING_FLAG);
}

}
;
// namespaces
