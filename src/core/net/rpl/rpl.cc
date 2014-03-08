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

  // WSN Should send continously
  cMessage *constructMessage = new cMessage();
  constructMessage->setKind(RPL_CONSTRUCT);
  core->scheduleAt(simTime(), constructMessage);
}

void RPL::sendDIO()
{
  ev << "broadcast DIO" << endl;

  DIO *icmp = new DIO();
  ((cMessage*) icmp)->setKind(IP_PACKET);
  ((IpPacket*) icmp)->setType(IP_ICMP);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);

  icmp->setDodagID(this->rplDag.dodagid);

  core->broadcast(icmp);
}

void RPL::sendDIS(int convergence)
{
  ev << "broadcast DIS" << endl;

  DIS *icmp = new DIS();
  ((cMessage*) icmp)->setKind(IP_PACKET);
  ((IpPacket*) icmp)->setType(IP_ICMP);
  ((ICMP*) icmp)->setIcmp_code(ICMP_DIS_CODE);

  icmp->setConvergence(convergence);

//  for (unsigned int i = 0; i < core->neighbor.size(); i++)
//  {
//    DIS *icmp_dup = icmp->dup();
//    icmp_dup->setRecvID(this->core->neighbor.at(i));
//
//    core->broadcast(icmp);
//  }
}

void RPL::receiveDIO(DIO* msg)
{
  ev << "Received DIO " << msg->getDodagID() << endl;
  //omit obsolete DIO
  if (this->rplDag.dodagid >= msg->getDodagID())
  {
    // sendDIO();
  }
  //forward update DIO, create connection
  else
  {
    //Consider new parent
    //WSN Choose new preferred parent

    //Draw new connection
    char setOutConnectionName[20];
    sprintf(setOutConnectionName, "out %d to %d", msg->getRecvID(), msg->getSendID());
    core->getParentModule()->gate(setOutConnectionName)->setDisplayString("ls=red,1");
    // EV << setOutConnectionName << endl;

    this->rplDag.dodagid = ((DIO*) msg)->getDodagID();
//    this->sendDIO();
  }
}

void RPL::receiveDIS(DIS* msg)
{
  EV << "Received DIS " << msg->getConvergence() << endl;
  //WSN check route to root
  if (core->route.size() == 0)
    ;
  else if (((Core*) core->route.back())->getId() != simulation.getModuleByPath("server")->getId())
    ;
  else
  {
    //WSN broadcast DIS toward root
    int convergence = ((DIS*) msg)->getConvergence();
    if (convergence > 0)
      this->sendDIS(convergence - 1);
  }
}

} /* namespace wsn_energy */
