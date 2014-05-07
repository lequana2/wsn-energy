//
//  created on : Mar 5, 2014
//      author : Mr.Quan LE
//      email  : lequana2@gmail.com
//
//  functioning: message code system
//

namespace wsn_energy;

//cplusplus {{
// include whatever
// #include "NetworkPacket_m.h"
//}}

// message kind
enum MESSAGE_KIND{
	DATA    = 2; // BLUE   data to buffer lower/upper
	COMMAND = 4; // YELLOW command to lower
	RESULT  = 1; // GREEN  result from lower
};

// Manual event
enum MANUAL_EVENT{
	NODE_STARTUP  = 0; // turn on a mote
	OUT_OF_ENERGY = 1; // out of energy flag
	NODE_DESTRUCT = 2; // turn off a mote (or) note runs out of energy
};

// App related
enum COMMAND_APP{
	APP_ENVIRON_FLAG = 2; // data from enviroment, to sensor
	APP_SENSING_FLAG = 1; // data from sensor, to apps
	APP_WORKING_FLAG = 0; // data from another node, acts as intermediate node 
	
	RPL_SET_UP_DELAY = 4; // delaying for setting up
};

// Net related
enum COMMAND_NET{
    NET_TIMER_DIO       = 1; // handle self-command handle DIO timer
    NET_TIMER_DIS       = 2; // handle self-command handle DIS timer
	NET_CHECK_BUFFER    = 3; // check packet buffer

	RPL_CONSTRUCT 	 	= 4; // base station ignitation
};

enum RESULT_NET{
	NET_DIO_SENT	= 23; // has sent dio
	NET_DIS_SENT    = 24; // has sent dis
}

// ip packet type
enum IP_PACKET_NEXT_HEADER{
    NEXT_HEADER_UDP		= 0; // UDP packet follows
    NEXT_HEADER_TCP		= 1; // TCP packet follows
    NEXT_HEADER_ICMP	= 2; // ICMP packet follows
};

// icmp packet type
enum ICMP_TYPE{
    ICMP_RPL		= 0; // ICMP RPL
}

// rpl icmp packet type
enum ICMP_CODE{
	RPL_DIO_CODE   	  = 0;	// RPL DIO message
	RPL_DIS_CODE	  = 1;	// RPL DIS message
}

// MAC related
enum COMMAND_MAC{
	CHANNEL_CCA_REQUEST = 70; // request CCA, to PHY
	
	MAC_BEGIN_SEND_FRAME = 73; // begin a sending session of a frame
	MAC_END_SEND_FRAME   = 74; // ends a session of sending a frame, enter IFS 
	MAC_EXPIRE_IFS		 = 75; // IFS has expired, ready for next session
};

enum FRAME_TYPE{
    FRAME_BEACON  	= 35; // frame beacon
    FRAME_COMMAND 	= 36; // frame command
	FRAME_DATA 		= 37; // frame data
	FRAME_ACK  		= 38; // frame ack
}

enum RESULT_FROM_MAC{
    MAC_SEND_DEAD_NEIGHBOR = 5;
	
	MAC_FINISH_PHASE       = 29; // finish 1 transmitting phase    
	MAC_SEND_END_TRANSMIT  = 28; // sent + receive ACK (if needed)
};

// RDC related
enum COMMAND_RDC{
	RDC_TRANSMIT = 30; // transmit
	RDC_LISTEN 	 = 31; // listen
	RDC_IDLE     = 32; // idle
	
	RDC_WAIT_FOR_ACK  = 34; // wait for ack / listenning
	RDC_CHANNEL_CHECK = 35; // channel check
};

enum RESULT_RDC{
	RDC_SEND_OK     = 0; // send + receive ACK (if needed)
	RDC_SEND_NO_ACK = 1; // sent + no ACK (if needed)
	RDC_SEND_FATAL  = 2; // fatal error, abort message
	RDC_SEND_COL	= 3; // collision with PHY
};

// PHY related
enum COMMAND_PHY{
	PHY_BEGIN_CCA       = 10; // radio begin CCA
	PHY_END_CCA         = 11; // radio end CCA
	
 	PHY_SWITCH_TRANSMIT	= 12; // switch to transmit mode
 	PHY_SWITCH_LISTEN	= 13; // switch to listening mode
 	PHY_SWITCH_IDLE     = 14; // switch to sleep mode
 	
 	PHY_BEGIN_TRANSMIT  = 15; // begin transmitting
	PHY_END_TRANSMIT	= 16; // ending transmitting

 	PHY_LISTENING    = 17; // begin listening
 	
