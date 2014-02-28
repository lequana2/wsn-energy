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

#ifndef CORE_H_
#define CORE_H_

#include <omnetpp.h>
#include <vector>

#define INIT_MESSAGE 1
#define START_MESSAGE 2
#define ICMP_MESSAGE 3

#define RANK_INFINITY 0xffff

namespace wsn_energy {

class Core : public cSimpleModule
{
  public:
      int numberClient;
      int trRange;
      int ssRange;
      int redundancy;
      int axisX;
      int axisY;
      int energy;

      std::vector<int> neighbor;

      //WSN info
      int dodagid;
      int rank;

      //WSN default route to server
      std::vector<int> route;

  protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
      void sendDIO();
      void sendDIS(int);

  private:
      void createConnection();
      int checkConnection(Core*, Core*);
      double calculateDistance(int,int,int,int);
};

}; // namespace

#endif /* CORE_H_ */
