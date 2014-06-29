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
#include "data_m.h"

// define number of packet each sensor need to send
//#define MAX 60
//#define MAX 1

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(Client);

void Client::initialize()
{
  // set global address
  // simulate the pseudo-assigned MAC and IPv6 address creation

  // create MAC
  this->macAddress = new MacAddress(getId());

  // create self IPv6 sddress
  this->ipAddress = new IpAddress(this->macAddress);

  // set gloabl server address
  // network address aaaa::/64
  // suppose it is a MAC-48 from 64 bit by putting ff::fe to midle
  // server address aaaa::ff::fe:1
  this->serverAddress = new IpAddress(170, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 254, 0, 0, 1);

  if (DEBUG)
  {
    std::cout << this->getFullPath() << "has mac address ";
    this->macAddress->print();
    std::cout << this->getFullPath() << "has tentative link-local address ";
    this->ipAddress->print();
    std::cout << endl;
  }

  this->packetNumber = 0;

  /* Contiki test scheme */
  switch ((int) getModuleByPath("^.^")->par("scheme").doubleValue())
  {
    case 1: /* one manual event */
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
          // Timer for next message
          if ((int) getModuleByPath("^.^")->par("scheme").doubleValue() == 2)
          {
#ifdef MAX
            if (++this->packetNumber < MAX)  // control maximum number
#else
            ++this->packetNumber;
#endif
            newData();
          }

          break; /* new data */
        }

        case APP_READY_TO_SEND: /* ready to send */
        {
          // begin send data
          sendData();
          break;
        } /* ready to send */

        default:
          ev << "Unknown command" << endl;
          break;
      }
      delete packet; // done command
      break;
      /* Command */
    }

    default:
      delete packet;
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

/*
 * Start timer to begin to collect data
 */
void Client::newData()
{
  int sendInterval = 55; // seconds
  int restPeriod = 10; // seconds

  // avoid immediately sending + simulate not-synchronized clock
  double time = 0;

//  if (simTime() + sendInterval + restPeriod < getModuleByPath("^.^")->par("timeLimit").doubleValue())
    selfTimer(sendInterval + restPeriod, APP_SENSING_FLAG);

  if (getModuleByPath("^.^")->par("rand").doubleValue() == 0)
    time = (rand() % 10000) / 10000.0 * sendInterval;
  else if (getModuleByPath("^.^")->par("rand").doubleValue() == 1)
    time = intuniform(0, 10000) / 10000.0 * sendInterval;

  if (DEBUG)
    this->getParentModule()->bubble("Data");

//  if (simTime().dbl() + sendInterval < getModuleByPath("^.^")->par("timeLimit").doubleValue())
    selfTimer(time, APP_READY_TO_SEND);
}

/*
 * Collect data from outside world and send toward server
 */
void Client::sendData()
{
  // create data to send
  char buf[30];
  int len = sprintf(buf, "Hello %d from %s", packetNumber, getParentModule()->getFullName());

  // hack port, address
  int destinationPort = UDP_SERVER_PORT;
  int destinationAddress = simulation.getModuleByPath("server.net")->getId();

  sendMessage(buf, len, destinationPort, destinationAddress);

  /* End to end statistics */
  (check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(APP_SEND));
}

/*
 * Send messge API
 */
void Client::sendMessage(char *value, int len, int destinationPort, int destinationAddress)
{
  // intialisation
  Data *data = new Data;
  data->setKind(DATA);
  data->setByteLength(len);

  // meta-data
  data->setTime(simTime().dbl());

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
