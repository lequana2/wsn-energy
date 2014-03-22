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
    double capsuleCumulativeEnergest;

    Battery();
    virtual ~Battery();

    void energestOn(int);
    void energestOff(int);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  private:
    double capsuleTotalTime[ENERGEST_TYPE_MAX];
    double capsuleStartTime[ENERGEST_TYPE_MAX];
    bool capsuleIsActivated[ENERGEST_TYPE_MAX];
};

} /* namespace wsn_energy */

#endif /* BATTERY_H_ */
