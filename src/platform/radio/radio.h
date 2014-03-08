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

#ifndef RADIO_H_
#define RADIO_H_

#include <omnetpp.h>
#include "ipPacket_m.h"

#define POWER_TX 1
#define POWER_RX 2
#define POWER_SB 3

#define TRX_BROADCAST 0
#define RCX_BROADCAST 1
#define END_BROADCAST 2

namespace wsn_energy {

class Radio : public cSimpleModule
{
  private:
    virtual void transmit_on();
    virtual void transmit_off();
    virtual void receive_on();
    virtual void receive_off();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void finish();

  public:
    int trRange;
    int coRange;

    // on the air broadcast
    IpPacket *broadcastMessage;

    // neighbor list
    std::vector<int> neighbor;
};

} /* namespace wsn_energy */

#endif /* RADIO_H_ */
