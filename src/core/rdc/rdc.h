/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: radio duty cycling
 */

#ifndef RDCDRIVER_H_
#define RDCDRIVER_H_

#include <myModule.h>
#include "packet_m.h"

namespace wsn_energy {

class RDCdriver : public myModule
{
  protected:
    FrameRDC *buffer;

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);

    /* transmit demand */
    virtual void sendPacket(FrameRDC*) = 0;

    /* call-back */
    virtual void sendSuccess(FrameRDC*) = 0;
    virtual void sendFailure() = 0;

    /* listen demand */
    virtual void on();
    virtual void off();

    /* consider new-coming */
    virtual void receiveSuccess(FrameMAC*) = 0;
    virtual void receiveFailure() = 0;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
