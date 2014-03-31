/*
 * battery.cpp
 *
 *  Created on: Mar 5, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#include <battery.h>

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
    this->power[i] = 0;
  }
  this->energestRemaining = OPERATION_POWER * OPERATION_VOLTAGE;
}

void Battery::energestOn(int type, double power)
{
  this->capsuleStartTime[type] = simTime().dbl();
  this->capsuleIsActivated[type] = true;
  this->power[type] = power;
}

void Battery::energestOff(int type)
{
  if (this->capsuleIsActivated[type])
  {
    double consumeTime = simTime().dbl() - this->capsuleStartTime[type];

    // consume energy
    // calculate in term off hour not second
    this->energestRemaining -= consumeTime * power[type] / 3600.0;

    // increase total time
    this->capsuleTotalTime[type] += consumeTime;

    // turn off capsule
    this->capsuleIsActivated[type] = false;
  }
  else
  {
    return;
  }
}
} /* namespace wsn_energy */
