//
// Generated file, do not edit! Created by opp_msgc 4.4 from package/strobe/strobe.msg.
//

#ifndef _STROBE_M_H_
#define _STROBE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif


namespace wsn_energy {

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum KIND{
 * 	DATA    = 2; 
 * 	COMMAND = 4; 
 * 	RESULT  = 1; 
 * };
 * </pre>
 */
enum KIND {
    DATA = 2,
    COMMAND = 4,
    RESULT = 1
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum MANUAL_EVENT{
 * 	NODE_STARTUP  = 0; 
 * 	OUT_OF_ENERGY = 1; 
 * 	NODE_DESTRUCT = 2; 
 * };
 * </pre>
 */
enum MANUAL_EVENT {
    NODE_STARTUP = 0,
    OUT_OF_ENERGY = 1,
    NODE_DESTRUCT = 2
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum COMMAND_APP{
 * 	APP_ENVIRON_FLAG = 0; 
 * 	APP_SENSING_FLAG = 1; 
 * 	
 * 	RPL_SET_UP_DELAY = 2; 
 * };
 * </pre>
 */
enum COMMAND_APP {
    APP_ENVIRON_FLAG = 0,
    APP_SENSING_FLAG = 1,
    RPL_SET_UP_DELAY = 2
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum COMMAND_NET{
 *     RPL_CONSTRUCT 	 	= 0; 
 *     
 *     NET_TIMER_DIO       = 1; 
 *     NET_TIMER_DIS       = 2; 
 * 	
 * 	NET_CHECK_BUFFER    = 3; 
 * };
 * </pre>
 */
enum COMMAND_NET {
    RPL_CONSTRUCT = 0,
    NET_TIMER_DIO = 1,
    NET_TIMER_DIS = 2,
    NET_CHECK_BUFFER = 3
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum COMMAND_MAC{
 * 	MAC_CCA_REQUEST = 0; 
 * 	
 * 	MAC_ASK_SEND_FRAME 	 = 1; 
 * 	
 * 	MAC_BEGIN_SEND_TURN  = 2; 
 * 	
 * 	MAC_END_SEND_FRAME   = 3; 
 * 	
 * 	MAC_EXPIRE_IFS		 = 4; 
 * };
 * </pre>
 */
enum COMMAND_MAC {
    MAC_CCA_REQUEST = 0,
    MAC_ASK_SEND_FRAME = 1,
    MAC_BEGIN_SEND_TURN = 2,
    MAC_END_SEND_FRAME = 3,
    MAC_EXPIRE_IFS = 4
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum FRAME_TYPE{
 *     FRAME_BEACON  	= 0; 
 *     FRAME_COMMAND 	= 1; 
 * 	FRAME_DATA 		= 2; 
 * 	FRAME_ACK  		= 3; 
 * }
 * </pre>
 */
enum FRAME_TYPE {
    FRAME_BEACON = 0,
    FRAME_COMMAND = 1,
    FRAME_DATA = 2,
    FRAME_ACK = 3
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum RESULT_FROM_MAC{
 *     MAC_SEND_DEAD_NEIGHBOR = 0; 
 * 	
 * 	MAC_FINISH_PHASE       = 1; 
 * 	MAC_SEND_END_TRANSMIT  = 2; 
 * };
 * </pre>
 */
enum RESULT_FROM_MAC {
    MAC_SEND_DEAD_NEIGHBOR = 0,
    MAC_FINISH_PHASE = 1,
    MAC_SEND_END_TRANSMIT = 2
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum COMMAND_RDC{
 * 	RDC_TRANSMIT = 0; 
 * 	RDC_LISTEN 	 = 1; 
 * 	RDC_IDLE     = 2; 
 * 	
 * 	RDC_CCA_REQUEST = 3; 
 * 	
 * 	RDC_CHANNEL_CHECK = 4; 
 * 	RDC_SEND_FRAME    = 5; 
 * 	
 * 	RDC_CCA_TIME_OUT   = 6; 
 * 	RDC_PHASE_TIME_OUT = 7; 
 * };
 * </pre>
 */
enum COMMAND_RDC {
    RDC_TRANSMIT = 0,
    RDC_LISTEN = 1,
    RDC_IDLE = 2,
    RDC_CCA_REQUEST = 3,
    RDC_CHANNEL_CHECK = 4,
    RDC_SEND_FRAME = 5,
    RDC_CCA_TIME_OUT = 6,
    RDC_PHASE_TIME_OUT = 7
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum RESULT_RDC{
 * 	RDC_READY_TRANS_PHASE = 0; 
 *     RDC_STOP_TRANS_PHASE  = 1; 
 *     
 *     RDC_BEGIN_TRANS_TURN  = 2; 
 *     
 *     
 * 	RDC_SEND_OK     	  = 3; 
 * 	RDC_SEND_NO_ACK 	  = 4; 
 * 	RDC_SEND_FATAL        = 5; 
 * 	RDC_SEND_COL	      = 6; 
 * };
 * </pre>
 */
enum RESULT_RDC {
    RDC_READY_TRANS_PHASE = 0,
    RDC_STOP_TRANS_PHASE = 1,
    RDC_BEGIN_TRANS_TURN = 2,
    RDC_SEND_OK = 3,
    RDC_SEND_NO_ACK = 4,
    RDC_SEND_FATAL = 5,
    RDC_SEND_COL = 6
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum COMMAND_PHY{
 * 	PHY_BEGIN_CCA       = 10; 
 * 	PHY_END_CCA         = 11; 
 * 	
 *  	PHY_SWITCH_TRANSMIT	= 12; 
 *  	PHY_SWITCH_LISTEN	= 13; 
 *  	PHY_SWITCH_IDLE     = 14; 
 *  	
 *  	PHY_BEGIN_TRANSMIT  = 15; 
 * 	PHY_END_TRANSMIT	= 16; 
 * 
 *  	PHY_LISTENING    	= 17; 
 *  	
 *  	PHY_IDLING  	 	= 18; 
 * };
 * </pre>
 */
enum COMMAND_PHY {
    PHY_BEGIN_CCA = 10,
    PHY_END_CCA = 11,
    PHY_SWITCH_TRANSMIT = 12,
    PHY_SWITCH_LISTEN = 13,
    PHY_SWITCH_IDLE = 14,
    PHY_BEGIN_TRANSMIT = 15,
    PHY_END_TRANSMIT = 16,
    PHY_LISTENING = 17,
    PHY_IDLING = 18
};

/**
 * Enum generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * enum RESULT_PHY{
 *     
 * 	CHANNEL_CLEAR   	= 10; 
 * 	CHANNEL_BUSY    	= 11; 
 * 	
 * 	
 * 	PHY_TX_OK		 	= 12; 
 * 	PHY_TX_ERR 		 	= 13; 
 * };
 * </pre>
 */
enum RESULT_PHY {
    CHANNEL_CLEAR = 10,
    CHANNEL_BUSY = 11,
    PHY_TX_OK = 12,
    PHY_TX_ERR = 13
};

/**
 * Class generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * packet Command{
 * 	int note;
 * }
 * </pre>
 */
class Command : public ::cPacket
{
  protected:
    int note_var;

  private:
    void copy(const Command& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Command&);

  public:
    Command(const char *name=NULL, int kind=0);
    Command(const Command& other);
    virtual ~Command();
    Command& operator=(const Command& other);
    virtual Command *dup() const {return new Command(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNote() const;
    virtual void setNote(int note);
};

inline void doPacking(cCommBuffer *b, Command& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Command& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>package/strobe/strobe.msg</tt> by opp_msgc.
 * <pre>
 * packet Result{
 * 	int note;
 * }
 * </pre>
 */
class Result : public ::cPacket
{
  protected:
    int note_var;

  private:
    void copy(const Result& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Result&);

  public:
    Result(const char *name=NULL, int kind=0);
    Result(const Result& other);
    virtual ~Result();
    Result& operator=(const Result& other);
    virtual Result *dup() const {return new Result(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNote() const;
    virtual void setNote(int note);
};

inline void doPacking(cCommBuffer *b, Result& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Result& obj) {obj.parsimUnpack(b);}

}; // end namespace wsn_energy

#endif // _STROBE_M_H_