 	PHY_IDLING  	 = 18; // begin idling
};

enum RESULT_PHY{
	CHANNEL_CLEAR   	= 10; // CCA clear
	CHANNEL_BUSY    	= 11; // CCA busy
	
	PHY_TX_OK		 = 12; // send okay
	PHY_TX_ERR 		 = 13; // internal error, does not need to resend e.g: packet is too big
	PHY_BUSY		 = 14; // radio is transmitting or receiving
	
	PHY_RECV_OK          = 15; // receive a completed message
	PHY_RECV_CORRUPTED   = 16; // receive a corrupted message
	PHY_RECV_INCOMPLETED = 17; // receive part of a message
};

// Command 
packet Command{
	int note;
}

// Result 
packet Result{
	int note;
}

// Physics
packet Raw{
    // 6 octets preamable
    int headerLength = 6;
    
    // fields
    // SHR synchronisation header
    // 4 octets (4 octets 0x00) preamable sequence
    // 1 octet  (1 octet  0xA7) start of frame delimeter (SFD)
    // PHR physical header
    // 1 octet frame length (does not count it self)
    
    // 127 octets maximum payload length
    // PHY protocol data unit (PPDU)
    int maxPayloadLength = 127;
}

// Frame
packet Frame{
    int numberTransmission = 0; // meta-data: number transmission
    int headerLength; 			// meta-data: determined upon frame creation
    
    // MAC protocol data unit (MPDU) = PHY service data unit (PSDU)
	
	// Frame Control Field 2 octets
	int 	frameType;        		    //  3 bit. Frame type field, see 802.15.4
  	int 	securityEnabled;  		    //  1 bit. True if security is used in this frame
  	int 	framePending;     			//  1 bit. True if sender has more data to send
  	bool 	ackRequired;      			//  1 bit. Is an ack frame required?
  	bool 	panIdCompression; 			//  1 bit. Is this a compressed header?
	int 	reserved; 		     	    //  3 bit. Unused bits
  	int 	destinationAddressMode;     //  2 bit. Destination address mode, see 802.15.4
  	int 	frameVersion;     		    //  2 bit. 802.15.4 frame version
  	int 	sourceAddressMode;          //  2 bit. Source address mode, see 802.15.4
  	
  	// Frame Check Sequence 2 octets FCS = MAC Footer MFR
  	uint16_t frameCheckSequence;
}

// Data frame
packet FrameDataStandard extends Frame{
// 	standard (non-compress) = 25 octets RFC 2460
   	headerLength = 25; // meta-data: length of this frame    
    
  	int dataSequenceNumber;	// 1 octet. Sequence number
  	
	int sourcePanID;	  		// 0/2   octets PANID
	int destinationPanID; 		// 0/2   octets PANID
	int sourceMacAddress; 		// 0/2/8 octets link-layer address address
	int destinationMacAddress;  // 0/2/8 octets link-layer addressaddress
}

packet FrameDataCompressed extends Frame{
//	 compressed = 8 octets + normal header 25 octets
	 int headerLength = 32;
	
// 		order of header (sicslowmac)
//		5 octets: Mesh Addressing Header (short address)
//      2 octet:  Broadcast Header 
//      1 octet:  Fragmentation Header (not implemented yet)
// 		Header Compressed Header (dispatch)
//
// 		4 octets minimum Mesh header 4944
// 		0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//      |1 0|O|F|HopsLft| originator address, final address
//      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//	O: This 1-bit field SHALL be zero if the Originator Address is an
//      IEEE extended 64 bit address (EUI-64), or 1 if it is a short 16-
//      bit addresses.
//
//  F: This 1-bit field SHALL be zero if the Final Destination Address is
//      an IEEE extended 64 bit address (EUI-64), or 1 if it is a short
//      16-bit addresses.
//
//  Hops Left:  This 4-bit field SHALL be decremented by each forwarding
//      node before sending this packet towards its next hop.  The packet
//      is not forwarded any further if Hops Left is decremented to 0.
//      The value 0xF is reserved and signifies an 8-bit Deep Hops Left
//      field immediately following, and allows a source node to specify a
//      hop limit greater than 14 hops.
//
// 	Originator Address:  This is the link-layer address of the
//      Originator.
//
//  Final Destination Address:  This is the link-layer address of the
//      Final Destination.
//
//   Note that the 'O' and 'F' bits allow for a mix of 16 and 64-bit
//   addresses.  This is useful at least to allow for mesh layer
//   "broadcast", as 802.15.4 broadcast addresses are defined as 16-bit
//   short addresses.
//
//  2 octets Broadcast Header 
//                           1
//       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
//      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//      |0|1|LOWPAN_BC0 |Sequence Number|
//      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//	1 octet dispatch (pattern - header)
//		  | 00  xxxxxx | NALP       - Not a LoWPAN frame               
//        | 01  000001 | IPv6       - uncompressed IPv6 Addresses      <-- ATTENTION
//        | 01  000010 | LOWPAN_HC1 - LOWPAN_HC1 compressed IPv6       <-- ATTENTION
//        |   ...      | reserved   - Reserved for future use          
//        | 01  010000 | LOWPAN_BC0 - LOWPAN_BC0 broadcast   <-- ATTENTION          
//        |   ...      | reserved   - Reserved for future use          
//        | 01  111111 | ESC        - Additional Dispatch octet follows 
}

