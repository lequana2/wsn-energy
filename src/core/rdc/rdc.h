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

#ifndef RDCDRIVER_H_
#define RDCDRIVER_H_

#include <omnetpp.h>
#include "packet_m.h"

namespace wsn_energy {

class RDCdriver : public cSimpleModule
{
  protected:
    FrameRDC *waitACK;
    bool isWaitingACK;

    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void finish();

    virtual void deferPacket(FrameRDC*) = 0;

    virtual void sendPacket(FrameRDC*) = 0;

    virtual void sendSuccess(FrameRDC*) = 0;
    virtual void sendFailure() = 0;

    virtual void receiveSuccess(FrameMAC*) = 0;
    virtual void receiveFailure() = 0;

    virtual void on() = 0;
    virtual void off() = 0;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
