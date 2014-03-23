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


namespace wsn_energy {

/**
 * Enum generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * enum MESSAGE
 * {
 * 	
 * 	NODE_STARTUP  = 0;
 * 	NODE_DESTRUCT = 1;
 * 	OUT_OF_ENERGY = 2;
 * 	RPL_CONSTRUCT = 3;
 * 	RPL_SOLICIT   = 4;
 * 
 * 	
 *  	LAYER_RADIO     		= 10; 
 *  	LAYER_RADIO_END_TRANS	= 11;
 *  	LAYER_RADIO_END_RECV    = 12;
 * 	LAYER_RADIO_OK			= 13;
 * 	LAYER_RADIO_COL 		= 14;
 * 
 * 	
 * 	LAYER_RDC        = 20; 
 * 	
 * 	
 * 	LAYER_MAC     = 31; 
 * 
 * 	
 * 	LAYER_NET     = 32; 
 * 	NET_ICMP_DIO  = 40;
 * 	NET_ICMP_DIS  = 41;
 * 	NET_DATA      = 42;
 * 	
 * 	
 * 	LAYER_APP		 = 50; 
 * 	APP_WORKING_FLAG = 51; 
 * 	APP_ENVIRON_FLAG = 52;
 * 	APP_SENSING_FLAG = 53;
 * }
 * </pre>
 */
enum MESSAGE {
    NODE_STARTUP = 0,
    NODE_DESTRUCT = 1,
    OUT_OF_ENERGY = 2,
    RPL_CONSTRUCT = 3,
    RPL_SOLICIT = 4,
    LAYER_RADIO = 10,
    LAYER_RADIO_END_TRANS = 11,
    LAYER_RADIO_END_RECV = 12,
    LAYER_RADIO_OK = 13,
    LAYER_RADIO_COL = 14,
    LAYER_RDC = 20,
    LAYER_MAC = 31,
    LAYER_NET = 32,
    NET_ICMP_DIO = 40,
    NET_ICMP_DIS = 41,
    NET_DATA = 42,
    LAYER_APP = 50,
    APP_WORKING_FLAG = 51,
    APP_ENVIRON_FLAG = 52,
    APP_SENSING_FLAG = 53
};

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet Raw{
 *     int typeRadioLayer;
 *     int len;
 *     bool bitError;
 *     int radioSendId;
 *     int radioRecvId;
 * }
 * </pre>
 */
class Raw : public ::cPacket
{
  protected:
    int typeRadioLayer_var;
    int len_var;
    bool bitError_var;
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
    virtual int getTypeRadioLayer() const;
    virtual void setTypeRadioLayer(int typeRadioLayer);
    virtual int getLen() const;
    virtual void setLen(int len);
    virtual bool getBitError() const;
    virtual void setBitError(bool bitError);
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
 * packet Frame extends Raw{
 * 	int typeMacLayer;
 * 	int senderMacAddress;
 * 	int recverMacAddress;
 * }
 * </pre>
 */
class Frame : public ::wsn_energy::Raw
{
  protected:
    int typeMacLayer_var;
    int senderMacAddress_var;
    int recverMacAddress_var;

  private:
    void copy(const Frame& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Frame&);

  public:
    Frame(const char *name=NULL, int kind=0);
    Frame(const Frame& other);
    virtual ~Frame();
    Frame& operator=(const Frame& other);
    virtual Frame *dup() const {return new Frame(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getTypeMacLayer() const;
    virtual void setTypeMacLayer(int typeMacLayer);
    virtual int getSenderMacAddress() const;
    virtual void setSenderMacAddress(int senderMacAddress);
    virtual int getRecverMacAddress() const;
    virtual void setRecverMacAddress(int recverMacAddress);
};

inline void doPacking(cCommBuffer *b, Frame& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Frame& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet IpPacket extends Frame{
 *     int typeNetLayer;
 *     int senderIpAddress;
 *     int recverIpAddress;
 * }
 * </pre>
 */
class IpPacket : public ::wsn_energy::Frame
{
  protected:
    int typeNetLayer_var;
    int senderIpAddress_var;
    int recverIpAddress_var;

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
    virtual int getTypeNetLayer() const;
    virtual void setTypeNetLayer(int typeNetLayer);
    virtual int getSenderIpAddress() const;
    virtual void setSenderIpAddress(int senderIpAddress);
    virtual int getRecverIpAddress() const;
    virtual void setRecverIpAddress(int recverIpAddress);
};

inline void doPacking(cCommBuffer *b, IpPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, IpPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet Data extends IpPacket {
 * 	int value;
 * }
 * </pre>
 */
class Data : public ::wsn_energy::IpPacket
{
  protected:
    int value_var;

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
    virtual int getValue() const;
    virtual void setValue(int value);
};

inline void doPacking(cCommBuffer *b, Data& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Data& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet DIO extends IpPacket {
 * 	int dodagID;
 * 	unsigned long rank;
 * 	int version;
 * }
 * </pre>
 */
class DIO : public ::wsn_energy::IpPacket
{
  protected:
    int dodagID_var;
    unsigned long rank_var;
    int version_var;

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
    virtual unsigned long getRank() const;
    virtual void setRank(unsigned long rank);
    virtual int getVersion() const;
    virtual void setVersion(int version);
};

inline void doPacking(cCommBuffer *b, DIO& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DIO& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>packet/packet.msg</tt> by opp_msgc.
 * <pre>
 * packet DIS extends IpPacket {
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

}; // end namespace wsn_energy

#endif // _PACKET_M_H_
