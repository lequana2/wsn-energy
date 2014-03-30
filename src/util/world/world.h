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

#ifndef ENVIROMENT_H_
#define ENVIROMENT_H_

#ifndef COLORIZE
#define COLORIZE 1
#define OFF_COLOR      "black"
#define IDLE_COLOR     "gray"
#define TRANSMIT_COLOR "blue"
#define LISTEN_COLOR   "yellow"
#define RECEIVE_COLOR  "orange"
#endif

#include <omnetpp.h>

#include "transmission.h"

namespace wsn_energy {

class World : public cSimpleModule
{
  private:
    void arrangeNodes(); // Arrange nodes in positions
    void connectNodes(); // Connect adjacent nodes

    void checkConnection(RadioDriver*);
    int deployConnection(RadioDriver*, RadioDriver*);

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    int numberClient;
    std::ostringstream oss;
    std::list<Transmission*> onAir;

    void changeStatus(RadioDriver*); // change color of sensor in term of status

    void registerTransmission(Transmission*);    // register a transmission in world
    bool isFeasibleTransmission(Transmission*);  // check whether a transmission feasible or not
    void stopTransmission(Transmission*);         // unregister a transmission from world
    bool senseBusyTransmission(Transmission*);   // perform CCA

    double calculateDistance(RadioDriver*, RadioDriver*); // calculate distance between 2 sensors
    double calculateDistance(int, int, int, int);        // calculate distance according to 2D coordinate
};

} /* namespace wsn_energy */

#endif /* ENVIROMENT_H_ */
