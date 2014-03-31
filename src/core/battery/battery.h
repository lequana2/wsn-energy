/*
 * battery.h
 *
 *  Created on: Mar 5, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#ifndef BATTERY_H_
#define BATTERY_H_

// Power unit = Watts (mWh)
#define OPERATION_POWER          1000.0 // mAh
#define OPERATION_VOLTAGE           1.5 // Voltage

enum ENERGEST_TYPE
{
  ENERGEST_TYPE_CPU, ENERGEST_TYPE_TRANSMIT, ENERGEST_TYPE_LISTEN, ENERGEST_TYPE_SENSORS, ENERGEST_TYPE_MAX,
};

#include <omnetpp.h>
#include <packet_m.h>

namespace wsn_energy {

class Battery : public cSimpleModule
{
  public:
    double energestRemaining;

    Battery();

    void energestOn(int, double);
    void energestOff(int);
    void update();

  private:
    double capsuleTotalTime[ENERGEST_TYPE_MAX];
    double capsuleStartTime[ENERGEST_TYPE_MAX];
    double power[ENERGEST_TYPE_MAX];
    bool capsuleIsActivated[ENERGEST_TYPE_MAX];
};

} /* namespace wsn_energy */

#endif /* BATTERY_H_ */
