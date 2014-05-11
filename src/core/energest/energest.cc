/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to energest.h
 */

#include <energest.h>
#include <radio.h>

#ifndef DEBUG
#define DEBUG 0
#endif

namespace wsn_energy {

Define_Module(Energest);

void Energest::initialize()
{
  for (int i = 0; i < ENERGEST_TYPE_MAX; i++)
  {
    this->capsuleIsActivated[i] = false;
    this->capsuleTotalTime[i] = 0;
    this->capsuleStartTime[i] = 0;
    this->power[i] = 0;
  }
  this->energestRemaining = MAXPOWER;
}

void Energest::handleMessage(cMessage *msg)
{
}

void Energest::finish()
{
}

void Energest::energestOn(int type, double power)
{
  this->capsuleStartTime[type] = simTime().dbl();
  this->capsuleIsActivated[type] = true;
  this->power[type] = power;
}

void Energest::energestOff(int type)
{
  if (this->capsuleIsActivated[type])
  {
    double consumeTime = simTime().dbl() - this->capsuleStartTime[type];

    if (DEBUG)
      ev << "Diff " << type << " :" << consumeTime << endl;

    // increase total time
    this->capsuleTotalTime[type] += consumeTime;

    // turn off capsule
    this->capsuleIsActivated[type] = false;

    // consume energy, in term off hour not second, because power is mAh
    this->energestRemaining -= consumeTime * power[type] / 3600.0;

    // residual energy
    // Turn off if below critical mode
    if (this->energestRemaining < MAXPOWER * CRITICAL)
      ((RadioDriver*) getParentModule()->getModuleByPath(".radio"))->switchOscilatorMode(POWER_DOWN);
  }
}

void Energest::update()
{
  for (int i = 0; i < ENERGEST_TYPE_MAX; i++)
  {
    bool resume = this->capsuleIsActivated[i];

    energestOff(i);

    if (resume)
      energestOn(i, this->power[i]);
  }
}
} /* namespace wsn_energy */
