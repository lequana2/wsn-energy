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

#ifndef __WSN_ENERGY_TRANSPORT_H_
#define __WSN_ENERGY_TRANSPORT_H_

#include <myModule.h>
#include <segment_m.h>
#include <data_m.h>

#ifndef UDP_PORT
#define UDP_PORT
#define UDP_SERVER_PORT 5678 // UDP port
#define UDP_CLIENT_PORT 8765 // UDP port
#endif

namespace wsn_energy {

class UDP : public myModule
{
  protected:
    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);
};

} //namespace

#endif
