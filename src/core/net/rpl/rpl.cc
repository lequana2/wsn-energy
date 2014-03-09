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

#include <algorithm>

#include "core.h"

namespace wsn_energy {

RPL::RPL()
{
}

RPL::~RPL()
{
  this->neighborList.clear();
}

RPL::RPL(Core *core)
{
  this->rpl_init();
  this->core = core;
}

void RPL::rpl_init()
{
  this->rplDag.dodagid = 0;
  this->rplDag.joined = false;
  this->rplDag.rank = RANK_INFINITY;
}

void RPL::rpl_set_root()
{
  this->rplDag.dodagid++;
  this->rplDag.joined = true;
  this->rplDag.rank = 0;

  // WSN Should send continously
  cMessage *constructMessage = new cMessage();
  constructMessage->setKind(RPL_CONSTRUCT);
  core->scheduleAt(simTime(), constructMessage);
}

void RPL::sendDIO()
{
  ev << "broadcast DIO" << endl;

  DIO *icmp = new DIO();
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);
  ((IpPacket*) icmp)->setType(IP_ICMP);

  icmp->setDodagID(this->rplDag.dodagid);

  core->broadcast(icmp);
}

void RPL::sendDIS(int convergence)
{
  ev << "broadcast DIS" << endl;

  DIS *icmp = new DIS();
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIS_CODE);
  ((IpPacket*) icmp)->setType(IP_ICMP);

  icmp->setConvergence(convergence);

  core->broadcast(icmp);
}

void RPL::receiveDIO(DIO* msg)
{
  ev << "Received DIO " << endl;

  //omit obsolete DIO
  if (this->rplDag.dodagid >= msg->getDodagID())
  {
    // sendDIO();
  }
  //forward update DIO, create connection
  else
  {
    // WSN Consider neighbor
    int neighbor = simulation.getModule(((Raw*) msg)->getRadioSendId())->getId();
    if (std::find(neighborList.begin(), neighborList.end(), neighbor) == neighborList.end())
    {
      ev << "new neighbor" << endl;
      neighborList.push_back(neighbor);

      // considering rank
      // assure children, siblings or parents

      // draw new connection
      char channelParent[20];
      sprintf(channelParent, "out %d to %d", ((Raw*) msg)->getRadioRecvId(), ((Raw*) msg)->getRadioSendId());
      EV << channelParent << endl;
      core->getParentModule()->gate(channelParent)->setDisplayString("ls=red,1");
    }

    // WSN Choose new preferred parent
    this->rplDag.dodagid = ((DIO*) msg)->getDodagID();
    this->sendDIO();
  }
}

void RPL::receiveDIS(DIS* msg)
{
  EV << "Received DIS " << endl;

  // currently in DAG, then broadcast DIS
  if (this->rplDag.joined)
  {
    this->sendDIO();
  }
  // already
  else
  {
    //WSN broadcast DIS toward root
//    int convergence = ((DIS*) msg)->getConvergence();
//    if (convergence > 0)
//      this->sendDIS(convergence - 1);
  }
}

} /* namespace wsn_energy */