// ACK Frame
packet FrameACK extends Frame{
	headerLength = 3; // empty

   	int dataSequenceNumber;          	// 8 bit. Sequence number
}

// In case of synchronize, and neighbor discovery (unslotted CSMA/CA)
packet FrameBeacon extends Frame{
	headerLength = 26;
    
	int beaconSequenceNumber;	// 1 octet. Sequence number
	
	int sourcePanID;	  		// 0/2   octets PANID
	int destinationPanID; 		// 0/2   octets PANID
	int sourceMacAddress; 		// 0/2/8 octets link-layer address address
	int destinationMacAddress;  // 0/2/8 octets link-layer addressaddress
  	
  	// 2 octets Superframe specification
  	int beaconOrder;			// 4 bit
  	int superFrameOrder;		// 4 bit
  	int finalCAPslot;			// 4 bit
  	int batteryLifeExtension;	// 1 bit
  	int reserved;				// 1 bit
  	int PANcoordinator;			// 1 bit
  	int associationPermit;		// 1 bit

	// variable GTS
	// variable pendingAddressFields
	// variable beaconPayload
}

// In case of synchronize, and neighbor discovery (unslotted CSMA/CA)
packet FrameCommand extends Frame{
    headerLength = 25;
    
	int dataSequenceNumber;	// 8 bit. Sequence number
	
	int sourcePanID;	  		// 0/2   octets PANID
	int destinationPanID; 		// 0/2   octets PANID
	int sourceMacAddress; 		// 0/2/8 octets link-layer address address
	int destinationMacAddress;  // 0/2/8 octets link-layer addressaddress
  	
  	// 1 octets Command type
  	int commandType; // 8 bit

	//	Association request
	//	Association response
	//	Disassociation notification
	//	Data request
	//	PAN ID conflict notification
	//	Orphan Notification
	//	Beacon request
	//	Coordinator realignment
	//	GTS request

	// variable command payload
}

// Packet
packet IpPacketInterface{
    double time;  			// meta-data: timestamp
    int 	headerLength; 	// meta-data: header length, depends on specific format
}

packet IpPacketStandard extends IpPacketInterface{  
// 		standard (non-compress) = 40 octets RFC 2460
    headerLength = 40;
    
//     4 bits version
//     8 bits traffic class
//     20 bits flow label
//     2 octets payload length
//     1 octets next header
//     1 octets hop limit
//     16 octets IPv6 source
//     16 octets IPv6 destination
    
    int version;
    int trafficClass;
    int flowLabel;
    int payloadLength;
    int nextHeader; // type: ICMP, UDP, TCP
    int hopLimit;
    int sourceIpAddress;
    int destinationIpAddress;
}

