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

namespace wsn_energy {

class RDCdriver : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage*);
    virtual void finish();

    virtual void deferPacket(cMessage*) = 0;

    virtual void sendPacket(cMessage*) = 0;

    virtual void sendSuccess() = 0;
    virtual void sendFailure() = 0;

    virtual void receiveSuccess(cMessage*) = 0;
    virtual void receiveFailure() = 0;

    virtual void on()  = 0;
    virtual void off() = 0;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
