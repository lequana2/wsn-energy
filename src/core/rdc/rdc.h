/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: radio duty cycling
 */

#ifndef RDCDRIVER_H_
#define RDCDRIVER_H_

//#ifndef WAIT_FOR_ACK_DURATION
//#define WAIT_FOR_ACK_DURATION 0.000864 // wait time of nullRDC
//#endif

#ifndef RDC
#define RDC
// value of ACK length header
#define ACK_LENGTH          5
// CCA type
#define RDC_CHECK_CCA       0
#define RDC_TRANS_CCA       1
#define MAC_CCA             2
// working phase
#define CHECKING_PHASE      0
#define TRANSMITTING_PHASE  1
#define FREE_PHASE          2
// check rate
#define CHANNEL_CHECK_RATE       8        // Hertz
#define CHANNEL_CHECK_INTERVAL   0.125    // second
// CCA configuration
#define CCA_TRANS_MAX            6        // maximum number of CCA before transmitting
#define CCA_COUNT_MAX            2        // maximum number of CCA per check
#define CCA_CHECK_TIME           0.000122 // time to perform a CCA (20 symbols)
#define CCA_SLEEP_TIME           0.0005   // interval between each CCA
// reaction
#define LISTEN_AFTER_DETECT      0.0125   // second, interval after detecting a strobe
#define INTER_FRAME_INTERVAL     0.004    // second, interval between each frame in a transmission phases
#define MAX_PHASE_STROBE         0.145488 // second, time for a transmission phases (1 check interval + 2 check phases)
// packet size
#define SHORTEST_PACKET_SIZE     23       // octets
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
    // just send ACK <-- distinguish with data sending
    bool isJustSendACK;

    // MAC is waiting for nearly done CCA
    bool isHavingPendingTransmission;

    // MAC CCA or RDC CCA
    int ccaType;

    // CCA counter in 1 checking phase
    int ccaCounter;

    // CCA counter in 1 transmission turn
    int ccaInOneTurn;

  protected:
    // For neighbor discovery protocol (NDP) - link-local aquire
    // For sequence checker
    // For phase optimization
    std::list<Neighbor*> neighbors;

    Command *ccaResult;
    Command *ccaTimeOut;
    Command *phaseTimeOut;

    Frame *bufferRDC;

    void initialize();
    void finish();

    bool cca();

    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

    /* MAC call-back */
    void enterMACtransmissonPhase();
    void quitMACtransmissonPhase();

    /* RDC transmission turn */
    void enterRDCtransmissionPhase();
    void quitRDCtransmissionPhase(int result);

    /* demand radio layer*/
    void sendFrame();
    void on();
    void off();

    /* begin a transmission phase */
    virtual void sendPacket(Frame*) = 0;

    /* after a transmission phase */
    virtual void sendSuccess(Frame*) = 0;
    virtual void sendFailure() = 0;

    /* after a listening phase */
    virtual void receiveSuccess(Frame*) = 0;
    virtual void receiveFailure() = 0;

  public:
    // working phase
    int phase;
};

} /* namespace wsn_energy */

#endif /* RDCDRIVER_H_ */
