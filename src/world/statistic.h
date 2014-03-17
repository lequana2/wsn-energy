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

namespace wsn_energy {

/**
 * Statistics Collector
 */
class Statistic : public cSimpleModule
{
  private:
    cMessage *polling; // Timer for polling total sensor energy

    int numRecvPacket; // Number of successfully received packets
    int numLostPacket; // Number of lost packets
    int numSensData; // Number of data sending by client
    int numRecvData; // Number of data recving by server

    simsignal_t totalSensorEnergySignal;

    simsignal_t sigRecvPacket;
    simsignal_t sigLostPacket;
    simsignal_t sigSensData;
    simsignal_t sigRecvData;

    /**
     * Record remaining energy of sensor nodes
     */
    void recRemainingEnergy();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    Statistic();
    ~Statistic();

    /* Calculate total energy and emit it */
    void pollTotalSensorEnergy();

    /* Increase number of successfully received packets (payload frames) */
    void incRecvPacket();
    /* Increase number of lost packets (payload frames) */
    void incLostPacket();

    /* Increase number of data send by mote (payload frames) */
    void incSensData();
    /* Increase number of data recv by server (payload frames) */
    void incRecvData();

    void finish();
};
}
#endif