packet IpPacketCompressed extends IpPacketInterface{
//	This common IPv6 header (as mentioned above) can
//	be compressed to 2 octets (1 octet for the HC1 encoding and 1 octet
//	for the Hop Limit), instead of 40 octets
//    
//    payload length included in 802.15.4 header
//    IPv6 source deprived from 802.15.4 header (link-layer address), reduce 16 octets 
//    IPv6 destination deprived from 802.15.4 header (link-layer address), reduce 16 octets 

//  	compressed HC1 = 2 octets RFC 4944
	
	headerLength = 2;

//	The "HC1 encoding" is shown below (starting with bit 0 and ending at
//  bit 7):
//
//		PI = prefix carried in-line non-compressed		
//		PC = prefix compressed
//		II = interface identifier in-line
//		IC = interface identifier compressed
//		
//  IPv6 source address (bits 0 and 1):
//  	00:  PI, II
//  	01:  PI, IC
//  	10:  PC, II
//  	11:  PC, IC
//
//  IPv6 destination address (bits 2 and 3):
//  	00:  PI, II
//  	01:  PI, IC
//  	10:  PC, II
//  	11:  PC, IC
//
//  Traffic Class and Flow Label (bit 4):
//  	0: not compressed, full 8 bits for Traffic Class and 20 bits
//     		for Flow Label are sent
//		1: Traffic Class and Flow Label are zero
//
//  Next Header (bits 5 and 6):
//  	00:  not compressed, full 8 bits are sent
//  	01:  UDP
//  	10:  ICMP
//  	11:  TCP
//
//  HC2 encoding(bit 7):
//  	0: No more header compression bits
//  	1: HC1 encoding immediately followed by more header compression
//     		bits per HC2 encoding format.  Bits 5 and 6 determine which
//     		of the possible HC2 encodings apply (e.g., UDP, ICMP or TCP
//     		encodings).

	int sourceIPAddress; 			// 2 bits + 0 bit compressed/ 128 bits non-compressed
	int destinationIPAddress; 		// 2 bits + 0 bit compressed/ 128 bits non-compressed
	int trafficClassAndFlowLabel; 	// 1 bit + 0 bit compressed/  28 bits non-compressed
	int nextHeader;					// 2 bits + 0 bit compressed/ 8 bits non-compressed
	int hc2encoding;				// 1 bit (determines whether any header compression bits)
}

// ICMP Packet
packet IcmpPacket{
	// standard (non-compress) = 8 octets
	int headerLength = 8;
	
	// 1 octets of type
	// 1 octets of code
	// 2 octets of checksum
	// 2 octets of other message specific information
	
	int type; // RPL ICMPv6
	int code; // DIO, DIS
	int checksum; 
	int others;
}

packet DIO{
    // WSN ??? octets
	int dodagID; // DODAGID
	int version; // version
	
	unsigned long rank; // rank 
	
	double selfEnergy;   // option: energy-history
	
	// length
	int payloadLength = 25;
}

packet DIS{
	// WSN ??? octets
	int payloadLength = 1;
}

// Segment
packet UdpPacketInterface{
    int headerLength; // meta-data: header length, depends on specific format
}

packet UdpPacketStandard extends UdpPacketInterface{
// 	standard (non-compress) = 8 octets

	headerLength = 8;  // meta-data: header length, carried in-line

	short sourcePort;      // 2 octets of source port
	short destinationPort; // 	2 octets of destination port
	short length;          // 	2 octets of packet length
	short checksum;        // 	2 octets of check sum of pseudo-header (IP header) 
}

packet UdpPacketCompressed extends UdpPacketInterface{
// 	compressed HC1 = 3 octets RFC 4944

	headerLength = 3; // meta-data: header length, carried in-line

//	The UDP header's checksum field is not compressed and is therefore carried in full.
//
//                      1                   2                   3
//      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//      |HC_UDP encoding|     Fields carried in-line follow...
//      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//         Figure 16: HC_UDP (UDP common compressed header encoding)
//
//	UDP source port (bit 0):
//        0: Not compressed, carried "in-line" (Section 10.3.2)
//        1: Compressed to 4 bits.  The actual 16-bit source port is
//           obtained by calculating: P + short_port value.  The value of
//           P is the number 61616 (0xF0B0).  The short_port is expressed
//           as a 4-bit value which is carried "in-line" (Section 10.3.2)
//
//  UDP destination port (bit 1):
//        0: Not compressed, carried "in-line" (Section 10.3.2)
//        1: Compressed to 4 bits.  The actual 16-bit destination port is
//           obtained by calculating: P + short_port value.  The value of
//           P is the number 61616 (0xF0B0).  The short_port is expressed
//           as a 4-bit value which is carried "in-line" (Section 10.3.2)
//
//  Length (bit 2):
//        0: not compressed, carried "in-line" (Section 10.3.2)
//        1: compressed, length computed from IPv6 header length
//           information.  The value of the UDP length field is equal to
//           the Payload Length from the IPv6 header, minus the length of
//           any extension headers present between the IPv6 header and
//           the UDP header.
//
//  Reserved (bit 3 through 7)
	
	bool udpSourcePort;			// 1 bit + 4 bit compressed/ 16 bits non-compressed 
	bool udpDestinationPort;	// 1 bit + 4 bit compressed/ 16 bits non-compressed
	short length;				// 1 bit + 0 bit compressed/ 16 bits non-compressed
	short checksum; 			// 2 octets ALWAYS non-compressed
}

// Data
packet Data{
    double time;  		// meta-data: timestamp upon sending
    
    int destinationPort; 	  // control-data: destination port
    int destinationIPAddress; // control-data: destination IP Address
    
	string value; 		// undefined length, data to be sent to server
}