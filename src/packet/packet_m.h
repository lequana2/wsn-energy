//
// Generated file, do not edit! Created by opp_msgc 4.4 from packet/packet.msg.
//

#ifndef _PACKET_M_H_
#define _PACKET_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "packet_len.h"
// }}


namespace wsn_energy {

/**
 * Enum generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * enum COMMAND_AND_RESULT
 * {
 * 	
 * 	NODE_STARTUP  = 0; 
 * 	NODE_DESTRUCT = 1; 
 * 	OUT_OF_ENERGY = 2; 
 * 	
 * 	
 * 	RPL_CONSTRUCT = 3; 
 * 	RPL_SOLICIT   = 4; 
 * 
 * 	
 *  	LAYER_RADIO     			= 10; 
 *  	
 *  	LAYER_RADIO_SWITCH_TRANSMIT	= 11; 
 *  	LAYER_RADIO_SWITCH_LISTEN	= 12; 
 *  	LAYER_RADIO_SWITCH_SLEEP    = 13; 
 *  	
 *  	LAYER_RADIO_BEGIN_TRANSMIT  = 14; 
 *  	LAYER_RADIO_BEGIN_LISTEN    = 15; 
 *  	
 *  	LAYER_RADIO_END_TRANSMIT	= 16; 
 *  	LAYER_RADIO_END_LISTENING  	= 17; 
 *  	
 *  	LAYER_RADIO_CCA_NOT_VALID   = 18; 
 * 	LAYER_RADIO_NOT_FREE	   	= 19; 
 * 	LAYER_RADIO_PACKET_OVERSIZE = 20; 
 * 	LAYER_RADIO_SEND_OK			= 21; 
 * 	
 * 	LAYER_RADIO_RECV_OK			= 22; 
 * 	LAYER_RADIO_RECV_CORRUPT	= 23; 
 * 	
 * 	
 * 	LAYER_RDC                	= 30; 
 * 	
 * 	LAYER_RDC_SEND				= 31; 
 * 	LAYER_RDC_SEND_OK			= 32; 
 * 	LAYER_RDC_SEND_NOT_OK		= 33; 
 * 	
 * 	LAYER_RDC_WAIT_ACK			= 34; 
 * 	
 * 	LAYER_RDC_LISTEN_ON			= 35; 
 * 	LAYER_RDC_LISTEN_OFF		= 36; 
 * 	
 * 	LAYER_RDC_RECV_OK			= 37; 
 * 	LAYER_RDC_RECV_ACK			= 38; 
 * 	
 * 	
 * 	LAYER_MAC 		    = 50; 
 * 	
 * 	LAYER_MAC_SEND_OK	= 51; 
 * 	LAYER_MAC_NO_ACK  	= 52; 
 * 	
 * 	LAYER_MAC_DEFER		= 53; 
 * 	LAYER_MAC_ERR		= 54; 
 * 
 * 	LAYER_MAC_RECV_OK	= 55; 
 * 
 * 	
 * 	LAYER_NET       	   = 70;	
 * 	
 * 	LAYER_NET_CHECK_BUFFER = 71; 
 * 	
 * 	LAYER_NET_SEND_OK	   = 72; 
 * 	LAYER_NET_SEND_NOT_OK  = 73; 
 * 	
 * 	NET_ICMP_DIO    	  = 74;	
 * 	NET_ICMP_DIS    	  = 75;	
 * 	NET_ICMP_ACK    	  = 76;	
 * 	
 * 	NET_DATA        	  = 77; 
 * 	
 * 	NET_ICMP_REQUEST_ACK  = 78; 
 * 	
 * 	
 * 	LAYER_APP		 = 90; 			
 * 	
 * 	APP_WORKING_FLAG = 91; 
 * 	APP_SENSING_FLAG = 92; 
 * 	APP_ENVIRON_FLAG = 93; 
 * }
 * </pre>
 */
enum COMMAND_AND_RESULT {
    NODE_STARTUP = 0,
    NODE_DESTRUCT = 1,
    OUT_OF_ENERGY = 2,
    RPL_CONSTRUCT = 3,
    RPL_SOLICIT = 4,
    LAYER_RADIO = 10,
    LAYER_RADIO_SWITCH_TRANSMIT = 11,
    LAYER_RADIO_SWITCH_LISTEN = 12,
    LAYER_RADIO_SWITCH_SLEEP = 13,
    LAYER_RADIO_BEGIN_TRANSMIT = 14,
    LAYER_RADIO_BEGIN_LISTEN = 15,
    LAYER_RADIO_END_TRANSMIT = 16,
    LAYER_RADIO_END_LISTENING = 17,
    LAYER_RADIO_CCA_NOT_VALID = 18,
    LAYER_RADIO_NOT_FREE = 19,
    LAYER_RADIO_PACKET_OVERSIZE = 20,
    LAYER_RADIO_SEND_OK = 21,
    LAYER_RADIO_RECV_OK = 22,
    LAYER_RADIO_RECV_CORRUPT = 23,
    LAYER_RDC = 30,
    LAYER_RDC_SEND = 31,
    LAYER_RDC_SEND_OK = 32,
    LAYER_RDC_SEND_NOT_OK = 33,
    LAYER_RDC_WAIT_ACK = 34,
    LAYER_RDC_LISTEN_ON = 35,
    LAYER_RDC_LISTEN_OFF = 36,
    LAYER_RDC_RECV_OK = 37,
    LAYER_RDC_RECV_ACK = 38,
    LAYER_MAC = 50,
    LAYER_MAC_SEND_OK = 51,
    LAYER_MAC_NO_ACK = 52,
    LAYER_MAC_DEFER = 53,
    LAYER_MAC_ERR = 54,
    LAYER_MAC_RECV_OK = 55,
    LAYER_NET = 70,
    LAYER_NET_CHECK_BUFFER = 71,
    LAYER_NET_SEND_OK = 72,
    LAYER_NET_SEND_NOT_OK = 73,
    NET_ICMP_DIO = 74,
    NET_ICMP_DIS = 75,
    NET_ICMP_ACK = 76,
    NET_DATA = 77,
    NET_ICMP_REQUEST_ACK = 78,
    LAYER_APP = 90,
    APP_WORKING_FLAG = 91,
    APP_SENSING_FLAG = 92,
    APP_ENVIRON_FLAG = 93
};

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet Raw{
 *     int note; 
 * 
 *     int radioSendId;
 *     int radioRecvId;
 * }
 * </pre>
 */
class Raw : public ::cPacket
{
  protected:
    int note_var;
    int radioSendId_var;
    int radioRecvId_var;

