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

#include "packet_m.h"

namespace wsn_energy {

class RadioDriver : public cSimpleModule
{
//  private:
//    virtual void transmit_on(Raw *raw);
//    virtual void transmit_off();
//    virtual void receive_off();
//    virtual void receive_on();
//
//    Raw *broadcastMessage; // buffer message

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
    bool isListening;
    bool isReceiving;
    bool isTransmitting;
    bool isPending;
    int trRange;
    int coRange;
    std::vector<int> neighbor; // simulated neighbor list, for world util
};

} /* namespace wsn_energy */

#endif /* RADIO_H_ */
