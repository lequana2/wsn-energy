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

#include <stdio.h>

#include "Client.h"
#include "ICMP_m.h"
#include "Core.h"

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
  Core::initialize();

  flag = true;

//  timerMessage = new cMessage("timer");
//  scheduleAt(simTime(), timerMessage);
}

void Client::handleMessage(cMessage *msg)
{
  Core::handleMessage(msg);

  switch (msg->getKind())
  {
    case INIT_MESSAGE:
//      if (this->getId() == ((cSimpleModule*) simulation.getModuleByPath("client[0]"))->getId())
//        sendDIS(5);
      break;

    case ICMP_MESSAGE:
      if (((ICMP*) msg)->getIcmp_code() == ICMP_DIO_CODE)
      {
//        EV << "Received DIO " << ((DIO*) msg)->getDodagID() << endl;
        //omit obsolete DIO
        if (this->dodagid >= ((DIO*) msg)->getDodagID())
        {
//          sendDIO();
        }
        //forward update DIO, create connection
        else
        {
          //Consider new parent
          //WSN Choose new preferred parent
          //Draw new connection
          char setOutConnectionName[20];
          sprintf(setOutConnectionName, "out %d to %d", msg->getArrivalModule()->getId(),
              msg->getSenderModule()->getId());
          (this->gate(setOutConnectionName))->setDisplayString("ls=red,1");
//          EV << setOutConnectionName << endl;

          this->dodagid = ((DIO*) msg)->getDodagID();
          sendDIO();
        }
      }
      else if (((ICMP*) msg)->getIcmp_code() == ICMP_DIS_CODE)
      {
//        EV << "Received DIS " << ((DIS*) msg)->getOptions() << endl;
        //WSN check route to root
        if (route.size() == 0)
          ;
        else if (((Core*) route.back())->getId() != simulation.getModuleByPath("server")->getId())
          ;
        else
        {
          //WSN broadcast DIS toward root
          int convergence = ((DIS*) msg)->getConvergence();
          if (convergence > 0)
            sendDIS(convergence - 1);
        }
      }
      break;

    default:
      break;
  }

  delete msg;

//    send(icmp,"port$o");
//    scheduleAt(simTime()+par("sendInterval").doubleValue(), timerMessage);
}

}
;
// namespace

