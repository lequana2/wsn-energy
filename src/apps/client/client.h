/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Distributed client, collect data and forward to server
 */

#ifndef __WSN_ENERGY_SOURCE_H
#define __WSN_ENERGY_SOURCE_H

#include <omnetpp.h>

namespace wsn_energy {

class Client : public cSimpleModule
{
  private:
    virtual void newData();

  public:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

}
;
// namespace

#endif
