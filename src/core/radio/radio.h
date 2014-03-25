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

#ifndef SWITCH_MODE_DELAY
#define SWITCH_MODE_DELAY                  0        // second
#define SWITCH_MODE_DELAY_SLEEP_TO_TRANS   0.000002 // second
#define SWITCH_MODE_DELAY_SLEEP_TO_LISTEN  0.000002 // second
#define SWITCH_MODE_DELAY_TRANS_TO_LISTEN  0.000002 // second
#define SWITCH_MODE_DELAY_TRANS_TO_SLEEP   0.000002 // second
#define SWITCH_MODE_DELAY_LISTEN_TO_SLEEP  0.000002 // second
#define SWITCH_MODE_DELAY_LISTEN_TO_TRANS  0.000002 // second
#endif

#define SLEEPING        0 // do nothing
#define TRANSMITTING    1 // transmitting something
#define LISTENING       2 // listening to nothing
#define RECEIVING       3 // listening to something

#include <omnetpp.h>

#include "packet_m.h"

namespace wsn_energy {

class RadioDriver : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void finish();

    // Functioning
    virtual void transmit_on(Raw *raw) = 0;
    virtual void transmit_off() = 0;
    virtual void listen_off();
    virtual void listen_on();

    // CCA
    virtual bool isClearChannel() = 0;

    // power
    virtual double getTxPower() = 0;
    virtual double getRxPower() = 0;

    Raw *broadcastMessage; // buffer message

  public:
    int status; // sleep, transmitting, listening, receiving

    int trRange; // simulated transmission range
    int coRange; // simulated collission range

    std::vector<int> neighbor; // simulated neighbor list, for world util
};

} /* namespace wsn_energy */

#endif /* RADIO_H_ */