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

#ifndef __WSN_ENERGY_TEST_H_
#define __WSN_ENERGY_TEST_H_

#include <omnetpp.h>
#include <packet_m.h>

namespace wsn_energy {

class myModule : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    virtual void processSelfMessage(cPacket*) = 0;
    virtual void processUpperLayerMessage(cPacket*) = 0;
    virtual void processLowerLayerMessage(cPacket*) = 0;

    void sendMessageToUpper(cPacket*);
    void sendMessageToLower(cPacket*);
};

} //namespace

#endif
