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
#define WAIT_FOR_ACK_DURATION 0.000864 // WSN 54 symbols ??? - nullRDC
#endif

#ifndef CHANNEL_CHECK
#define CHANNEL_CHECK
#define FAST_SLEEP               1        // using fast-sleep
// check rate
#define CHANNEL_CHECK_RATE       8        // Hertz
#define CHANNEL_CHECK_INTERVAL   0.125    // second
// CCA configuration
#define CCA_COUNT_MAX            2        // maximum number of CCA per check
#define CCA_TRANS_MAX            6        // maximum number of CCA before transmitting
#define CCA_CHECK_TIME           0.000122 // time to perform a CCA (20 symbols)
#define CCA_SLEEP_TIME           0.005    // interval between each CCA
// reaction
#define LISTEN_AFTER_DETECT      0.0125   // second, interval after detecting a strobe
#define INTER_FRAME_INTERVAL     0.004    // second, interval between each frame in a transmission phases
#define MAX_PHASE_STROBE         0.145488 // second, time for a transmission phases (1 check interval + 2 check phases)
// packet size
#define SHORTEST_PACKET_SIZE     43       // WSN need to recalculate, whatever :))
#endif

#include <myModule.h>
#include <frame_m.h>

namespace wsn_energy {

class Neighbor
{
  public:
    int senderID;
    int sequence;
    double phaseOptimization; // next time checking (because same check rate)
};

class RDCdriver : public myModule
{
  private:
    // contikimac controls
    bool isOnAnTranssmissionPhase;
    bool isOnAnCheckingPhase;
    int ccaCounter;
    double cumulativeSessionTime;

  protected:
    // For neighbor discovery protocol (NDP) - link-local aquire
    // For sequence checker
    // For phase optimization
    std::list<Neighbor*> neighbors;

    Frame* buffer;

    void initialize();

    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

    /* demand */
    void send();
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
