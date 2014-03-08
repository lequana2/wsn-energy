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

class Core; // forward declaration

class RPL_dag
{
  public:
    int dodagid;
    unsigned long rank;
    bool joined;
    std::list<int> parentList;
};

class RPL
{
  public:
    RPL_dag rplDag;

    RPL(Core *core);

    void rpl_set_root();
    void rpl_init();

    void sendDIO();
    void sendDIS(int);

    void receiveDIO(DIO*);
    void receiveDIS(DIS*);

  private:
    Core *core;
};

} /* namespace wsn_energy */

#endif /* RPL_H_ */
