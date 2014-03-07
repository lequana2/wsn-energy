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
#include "core.h"

#define TX_POWER 0
#define RX_POWER 0

namespace wsn_energy {

class Radio : public cSimpleModule
{
  private:
    virtual void turnOn();
    virtual void turnOff();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);

  public:
    virtual void send(Core *sender, Core *recver, cMessage *msg);
};

} /* namespace wsn_energy */

#endif /* RADIO_H_ */