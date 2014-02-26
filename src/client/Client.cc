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

#include "Client.h"
#include "ICMP_m.h"

namespace wsn_energy {

Define_Module(Client);

Client::Client()
{
    timerMessage = NULL;
}

Client::~Client()
{
    cancelAndDelete(timerMessage);
}

void Client::initialize()
{
    timerMessage = new cMessage("timer");
    scheduleAt(simTime(), timerMessage);
    flag = true;
}

void Client::handleMessage(cMessage *msg)
{
    ASSERT(msg==timerMessage);

    //WSN sending ICMP 6
    cMessage *icmp = NULL;

    if(flag){
      icmp = new DIO();
      ((ICMP*) icmp)->setIcmp_code(ICMP_DIO_CODE);
    } else {
      icmp = new DIS();
      ((ICMP*)icmp)->setIcmp_code(ICMP_DIS_CODE);
    }
    flag = !flag;

    send(icmp,"port$o");

    scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);
}

}; // namespace

