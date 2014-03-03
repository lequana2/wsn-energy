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

#ifndef __WSN_ENERGY_SINK_H
#define __WSN_ENERGY_SINK_H

#include <omnetpp.h>
#include "core.h"

namespace wsn_energy {

/**
 * Message sink; see NED file for more info.
 */
class Server: public Core
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  private:
    // state
//    simtime_t lastArrival;

    // statistics
//    cDoubleHistogram iaTimeHistogram;
//    cOutVector arrivalsVector;

};

}; // namespace

#endif
