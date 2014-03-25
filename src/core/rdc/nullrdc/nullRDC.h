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

#ifndef RDC_H_
#define RDC_H_

#define WAIT_FOR_ACK 0.004 // s

#include "rdc.h"
#include "packet_m.h"

namespace wsn_energy {

class nullRDC : public RDCdriver
{
  protected:
    virtual void deferPacket(cMessage*);

    virtual void sendPacket(cMessage*);

    virtual void sendSuccess(cMessage*);
    virtual void sendFailure();

    virtual void receiveSuccess(cMessage*);
    virtual void receiveFailure();

    virtual void on();
    virtual void off();
};

} /* namespace wsn_energy */

#endif /* RDC_H_ */
