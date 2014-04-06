/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Base-station app, construct network topology, receive data from mote
 */

#ifndef __WSN_ENERGY_SINK_H
#define __WSN_ENERGY_SINK_H

#include <myModule.h>

namespace wsn_energy {

class Server : public myModule
{
  protected:
    virtual void initialize();

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);
};

}
;
// namespace

#endif
