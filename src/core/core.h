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

#ifndef CORE_H_
#define CORE_H_

#include <omnetpp.h>
#include <list>

#include "ipPacket_m.h"
#include "rpl.h"

// PACKET
#define ICMP_MESSAGE 1
#define ICMP_SOLICIT 2

// EVENT
#define END_BROADCAST 5
#define RPL_CONSTRUCT 4
#define DATA_FORWARD 3

namespace wsn_energy {

class Core : public cSimpleModule
{
  public:
    int numberClient;
    int trRange;
    int coRange;
    int redundancy;
    int axisX;
    int axisY;
    int energy;

    //WSN RPL
    RPL *rpl;

    std::vector<int> neighbor;

    //on the ải broadcast
    IpPacket *broadcastMessage;

    //WSN default route to server
    std::list<int> route;

    void broadcast(IpPacket*);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);
};

}
;
// namespace

#endif /* CORE_H_ */