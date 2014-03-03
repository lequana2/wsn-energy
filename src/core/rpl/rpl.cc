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

#include <rpl.h>

#include "core.h"

namespace wsn_energy {

RPL::RPL(Core *core)
{
  this->rpl_init();
  this->core = core;
}

void RPL::rpl_init()
{
  this->rplDag.dodagid = 0;
  this->rplDag.joined = 0;
  this->rplDag.rank = RANK_INFINITY;
}

void RPL::rpl_set_root()
{
  this->rplDag.dodagid++;
  this->rplDag.rank = 0;
}

void RPL::sendDIO()
{
  ev << "broadcast DIO" << endl;

  DIO *icmp = new DIO();
  ((cMessage*) icmp)->setKind(ICMP_MESSAGE);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);

  icmp->setSendID(core->getId());
  icmp->setDodagID(this->rplDag.dodagid);

  for (unsigned int i = 0; i < core->neighbor.size(); i++)
  {
    DIO *icmp_dup = icmp->dup();
    icmp_dup->setRecvID(this->core->neighbor.at(i));

    core->sendMessage((Core*) simulation.getModule(core->neighbor.at(i)), icmp_dup);
  }
}

void RPL::sendDIS(int convergence)
{
  ev << "broadcast DIS" << endl;

  DIS *icmp = new DIS();
  ((cMessage*) icmp)->setKind(ICMP_MESSAGE);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIS_CODE);

  icmp->setConvergence(convergence);

  for (unsigned int i = 0; i < core->neighbor.size(); i++)
  {
    DIS *icmp_dup = icmp->dup();
    icmp_dup->setRecvID(this->core->neighbor.at(i));

    core->sendMessage((Core*) simulation.getModule(core->neighbor.at(i)), icmp_dup);
  }
}
} /* namespace wsn_energy */
