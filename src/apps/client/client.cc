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
#define MAX 2

#ifndef DEBUG
#define DEBUG 0
#endif

// WSN set global address
//
// SELF ADDRESS
// uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
//  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
//  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
//
// SERVER ADDRESS
//#if 0
///* Mode 1 - 64 bits inline */
//   uip_ip6addr(&server_ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 1);
//#elif 1
///* Mode 2 - 16 bits inline */
//  uip_ip6addr(&server_ipaddr, 0xaaaa, 0, 0, 0, 0, 0x00ff, 0xfe00, 1);
//#else
///* Mode 3 - derived from server link-local (MAC) address */
//  uip_ip6addr(&server_ipaddr, 0xaaaa, 0, 0, 0, 0x0250, 0xc2ff, 0xfea8, 0xcd1a); //redbee-econotag
//#endif

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  this->packetOrder = 0;

  /* Contiki test scheme */
  switch ((int) getModuleByPath("^.^")->par("scheme").doubleValue())
  {
    case 1: /* one event */
    {
      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(getModuleByPath("^.^")->par("setupDelay").doubleValue() + 10, APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(getModuleByPath("^.^")->par("setupDelay").doubleValue() + 20, APP_SENSING_FLAG);

      if (this->getParentModule()->getId() == simulation.getModuleByPath("client[54]")->getId())
        selfTimer(getModuleByPath("^.^")->par("setupDelay").doubleValue() + 30, APP_SENSING_FLAG);

      break;
    } /* one event */

    case 2: /* ignite periodically */
    {
      selfTimer(getModuleByPath("^.^")->par("setupDelay").doubleValue(), RPL_SET_UP_DELAY);
      break;
    } /* ignite periodically */

    default:
      if (DEBUG)
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
          // create data to send
          char buf[30];
          int len = sprintf(buf, "Hello %d from %d", packetOrder, this->getId());

          // hack port, address
          int destinationPort = UDP_SERVER_PORT;
          int destinationAddress = simulation.getModuleByPath("server.net")->getId();

          sendMessage(buf, len, destinationPort, destinationAddress);

          /* End to end statistics */
          (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(APP_SEND));

          // Timer for next message
          if ((int) getModuleByPath("^.^")->par("scheme").doubleValue() == 2)
          {
#ifdef MAX
            if (this->packetOrder++ < MAX)  // control maximum number
#else
            this->packetOrder++;
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
}

void Client::newData()
{
  int sendInterval = 4; // second

  // avoid immediately sending + simulate not-synchronized clock
  double time = 0;

  if (getModuleByPath("^.^")->par("rand").doubleValue() == 0)
    time = sendInterval / 2 + (rand() % 1000000) / 2000000.0 * sendInterval;
  else if (getModuleByPath("^.^")->par("rand").doubleValue() == 1)
//    time = sendInterval / 2 + intuniform(0, 1000000) / 2000000.0 * sendInterval;
    time = intuniform(0, 1000000) / 1000000.0 * sendInterval;

  if (DEBUG)
    this->getParentModule()->bubble("Data");

  selfTimer(time, APP_SENSING_FLAG);
}

void Client::sendMessage(char *value, int len, int destinationPort, int destinationAddress)
{
  // intialization
  Data *data = new Data;
  data->setKind(DATA);

  // meta-data
  data->setTime(simTime().dbl());
  data->setPayloadLength(len);

  // control-data
  data->setDestinationPort(destinationPort);
  data->setDestinationIPAddress(destinationAddress);

  // data
  data->setValue(value);

  sendMessageToLower(data);
}

}
;
// namespaces
