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

#ifndef RPL_H_
#define RPL_H_

#include <list>
#include "packet_m.h"

#define RANK_INFINITY 0xffff

namespace wsn_energy {

/* forward declaration */
class IPv6;
class ObjectiveFunction;

class NodeQuality
{
  public:
    double hopCount;
    double energy;
};

class LinkQuality
{
  public:
    double etx;
};

class RPL_neighbor
{
  public:
    int neighborID;
    unsigned long neighborRank;

    NodeQuality nodeQuality;
    LinkQuality linkQuality;
};

class RPL_dag
{
  public:
    bool joined;
    int dodagID;
    int version;
    // Self rank
    unsigned long rank;

    // upward route
    RPL_neighbor *preferredParent;

    // neighbor information
    std::list<RPL_neighbor*> parentList;
    std::list<RPL_neighbor*> siblingList;

    // Objective Function
    ObjectiveFunction *of;
};

class RPL
{
  private:
    IPv6 *net;

  public:
    RPL_dag rplDag;

    RPL(IPv6 *net);

    void rpl_set_root();
    void rpl_init();

    void sendDIO();
    void sendDIS(int);

    void processDIO(DIO*);
    void processDIS(DIS*);
};

} /* namespace wsn_energy */

#endif /* RPL_H_ */
