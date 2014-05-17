/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Capsulating operation time of each mode
 */

#ifndef ENERGEST_H_
#define ENERGEST_H_

#include <omnetpp.h>

// Power unit = Watts (mWh)
#define BATTERY_NUMBER                2 // use 2 batteries
#define OPERATION_POWER          1000.0 // mAh
#define OPERATION_VOLTAGE           1.5 // Voltage
#define RESIDUAL                      1 // 100%
//#define CRITICAL                    0.1 // 10 %
#define CRITICAL                      0 // 0 %

#define MAX_POWER    OPERATION_POWER * OPERATION_VOLTAGE * BATTERY_NUMBER

// CPU power
// is this really need if using Sky mote with intergrated cc2420 coupled with msp430 ?
#define MSP430_CURRENT 0.5 // mA
#define MSP430_VOLTAGE   3 // Vcc
#define MSP430_POWER   MSP430_CURRENT*MSP430_VOLTAGE

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
