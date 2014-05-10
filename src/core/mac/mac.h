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
#include <frame_m.h>

namespace wsn_energy {

class MACdriver : public myModule
{
  private:
    bool isBufferClear;

  protected:
    Frame* buffer;
    int sequenceNumber;

    void initialize();
    void finish();

    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

    /* backoff transmitting, CCA is involved */
    virtual void deferPacket() = 0;

    /* send buffer packet */
    virtual void sendFrame();

    /* accept input from lowerlayer */
    virtual void receiveFrame(Frame*);

  public:
    // 802.15.4 self address
    int linkLocalAddress;

    // 802.15.4 default router address
    int defaultRoute;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
