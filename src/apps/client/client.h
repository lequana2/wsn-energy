/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Distributed client, collect data and forward to server
 */

#ifndef __WSN_ENERGY_SOURCE_H
#define __WSN_ENERGY_SOURCE_H

//#define MAX 900

#include <myModule.h>

namespace wsn_energy {

class Client : public myModule
{
  private:
    int numberOfPacket;
    virtual void newData();

  protected:
    void initialize();
    void handleMessage(cMessage*);

  public:
    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);
};

}
;
// namespace

#endif
