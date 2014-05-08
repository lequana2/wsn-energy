//
// Generated file, do not edit! Created by opp_msgc 4.4 from package/segment/segment.msg.
//

#ifndef _SEGMENT_M_H_
#define _SEGMENT_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0404
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif


namespace wsn_energy {

/**
 * Class generated from <tt>package/segment/segment.msg</tt> by opp_msgc.
 * <pre>
 * packet UdpPacketInterface{
 *     int headerLength; 
 * }
 * </pre>
 */
class UdpPacketInterface : public ::cPacket
{
  protected:
    int headerLength_var;

  private:
    void copy(const UdpPacketInterface& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const UdpPacketInterface&);

  public:
    UdpPacketInterface(const char *name=NULL, int kind=0);
    UdpPacketInterface(const UdpPacketInterface& other);
    virtual ~UdpPacketInterface();
    UdpPacketInterface& operator=(const UdpPacketInterface& other);
    virtual UdpPacketInterface *dup() const {return new UdpPacketInterface(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getHeaderLength() const;
    virtual void setHeaderLength(int headerLength);
};

inline void doPacking(cCommBuffer *b, UdpPacketInterface& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, UdpPacketInterface& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>package/segment/segment.msg</tt> by opp_msgc.
 * <pre>
 * packet UdpPacketStandard extends UdpPacketInterface{
 * 
 * 
 * 	headerLength = 8;  
 * 
 * 	short sourcePort;      
 * 	short destinationPort; 
 * 	short length;          
 * 	short checksum;        
 * }
 * </pre>
 */
class UdpPacketStandard : public ::wsn_energy::UdpPacketInterface
{
  protected:
    short sourcePort_var;
    short destinationPort_var;
    short length_var;
    short checksum_var;

  private:
    void copy(const UdpPacketStandard& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const UdpPacketStandard&);

  public:
    UdpPacketStandard(const char *name=NULL, int kind=0);
    UdpPacketStandard(const UdpPacketStandard& other);
    virtual ~UdpPacketStandard();
    UdpPacketStandard& operator=(const UdpPacketStandard& other);
    virtual UdpPacketStandard *dup() const {return new UdpPacketStandard(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual short getSourcePort() const;
    virtual void setSourcePort(short sourcePort);
    virtual short getDestinationPort() const;
    virtual void setDestinationPort(short destinationPort);
    virtual short getLength() const;
    virtual void setLength(short length);
    virtual short getChecksum() const;
    virtual void setChecksum(short checksum);
};

inline void doPacking(cCommBuffer *b, UdpPacketStandard& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, UdpPacketStandard& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>package/segment/segment.msg</tt> by opp_msgc.
 * <pre>
 * packet UdpPacketCompressed extends UdpPacketInterface{
 * 
 * 
 * 	headerLength = 3; 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 	
 * 	bool udpSourcePort;			
 * 	bool udpDestinationPort;	
 * 	short length;				
 * 	short checksum; 			
 * }
 * </pre>
 */
class UdpPacketCompressed : public ::wsn_energy::UdpPacketInterface
{
  protected:
    bool udpSourcePort_var;
    bool udpDestinationPort_var;
    short length_var;
    short checksum_var;

  private:
    void copy(const UdpPacketCompressed& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const UdpPacketCompressed&);

  public:
    UdpPacketCompressed(const char *name=NULL, int kind=0);
    UdpPacketCompressed(const UdpPacketCompressed& other);
    virtual ~UdpPacketCompressed();
    UdpPacketCompressed& operator=(const UdpPacketCompressed& other);
    virtual UdpPacketCompressed *dup() const {return new UdpPacketCompressed(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool getUdpSourcePort() const;
    virtual void setUdpSourcePort(bool udpSourcePort);
    virtual bool getUdpDestinationPort() const;
    virtual void setUdpDestinationPort(bool udpDestinationPort);
    virtual short getLength() const;
    virtual void setLength(short length);
    virtual short getChecksum() const;
    virtual void setChecksum(short checksum);
};

inline void doPacking(cCommBuffer *b, UdpPacketCompressed& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, UdpPacketCompressed& obj) {obj.parsimUnpack(b);}

}; // end namespace wsn_energy

#endif // _SEGMENT_M_H_
