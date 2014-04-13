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

class IpTable
{
    int ipAddress;
    int macAddress;
};

class MACdriver : public myModule
{
  protected:
    std::list<IpTable> ipTable; // mac-ip table
    bool isHavingPendingPacket;
    FrameMAC *frameBuffer;

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);

    /* backoff transmitting */
    virtual void deferPacket() = 0;

    /* send buffer packet */
    virtual void sendPacket();

    /* accept input from lowerlayer */
    virtual void receivePacket(FrameMAC*);

  public:
    std::list<FrameMAC*> buffer; // Buffer message to send, public scope for debugging
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
