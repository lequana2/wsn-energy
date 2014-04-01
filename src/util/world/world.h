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

#include <omnetpp.h>
#include "mySignal.h"
#include "radio.h"

namespace wsn_energy {

class World : public cSimpleModule
{
  private:
    int numberClient;

    void arrangeNodes(); // Arrange nodes in positions
    void connectNodes(); // Connect adjacent nodes

//    void checkConnection(RadioDriver*); // WSN to be removed: ??? do
//    int deployConnection(RadioDriver*, RadioDriver*); // WSN to be removed:

  protected:
    void initialize();
    void handleMessage(cMessage *msg);
    void finish();

  public:
    std::ostringstream oss;
    cArray host;
    cArray signal;

    void changeStatus(RadioDriver*); // WSN to be removed: change color of sensor in term of status

    void registerTransmission(mySignal*);    // WSN to be removed: register a transmission in world
    bool isFeasibleTransmission(mySignal*);  // WSN to be removed: check whether a transmission feasible or not
    void stopTransmission(mySignal*);         // WSN to be removed: unregister a transmission from world
    bool senseBusyTransmission(mySignal*);   // WSN to be removed: perform CCA

    double calculateDistance(RadioDriver*, RadioDriver*); // calculate distance between 2 sensors
    double calculateDistance(int, int, int, int);        // calculate distance according to 2D coordinate
};

} /* namespace wsn_energy */

#endif /* ENVIROMENT_H_ */
