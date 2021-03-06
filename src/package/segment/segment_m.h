//
// Generated file, do not edit! Created by opp_msgc 4.5 from package/segment/segment.msg.
//

#ifndef _WSN_ENERGY_SEGMENT_M_H_
#define _WSN_ENERGY_SEGMENT_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include <ipAddress.h>
// }}


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
 * 	IpAddress destinationPortV6; 
 * 	short length;          
 * 	short checksum;        
 * 	
 * 	int destinationPort; 
 * }
 * </pre>
 */
class UdpPacketStandard : public ::wsn_energy::UdpPacketInterface
{
  protected:
    short sourcePort_var;
    IpAddress destinationPortV6_var;
    short length_var;
    short checksum_var;
    int destinationPort_var;

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
    virtual IpAddress& getDestinationPortV6();
    virtual const IpAddress& getDestinationPortV6() const {return const_cast<UdpPacketStandard*>(this)->getDestinationPortV6();}
    virtual void setDestinationPortV6(const IpAddress& destinationPortV6);
    virtual short getLength() const;
    virtual void setLength(short length);
    virtual short getChecksum() const;
    virtual void setChecksum(short checksum);
    virtual int getDestinationPort() const;
    virtual void setDestinationPort(int destinationPort);
};

inline void doPacking(cCommBuffer *b, UdpPacketStandard& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, UdpPacketStandard& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>package/segment/segment.msg</tt> by opp_msgc.
 * <pre>
 * packet UdpPacketCompressed extends UdpPacketInterface{
 * 
 * 	headerLength = 4; 
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
 * 	bool udpSourcePortCompressed;			
 * 	bool udpDestinationPortCompressed;		
 * 	bool lengthCompressed;				    
 * 	
 * 	
 * 	
 * 	short checksum; 			
 * 
 * 	int inlineLength;				 
 * 	int inlineUdpSourcePort;      
 * 	IpAddress inlineUdpDestinationPortV6; 
 * 	
 * 	int inlineUdpDestinationPort; 
 * }
 * </pre>
 */
class UdpPacketCompressed : public ::wsn_energy::UdpPacketInterface
{
  protected:
    bool udpSourcePortCompressed_var;
    bool udpDestinationPortCompressed_var;
    bool lengthCompressed_var;
    short checksum_var;
    int inlineLength_var;
    int inlineUdpSourcePort_var;
    IpAddress inlineUdpDestinationPortV6_var;
    int inlineUdpDestinationPort_var;

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
    virtual bool getUdpSourcePortCompressed() const;
    virtual void setUdpSourcePortCompressed(bool udpSourcePortCompressed);
    virtual bool getUdpDestinationPortCompressed() const;
    virtual void setUdpDestinationPortCompressed(bool udpDestinationPortCompressed);
    virtual bool getLengthCompressed() const;
    virtual void setLengthCompressed(bool lengthCompressed);
    virtual short getChecksum() const;
    virtual void setChecksum(short checksum);
    virtual int getInlineLength() const;
    virtual void setInlineLength(int inlineLength);
    virtual int getInlineUdpSourcePort() const;
    virtual void setInlineUdpSourcePort(int inlineUdpSourcePort);
    virtual IpAddress& getInlineUdpDestinationPortV6();
    virtual const IpAddress& getInlineUdpDestinationPortV6() const {return const_cast<UdpPacketCompressed*>(this)->getInlineUdpDestinationPortV6();}
    virtual void setInlineUdpDestinationPortV6(const IpAddress& inlineUdpDestinationPortV6);
    virtual int getInlineUdpDestinationPort() const;
    virtual void setInlineUdpDestinationPort(int inlineUdpDestinationPort);
};

inline void doPacking(cCommBuffer *b, UdpPacketCompressed& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, UdpPacketCompressed& obj) {obj.parsimUnpack(b);}

}; // end namespace wsn_energy

#endif // _WSN_ENERGY_SEGMENT_M_H_