  private:
    void copy(const Raw& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Raw&);

  public:
    Raw(const char *name=NULL, int kind=0);
    Raw(const Raw& other);
    virtual ~Raw();
    Raw& operator=(const Raw& other);
    virtual Raw *dup() const {return new Raw(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNote() const;
    virtual void setNote(int note);
    virtual int getRadioSendId() const;
    virtual void setRadioSendId(int radioSendId);
    virtual int getRadioRecvId() const;
    virtual void setRadioRecvId(int radioRecvId);
};

inline void doPacking(cCommBuffer *b, Raw& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Raw& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet FrameRDC{
 * 	int note;  
 * }
 * </pre>
 */
class FrameRDC : public ::cPacket
{
  protected:
    int note_var;

  private:
    void copy(const FrameRDC& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FrameRDC&);

  public:
    FrameRDC(const char *name=NULL, int kind=0);
    FrameRDC(const FrameRDC& other);
    virtual ~FrameRDC();
    FrameRDC& operator=(const FrameRDC& other);
    virtual FrameRDC *dup() const {return new FrameRDC(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNote() const;
    virtual void setNote(int note);
};

inline void doPacking(cCommBuffer *b, FrameRDC& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, FrameRDC& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet FrameMAC{
 *     int note;  
 * 
 * 	int numberTransmission = 0; 
 * 
 * 	int senderMacAddress; 
 * 	int recverMacAddress; 
 * 
 * 	int sequenceNumber;   
 * }
 * </pre>
 */
class FrameMAC : public ::cPacket
{
  protected:
    int note_var;
    int numberTransmission_var;
    int senderMacAddress_var;
    int recverMacAddress_var;
    int sequenceNumber_var;

  private:
    void copy(const FrameMAC& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FrameMAC&);

  public:
    FrameMAC(const char *name=NULL, int kind=0);
    FrameMAC(const FrameMAC& other);
    virtual ~FrameMAC();
    FrameMAC& operator=(const FrameMAC& other);
    virtual FrameMAC *dup() const {return new FrameMAC(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNote() const;
    virtual void setNote(int note);
    virtual int getNumberTransmission() const;
    virtual void setNumberTransmission(int numberTransmission);
    virtual int getSenderMacAddress() const;
    virtual void setSenderMacAddress(int senderMacAddress);
    virtual int getRecverMacAddress() const;
    virtual void setRecverMacAddress(int recverMacAddress);
    virtual int getSequenceNumber() const;
    virtual void setSequenceNumber(int sequenceNumber);
};

inline void doPacking(cCommBuffer *b, FrameMAC& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, FrameMAC& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet IpPacket{
 *     int note; 	
 *     
 * 	int type;	
 * 
 *     int senderIpAddress; 
 *     int recverIpAddress; 
 * 
 *     bool isRequestAck; 
 * }
 * </pre>
 */
class IpPacket : public ::cPacket
{
  protected:
    int note_var;
    int type_var;
    int senderIpAddress_var;
    int recverIpAddress_var;
    bool isRequestAck_var;

  private:
    void copy(const IpPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const IpPacket&);

  public:
    IpPacket(const char *name=NULL, int kind=0);
    IpPacket(const IpPacket& other);
    virtual ~IpPacket();
    IpPacket& operator=(const IpPacket& other);
    virtual IpPacket *dup() const {return new IpPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNote() const;
    virtual void setNote(int note);
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getSenderIpAddress() const;
    virtual void setSenderIpAddress(int senderIpAddress);
    virtual int getRecverIpAddress() const;
    virtual void setRecverIpAddress(int recverIpAddress);
    virtual bool getIsRequestAck() const;
    virtual void setIsRequestAck(bool isRequestAck);
};

inline void doPacking(cCommBuffer *b, IpPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, IpPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet Data extends IpPacket{
 * 	string value; 
 * }
 * </pre>
 */
class Data : public ::wsn_energy::IpPacket
{
  protected:
    opp_string value_var;

  private:
    void copy(const Data& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Data&);

  public:
    Data(const char *name=NULL, int kind=0);
    Data(const Data& other);
    virtual ~Data();
    Data& operator=(const Data& other);
    virtual Data *dup() const {return new Data(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getValue() const;
    virtual void setValue(const char * value);
};

inline void doPacking(cCommBuffer *b, Data& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Data& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet DIO  extends IpPacket{
 * 	int dodagID; 
 * 	int version; 
 * 	unsigned long rank;   
 * 	double secondCriteria; 
 * }
 * </pre>
 */
class DIO : public ::wsn_energy::IpPacket
{
  protected:
    int dodagID_var;
    int version_var;
    unsigned long rank_var;
    double secondCriteria_var;

  private:
    void copy(const DIO& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DIO&);

  public:
    DIO(const char *name=NULL, int kind=0);
    DIO(const DIO& other);
    virtual ~DIO();
    DIO& operator=(const DIO& other);
    virtual DIO *dup() const {return new DIO(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getDodagID() const;
    virtual void setDodagID(int dodagID);
    virtual int getVersion() const;
    virtual void setVersion(int version);
    virtual unsigned long getRank() const;
    virtual void setRank(unsigned long rank);
    virtual double getSecondCriteria() const;
    virtual void setSecondCriteria(double secondCriteria);
};

inline void doPacking(cCommBuffer *b, DIO& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DIO& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet DIS  extends IpPacket{
 * 	int convergence;
 * }
 * </pre>
 */
class DIS : public ::wsn_energy::IpPacket
{
  protected:
    int convergence_var;

  private:
    void copy(const DIS& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DIS&);

  public:
    DIS(const char *name=NULL, int kind=0);
    DIS(const DIS& other);
    virtual ~DIS();
    DIS& operator=(const DIS& other);
    virtual DIS *dup() const {return new DIS(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getConvergence() const;
    virtual void setConvergence(int convergence);
};

inline void doPacking(cCommBuffer *b, DIS& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DIS& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet ACK extends IpPacket{
 * 	double energy;
 * }
 * </pre>
 */
class ACK : public ::wsn_energy::IpPacket
{
  protected:
    double energy_var;

  private:
    void copy(const ACK& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ACK&);

  public:
    ACK(const char *name=NULL, int kind=0);
    ACK(const ACK& other);
    virtual ~ACK();
    ACK& operator=(const ACK& other);
    virtual ACK *dup() const {return new ACK(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual double getEnergy() const;
    virtual void setEnergy(double energy);
};

inline void doPacking(cCommBuffer *b, ACK& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ACK& obj) {obj.parsimUnpack(b);}

}; // end namespace wsn_energy

#endif // _PACKET_M_H_
