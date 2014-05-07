/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: radio duty cycling
 */

#ifndef RDCDRIVER_H_
#define RDCDRIVER_H_

#ifndef WAIT_FOR_ACK_DURATION
#define WAIT_FOR_ACK_DURATION 0.000864 // 54 symbols
#endif

#ifndef CHANNEL_CHECK
#define CHANNEL_CHECK
#define CHANNEL_CHECK_RATE       8     // Hz
#define CHANNEL_CHECK_INTERVAL   1.0/8 // second
#endif

#include <myModule.h>
#include "packet_m.h"

namespace wsn_energy {

class Neighbor
{
  public:
    int senderID;
    int sequence;
    int phaseOptimization;
};

class RDCdriver : public myModule
{
  private:
    int counter;

  protected:
    Command* channelCheck;
    Command* waitForACK;
    bool isWaitingACK;

    std::list<Neighbor*> neighbors;

    Frame* buffer;

    void initialize();

    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

    /* listen demand */
    void on();
    void off();

    /* transmit demand */
    virtual void sendPacket(Frame*) = 0;

    /* call-back */
    virtual void sendSuccess(Frame*) = 0;
    virtual void sendFailure() = 0;

    /* consider new-coming */
    virtual void receiveSuccess(Frame*) = 0;
    virtual void receiveFailure() = 0;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
