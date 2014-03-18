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
  for (int i = 0; i < ENERGEST_TYPE_MAX; i++){
    this->capsuleTotalTime[i] = 0;
    this->capsuleIsActivated[i] = false;
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
    if (DEBUG)
    {
      char s[30];
      sprintf(s, "Different: %f", this->capsuleTotalTime[type]);
      ev << s << endl;
    }
    this->capsuleIsActivated[type] = false;
  }

  // cumulative
  for (int i = 0; i < ENERGEST_TYPE_MAX; i++){
   this->capsuleCumulativeEnergest += this->capsuleTotalTime[i];
  }

  if (DEBUG)
  {
    char s[30];
    sprintf(s, "%d: %f", this->getParentModule()->getId(), this->capsuleCumulativeEnergest);
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
