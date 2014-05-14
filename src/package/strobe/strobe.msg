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
    NET_TIMER_DIO       = 0; // handle self-command handle DIO timer
    NET_TIMER_DIS       = 1; // handle self-command handle DIS timer
	
	NET_CHECK_BUFFER    = 2; // check packet buffer
};

// MAC related
enum COMMAND_MAC{
	MAC_CCA_REQUEST = 0; // request CCA, to PHY
	
	MAC_ASK_SEND_FRAME 	 = 1; // ask RDC to send a transmission phase of a frame
	MAC_BEGIN_SEND_TURN  = 2; // start 1 turn in a transmission phase 
	MAC_END_SEND_FRAME   = 3; // ends a session of sending a frame, enter IFS 
	MAC_EXPIRE_IFS		 = 4; // IFS has expired, ready for next frame
};

enum RESULT_FROM_MAC{
	MAC_FINISH_PHASE       = 0; // finish 1 transmitting phase
    MAC_SEND_DEAD_NEIGHBOR = 1; // inform a dead neighbor
};

// RDC related
enum COMMAND_RDC{
    // command to radio
	RDC_TRANSMIT = 0; // transmit
	RDC_LISTEN 	 = 1; // listen
	RDC_IDLE     = 2; // idle
	
	// cca -> listening and then checking result, does not turn off radio	
	RDC_CCA_REQUEST = 3; 
	
	RDC_CHANNEL_CHECK = 4; // channel check
	RDC_SEND_FRAME    = 5; // send frame
	
	// self timer
	RDC_CCA_TIME_OUT   = 6; // cca time out
	RDC_PHASE_TIME_OUT = 7; // phase time out

	// begin a transmission (in one turn 6 maximum CCA + 1 trans)
	RDC_BEGIN_TRANS_TURN  = 8; 
};

enum RESULT_RDC{
	// inform RDC is free	
	RDC_READY_TRANS_PHASE = 0; // begin transmission session, turn off periodical check
    
    // after 1 transmission turn (consists of one/many time(s))
	RDC_SEND_OK     	  = 3; // send + receive ACK (if needed)
	RDC_SEND_NO_ACK 	  = 4; // sent + no ACK (if needed)
	RDC_SEND_FATAL        = 5; // fatal error, abort message
	RDC_SEND_COL	      = 6; // collision with PHY
};

// PHY related
enum COMMAND_PHY{
	PHY_BEGIN_CCA       = 0; // radio begin CCA
	PHY_END_CCA         = 1; // radio end CCA
	
 	PHY_SWITCH_TRANSMIT	= 2; // switch to transmit mode
 	PHY_BEGIN_TRANSMIT  = 3; // begin transmitting
	PHY_END_TRANSMIT	= 4; // ending transmitting

	PHY_SWITCH_LISTEN	= 5; // switch to listening mode
 	PHY_LISTENING    	= 6; // begin listening

	PHY_SWITCH_IDLE     = 7; // switch to sleep mode 	
 	PHY_IDLING  	 	= 8; // begin idling
};

enum RESULT_PHY{
    // CCA result
	CHANNEL_CLEAR   	= 10; // CCA clear
	CHANNEL_BUSY    	= 11; // CCA busy
	
	// transmission result
	PHY_TX_OK		 	= 12; // send okay
	PHY_TX_ERR 		 	= 13; // internal error, does not need to resend e.g: packet is too big
};