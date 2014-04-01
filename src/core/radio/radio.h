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

#include "myModule.h"

#ifndef HARDWARE
#define HARDWARE                           1
#define SWITCH_MODE_DELAY                  0              // second
#define SYMBOL                             0.000016       // 1 symbol = 4/250 millisecond
#define SWITCH_MODE_DELAY_IDLE_TO_TRANS    SYMBOL*12      // 12 symbol
#define SWITCH_MODE_DELAY_IDLE_TO_LISTEN   SYMBOL*12      // 12 symbol
#define SWITCH_MODE_DELAY_TRANS_TO_LISTEN  SYMBOL*24      // 24 symbol
#define SWITCH_MODE_DELAY_TRANS_TO_IDLE    SYMBOL*0       // 0 symbol
#define SWITCH_MODE_DELAY_LISTEN_TO_TRANS  SYMBOL*24      // 24 symbol
#define SWITCH_MODE_DELAY_LISTEN_TO_IDLE   SYMBOL*0       // 0 symbol
#define DATA_RATE                          250000.0       // bit per second
#endif

#ifndef COLORIZE
#define COLORIZE 1
#define OFF_COLOR      "black"
#define IDLE_COLOR     "gray"
#define TRANSMIT_COLOR "blue"
#define LISTEN_COLOR   "yellow"
#define RECEIVE_COLOR  "orange"
#endif

#define POWER_DOWN      0 // power down
#define IDLE            1 // do nothing
#define TRANSMITTING    2 // transmitting something
#define LISTENING       3 // listening to nothing
#define RECEIVING       4 // listening to something

namespace wsn_energy {

class RadioDriver : public myModule
{
  private:
    Raw *bufferTXFIFO; // buffered transmit mode(TX_MODE 0) 128 bytes TXFIFO, in CC2420 RAM

    // Switch oscilator mode
    void switchOscilatorMode(int mode);

    // Self functioning
    void transmit_on(Raw*);
    void transmit_off();
    void listen();
    void receive(Raw*);
    void sleep();

    // power
    virtual double getTxPower() = 0;
    virtual double getRxPower() = 0;
    virtual double getIdPower() = 0;

    // CCA
    virtual void performCCA() = 0;

  protected:
    void initialize();
    void handleMessage(cMessage*);
    void finish();

    // processing
    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

  public:
    int status;  // sleep, transmitting, listening, receiving
    int trRange; // simulated transmission range according to TXPOWER
    int coRange; // simulated collission range according to RXPOWER

    std::vector<int> neighbor; // WSN simulated neighbor list, for world util. Is this necessary ???
};

} /* namespace wsn_energy */

#endif /* RADIO_H_ */
