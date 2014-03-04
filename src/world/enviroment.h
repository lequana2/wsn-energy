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

#include "transmission.h"

namespace wsn_energy {

class Enviroment : public cSimpleModule
{
  public:
    void registerTranmission(Transmission*);
    bool isFeasibleTranmission(Transmission*);
    void stopTranmission(Transmission*);

    double calculateDistance(Core*, Core*);
    double calculateDistance(int, int, int, int);

  private:
    std::list<Transmission*> onTheAir;
    void arrangeNodes(); // Arrange nodes in positions
    void connectNodes(); // Connect adjacent nodes

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void checkConnection(Core*);
    int deployConnection(Core*, Core*);
};

} /* namespace wsn_energy */

#endif /* ENVIROMENT_H_ */
