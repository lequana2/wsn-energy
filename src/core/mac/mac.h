/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: mac driver
 */

#ifndef MACDRIVER_H_
#define MACDRIVER_H_

#include "myModule.h"

namespace wsn_energy {

class MACdriver : public myModule
{
  protected:
    /* WSN ip-routing table !!! */
    FrameMAC *buffer;

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);

    /* backoff transmitting */
    virtual void deferPacket() = 0;

    /* send buffer packet */
    virtual void sendPacket();

    /* accept input from lowerlayer */
    virtual void receivePacket(FrameMAC*);
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
