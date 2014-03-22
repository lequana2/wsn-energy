/*
 * battery.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#include <battery.h>
#include "cc2420-const.h"

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(Battery);

Battery::Battery()
{
  for (int i = 0; i < ENERGEST_TYPE_MAX; i++)
  {
    this->capsuleIsActivated[i] = false;
    this->capsuleTotalTime[i] = 0;
    this->capsuleStartTime[i] = 0;
  }
  this->capsuleCumulativeEnergest = 0;
}

Battery::~Battery()
{
  // TODO Auto-generated destructor stub
}

void Battery::energestOn(int type)
{
  this->capsuleStartTime[type] = simTime().dbl();
  this->capsuleIsActivated[type] = true;
}

void Battery::energestOff(int type)
{
  if (this->capsuleIsActivated[type])
  {
    this->capsuleTotalTime[type] += simTime().dbl() - this->capsuleStartTime[type];
    this->capsuleIsActivated[type] = false;
  }
  else
  {
    return;
  }

  // Update
  switch (type)
  {
    case ENERGEST_TYPE_TRANSMIT:
      this->capsuleCumulativeEnergest += (simTime().dbl() - this->capsuleStartTime[type]) * TXPOWER_CURRENT * VOLTAGE;
      break;
    case ENERGEST_TYPE_LISTEN:
      this->capsuleCumulativeEnergest += (simTime().dbl() - this->capsuleStartTime[type]) * RXPOWER_CURRENT * VOLTAGE;
      break;
  }

  if (DEBUG)
  {
    char s[30];
    sprintf(s, "%d: %f", type, this->capsuleTotalTime[type]);
    ev << s << endl;
  }
}

void Battery::initialize()
{
}

void Battery::handleMessage(cMessage *msg)
{
}

void Battery::finish()
{
}

} /* namespace wsn_energy */
