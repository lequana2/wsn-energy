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

#include "Server.h"
#include "ICMP_m.h"
#include "Core.h"

namespace wsn_energy {

Define_Module(Server);

void Server::initialize()
{
  Core::initialize();
//  lastArrival = simTime();
//  iaTimeHistogram.setName("interarrival times");
//  arrivalsVector.setName("arrivals");
//  arrivalsVector.setInterpolationMode(cOutVector::NONE);
}

void Server::handleMessage(cMessage *msg)
{
//  simtime_t d = simTime() - lastArrival;
  Core::handleMessage(msg);

  switch (msg->getKind())
  {
    case START_MESSAGE:
      //WSN disable proactive
//      sendDIO();
      break;

    case ICMP_MESSAGE:
      if (((ICMP*) msg)->getIcmp_code() == ICMP_DIO_CODE)
      {
        EV << "Received DIO " << ((DIO*) msg)->getDodagID() << endl;
      }
      else if (((ICMP*) msg)->getIcmp_code() == ICMP_DIS_CODE)
      {
//        EV << "Received DIS " << ((DIS*) msg)->getOptions() << endl;
        //WSN create global repair
        sendDIO();
      }
      break;

    default:
      break;
  }

  delete msg;

//  iaTimeHistogram.collect(d);
//  arrivalsVector.record(1);
//  lastArrival = simTime();
}

void Server::finish()
{
//  recordStatistic(&iaTimeHistogram);
}

}
;
// namespace
