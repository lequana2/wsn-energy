//
//  created on : Mar 5, 2014
//      author : Mr.Quan LE
//      email  : lequana2@gmail.com
//
//  functioning: message code system
//

cplusplus {{
	#include "packet_len.h"
}}

namespace wsn_energy;

enum MESSAGE_KIND{
	COMMAND = 4; // YELLOW command to lower
	RESULT  = 1; // GREEN result from lower
	DATA    = 2; // BLUE data to buffer lower/upper
};

// Environment
enum SPECIAL_EVENT{
	NODE_STARTUP  = 0; // turn on a mote
	OUT_OF_ENERGY = 1; // out of energy flag
	NODE_DESTRUCT = 2; // turn off a mote (or) note runs out of energy
};

// App layer
enum COMMAND_FROM_APP{
	APP_WORKING_FLAG = 0; // data from another node 
	APP_SENSING_FLAG = 1; // data from sensor
	APP_ENVIRON_FLAG = 2; // data from enviroment
	
	RPL_CONSTRUCT = 3; // perform broadcasting DIO
	RPL_SOLICIT   = 4; // request DIS
};

// Net layer
enum COMMAND_FROM_NET{
    NET_CHECK_BUFFER       = 0;  // self-check its buffer
    NET_TIMER_DIO          = 1;  // handle DIO timer
};

// ip packet type
enum IP_PACKET_TYPE{
	NET_DATA        	  = 0;  // normal data message
	NET_ICMP_RPL		  = 1;  // kind of ICMP
	
	NET_ICMP_DIO    	  = 2;	// ICMP DIO message
	NET_ICMP_DIS    	  = 3;	// ICMP DIS message
};

// MAC layer command
enum COMMAND_FROM_MAC{
	CHANNEL_CCA_REQUEST = 70; // request CCA
	MAC_SEND_BUFFER     = 71; // send
};

// MAC layer result
enum RESULT_FROM_MAC{
	MAC_SEND_OK		= 0; // sent + receive ACK (if needed)
	MAC_SEND_NO_ACK = 1; // sent + no ACK (if needed)
	MAC_SEND_FATAL  = 2; // fatal error, abort message
	MAC_SEND_ERROR  = 3; // exceed total number of transmission, try again later
};

// RDC layer command
enum COMMAND_FROM_RDC{
	RDC_SEND   = 30; // transmit
	RDC_LISTEN = 31; // listen
	RDC_IDLE   = 32; // idle
	
	RDC_WAIT_FOR_ACK = 34; // wait for ack / listenning
};

// RDC layer result
enum RESULT_FROM_RDC{
	RDC_SEND_OK     = 0; // send + receive ACK (if needed)
	RDC_SEND_NO_ACK = 1; // sent + no ACK (if needed)
	RDC_SEND_FATAL  = 2; // fatal error, abort message
	RDC_SEND_COL	= 3; // collision with PHY
};

// PHY layer
enum COMMAND_FROM_PHY{
	PHY_BEGIN_CCA       = 10; // radio begin CCA ???
	PHY_END_CCA         = 11; // radio end CCA
	
 	PHY_SWITCH_TRANSMIT	= 12; // switch to transmit mode
 	PHY_SWITCH_LISTEN	= 13; // switch to listening mode
 	PHY_SWITCH_IDLE     = 14; // switch to sleep mode
 	
 	PHY_BEGIN_TRANSMIT  = 15; // begin transmitting
	PHY_END_TRANSMIT	= 16; // ending transmitting

 	PHY_LISTENING    = 17; // begin listening
 	
 	PHY_IDLING  	 = 18; // begin idling
};

enum RESULT_FROM_PHY{
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

// Data
packet Raw{
}

packet FrameRDC{
	int note;  // control message
	
	bool isACK; // is ACK frame
}

packet FrameMAC{
    int numberTransmission = 0; // meta-data: number transmission

	int sequenceNumber;   // sequence number    	
	int senderMacAddress; // sender MAC address
	int recverMacAddress; // recver MAC address
}

packet IpPacket{
	int messageCode;	// type message (Data, ICMP)
	int icmpCode;       // ICMP type

	bool isBroadcast;   // is multicasted to all neighbors

    int senderIpAddress; // sender IP address
    int recverIpAddress; // recver IP address
}

packet DIO  extends IpPacket{
	int dodagID; // DODAGID
	int version; // version
	
	unsigned long rank; // rank 
	
	double selfEnergy;   // option: energy-history
}

packet DIS  extends IpPacket{
	int hopTTL;
}

packet UdpPacket{
    int sourceIpAddress; // sensor node IP address
	int sinkIpAddress;   // base station IP address
}

packet Data{
    double time;  // meta-data: timestamp upon sending
    
	string value; // data to be sent to server
}