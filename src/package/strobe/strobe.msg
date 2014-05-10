//
//  created on : Mar 5, 2014
//      author : Mr.Quan LE
//      email  : lequana2@gmail.com
//
//  functioning: strobe command
//

namespace wsn_energy;

// message kind
enum KIND{
	DATA    = 2; // BLUE   data to buffer lower/upper
	COMMAND = 4; // YELLOW command to lower
	RESULT  = 1; // GREEN  result from lower
};

// Command 
packet Command{
	int note;
}

// Result 
packet Result{
	int note;
}

// Manual event
enum MANUAL_EVENT{
	NODE_STARTUP  = 0; // turn on a mote
	OUT_OF_ENERGY = 1; // out of energy flag
	NODE_DESTRUCT = 2; // turn off a mote (or) note runs out of energy
};

// App related
enum COMMAND_APP{
	APP_ENVIRON_FLAG = 0; // data from enviroment, to sensor
	APP_SENSING_FLAG = 1; // data from sensor, to apps
	
	RPL_SET_UP_DELAY = 2; // flag for delaying for setting up
};

// Net related
enum COMMAND_NET{
    RPL_CONSTRUCT 	 	= 0; // base station ignitation
    
    NET_TIMER_DIO       = 1; // handle self-command handle DIO timer
    NET_TIMER_DIS       = 2; // handle self-command handle DIS timer
	
	NET_CHECK_BUFFER    = 3; // check packet buffer
};

enum RESULT_NET{
	NET_DIO_SENT	= 10; // has sent dio
	NET_DIS_SENT    = 11; // has sent dis
}

// ip packet type
enum IP_PACKET_NEXT_HEADER{
    NEXT_HEADER_UDP		= 0; // UDP  packet follows
    NEXT_HEADER_TCP		= 1; // TCP  packet follows
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
	MAC_CCA_REQUEST = 0; // request CCA, to PHY
	
	MAC_ASK_SEND_FRAME 	 = 1; // ask RDC to send a transmission phase of a frame
	
	MAC_BEGIN_SEND_TURN  = 2; // start 1 turn in a transmission phase 
	
	MAC_END_SEND_FRAME   = 3; // ends a session of sending a frame, enter IFS 
	
	MAC_EXPIRE_IFS		 = 4; // IFS has expired, ready for next frame
};

enum FRAME_TYPE{
    FRAME_BEACON  	= 0; // frame beacon
    FRAME_COMMAND 	= 1; // frame command
	FRAME_DATA 		= 2; // frame data
	FRAME_ACK  		= 3; // frame ack
}

enum RESULT_FROM_MAC{
    MAC_SEND_DEAD_NEIGHBOR = 0; // inform a dead neighbor
	
	MAC_FINISH_PHASE       = 1; // finish 1 transmitting phase    
	MAC_SEND_END_TRANSMIT  = 2; // sent + receive ACK (if needed)
};

// RDC related
enum COMMAND_RDC{
	RDC_TRANSMIT = 0; // transmit
	RDC_LISTEN 	 = 1; // listen
	RDC_IDLE     = 2; // idle
	
	RDC_CCA_REQUEST = 3; // cca -> listening and then checking result, does not turn off radio
	
	RDC_CHANNEL_CHECK = 4; // channel check
	RDC_SEND_FRAME    = 5; // send frame
	
	RDC_CCA_TIME_OUT  = 6; // cca time out
};

enum RESULT_RDC{
	RDC_READY_TRANS_PHASE = 0; // begin transmission session, turn off periodical check
    RDC_STOP_TRANS_PHASE  = 1; // stop transmission session,  turn on periodical check
    
    RDC_BEGIN_TRANS_TURN  = 2; // begin a transmission (in one turn 6 maximum CCA + 1 trans)
    
    // after 1 transmission turn (consists of one/many time(s))
	RDC_SEND_OK     	  = 3; // send + receive ACK (if needed)
	RDC_SEND_NO_ACK 	  = 4; // sent + no ACK (if needed)
	RDC_SEND_FATAL        = 5; // fatal error, abort message
	RDC_SEND_COL	      = 6; // collision with PHY
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

 	PHY_LISTENING    	= 17; // begin listening
 	
 	PHY_IDLING  	 	= 18; // begin idling
};

enum RESULT_PHY{
    // CCA result
	CHANNEL_CLEAR   	= 10; // CCA clear
	CHANNEL_BUSY    	= 11; // CCA busy
	
	// transmission result
	PHY_TX_OK		 	= 12; // send okay
	PHY_TX_ERR 		 	= 13; // internal error, does not need to resend e.g: packet is too big
};