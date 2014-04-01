/*
 * energest.h
 *
 *  Created on: Mar 5, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include <omnetpp.h>
#include <packet_m.h>

// Power unit = Watts (mWh)
#define OPERATION_POWER          1000.0 // mAh
#define OPERATION_VOLTAGE           1.5 // Voltage

enum ENERGEST_TYPE
{
  ENERGEST_TYPE_CPU,
  ENERGEST_TYPE_TRANSMIT,
  ENERGEST_TYPE_LISTEN,
  ENERGEST_TYPE_IDLE,
  ENERGEST_TYPE_SENSORS,
  ENERGEST_TYPE_MAX,
};

namespace wsn_energy {

class Energest : public cSimpleModule
{
  private:
    double capsuleStartTime[ENERGEST_TYPE_MAX];
    double power[ENERGEST_TYPE_MAX];
    bool capsuleIsActivated[ENERGEST_TYPE_MAX];

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  public:
    double energestRemaining;
    double capsuleTotalTime[ENERGEST_TYPE_MAX];

    void update();
    void energestOn(int, double);
    void energestOff(int);
};

} /* namespace wsn_energy */

#endif /* BATTERY_H_ */
