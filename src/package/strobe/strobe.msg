//
//  created on : Mar 5, 2014
//      author : Mr.Quan LE
//      email  : lequana2@gmail.com
//
//  functioning: strobe command
//

namespace wsn_energy;

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
	FRAME_TRANS_REQUEST = 71; // request a session to send 
	
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

	RDC_READY_TRANS_PHASE = 4; // begin transmission session, turn off periodical check
	RDC_STOP_TRANS_PHASE  = 5; // stop transmission session, turn on periodical check
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