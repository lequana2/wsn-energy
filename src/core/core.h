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

#include "rpl.h"

// PACKET
#define IP_PACKET 1

// EVENT
#define ICMP_SOLICIT  2
#define RPL_CONSTRUCT 4
#define DATA_FORWARD  3
#define FIN_TRANSMISS 5

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

    //on the air broadcast
    IpPacket *broadcastMessage;

    //WSN default route to server
    std::list<int> route;

    void broadcast(IpPacket*);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void finish();
};

}
;
// namespace

#endif /* CORE_H_ */
