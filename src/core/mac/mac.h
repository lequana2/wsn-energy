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

#ifndef MACDRIVER_H_
#define MACDRIVER_H_

#include "myModule.h"

namespace wsn_energy {

class MACdriver : public myModule
{
  protected:
    FrameMAC *buffer;
    FrameMAC *requestCCA;

    void initialize();
    void finish();

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);

    /* backoff transmitting*/
    virtual void deferPacket() = 0;

    /* accept output from upperlayer*/
    virtual void sendPacket();

    /* accept input from lowerlayer*/
    virtual void receivePacket(FrameMAC*);
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
