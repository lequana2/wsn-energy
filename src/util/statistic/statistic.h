//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __TRACKINGWSN_STATCOLLECTOR_H_
#define __TRACKINGWSN_STATCOLLECTOR_H_

#include <omnetpp.h>

#ifndef DEF
#define DEF 1
#define APP_SEND 0
#define APP_RECV 1
#define NET_SEND 2
#define NET_RECV 3
#define MAC_SEND 4
#define MAC_RECV 5
#define RADIO_SEND 6
#define RADIO_RECV 7
#endif

namespace wsn_energy {

/**
 * Statistics Collector
 */
class Statistic : public cSimpleModule
{
  private:
    cMessage *polling; // Timer for polling total sensor energy
    cMessage *pollingCount; // Timer for polling total sensor energy (Hung's method)

    double numNetworkEnergyCount; // Energy of all network (Hung's method)
    simsignal_t sigNetworkEnergyCount;

    double numSensorEnergyCount; // Energy for each distributed node (Hung's method)
    simsignal_t sigSensorEnergyCount;

    double numNetworkEnergy; // Energy of all network
    simsignal_t sigNetworkEnergy;

    double numSensorEnergy; // Energy for each distributed node
    simsignal_t sigSensorEnergy;

    double numTotalEnergy;  // Energy remaining in whole network
    simsignal_t sigTotalEnergy;

    double numTotalDelay; // Total delayTime
    simsignal_t sigTotalDelay;

    int numRadioSend; // Number of radio message to send
    int numRadioRecv; // Number of failed radio sending
    simsignal_t sigRadioSend;
    simsignal_t sigRadioRecv;

    int numMacSend; // Number of frame to send
    int numMacRecv; // Number of failed frame sending
    simsignal_t sigMacSend;
    simsignal_t sigMacRecv;

    int numNetSend; // Number of IpPacket to send
    int numNetRecv; // Number of failed IpPacket sending
    simsignal_t sigNetSend;
    simsignal_t sigNetRecv;

    int numAppSend; // Number of data sending by client
    int numAppRecv; // Number of recv recving by server
    simsignal_t sigAppSend;
    simsignal_t sigAppRecv;

    double timeTrans;
    double timeListen;
    double timeIdle;

    simsignal_t sigTimeTrans;
    simsignal_t sigTimeListen;
    simsignal_t sigTimeIdle;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void finish();

  public:
    void pollTotalSensorEnergy();
    void pollTotalSensorEnergyCount();

    void packetRateTracking(int);
    void packetDelayTracking(double);
};
}
#endif
