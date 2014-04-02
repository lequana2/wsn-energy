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
    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);

    /* accept output from upperlayer*/
    virtual void sendPacket(FrameMAC*) = 0;
    /* backoff transmitting*/
    virtual void deferPacket(FrameMAC*) = 0;

    /* accept input from lowerlayer*/
    virtual void receivePacket(FrameMAC*) = 0;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
