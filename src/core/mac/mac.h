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

class shortAddress802154
{
    char octet[2];
};

class longAddress802154
{
    char octect[8];
};

class MACdriver : public myModule
{
  protected:
    Frame *frameBuffer;

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);

    /* backoff transmitting, CCA is involved */
    virtual void deferPacket() = 0;

    /* send buffer packet */
    virtual void sendPacket();

    /* accept input from lowerlayer */
    virtual void receivePacket(Frame*);

  public:
    // 802.15.4 self address
    int linkLocalAddress;

    // 802.15.4 default router address
    int defaultRoute;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
