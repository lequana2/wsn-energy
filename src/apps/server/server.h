/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Base-station app, construct network topology, receive data from mote
 */

#ifndef __WSN_ENERGY_SINK_H
#define __WSN_ENERGY_SINK_H

#include <omnetpp.h>

namespace wsn_energy {

class Server : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

}
;
// namespace

#endif
