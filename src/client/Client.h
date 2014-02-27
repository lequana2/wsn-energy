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

#ifndef __WSN_ENERGY_SOURCE_H
#define __WSN_ENERGY_SOURCE_H

#include <omnetpp.h>

namespace wsn_energy {

/**
 * Generates messages; see NED file for more info.
 */
class Client : public cSimpleModule
{
  public:
    int numOfSensors;
    int trRange;
    int ssRange;
    int redundancy;
    int axisX;
    int axisY;
    int energy;

  private:
    cMessage *timerMessage;
    bool flag;

  public:
     Client();
     virtual ~Client();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}; // namespace

#endif
