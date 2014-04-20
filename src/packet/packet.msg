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
	RESULT  = 1; // GREEN result from lower
	DATA    = 2; // BLUE data to buffer lower/upper
	COMMAND = 4; // YELLOW command to lower
};

// Environment
enum SPECIAL_EVENT{
	NODE_STARTUP  = 0; // turn on a mote
	OUT_OF_ENERGY = 1; // out of energy flag
	NODE_DESTRUCT = 2; // turn off a mote (or) note runs out of energy
};

// App layer
enum COMMAND_APP{
	APP_ENVIRON_FLAG = 2; // data from enviroment, to sensor
	APP_SENSING_FLAG = 1; // data from sensor, to apps
	APP_WORKING_FLAG = 0; // data from another node, acts as intermediate node 
	
	RPL_CONSTRUCT 	 = 3; // base station ignitation
	RPL_SET_UP_DELAY = 4; // delay for setting up
};

// Net layer command
enum COMMAND_NET{
    NET_TIMER_DIO       = 1;  // self-command handle DIO timer
    NET_TIMER_DIS       = 2;  // self-command handle DIS timer

	NET_CHECK_BUFFER    = 3; // check buffer
};

// Net layer result
enum RESULT_NET{
	NET_DIO_SENT	= 23; // has send dio
	NET_DIS_SENT    = 24; // has send dis
}

// ip packet type
enum IP_PACKET_TYPE{
	NET_DATA        	  = 1;  // normal data message
	
	NET_ICMP_RPL		  = 2;  // kind of ICMP
	NET_ICMP_DIO    	  = 3;	// ICMP DIO message
	NET_ICMP_DIS    	  = 4;	// ICMP DIS message
};

// MAC layer command
enum COMMAND_MAC{
	CHANNEL_CCA_REQUEST = 70; // request CCA, to PHY
	
	MAC_BEGIN_SEND_FRAME = 73; // begin sending a frame
	MAC_END_SEND_FRAME   = 74; // after sending a frame, begin interframe space (sifs/lifs)
	MAC_EXPIRE_IFS		 = 75; // IFS has expired, ready for next frame
};

// MAC layer result
enum RESULT_FROM_MAC{
    MAC_SEND_DEAD_NEIGHBOR = 5;
	
	MAC_FINISH_PHASE       = 29; // finish 1 transmitting phase    
	MAC_SEND_END_TRANSMIT  = 28; // sent + receive ACK (if needed)
};

// RDC layer command
enum COMMAND_RDC{
	RDC_TRANSMIT = 30; // transmit
	RDC_LISTEN 	 = 31; // listen
	RDC_IDLE     = 32; // idle
	
	RDC_WAIT_FOR_ACK = 34; // wait for ack / listenning
};

// RDC layer result
enum RESULT_RDC{
	RDC_SEND_OK     = 0; // send + receive ACK (if needed)
	RDC_SEND_NO_ACK = 1; // sent + no ACK (if needed)
	RDC_SEND_FATAL  = 2; // fatal error, abort message
	RDC_SEND_COL	= 3; // collision with PHY
};

// PHY layer
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

// Data
packet Raw{
}

packet Frame{
    int numberTransmission = 0; // meta-data: number transmission

	int sequenceNumber;   // sequence number    	
	bool isACK; 		  // is ACK frame

	int senderMacAddress; // sender MAC address
	int recverMacAddress; // recver MAC address
}

packet IpPacket{
	int messageCode;	// type message (Data, ICMP)
	int icmpCode;       // ICMP type

    double time;  // meta-data: timestamp upon sending

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
}

packet UdpPacket{
    int sourceIpAddress; // sensor node IP address
	int sinkIpAddress;   // base station IP address
}

packet Data{
    double time;  // meta-data: timestamp upon sending
    
	string value; // data to be sent to server
}