//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

cplusplus {{
	#include "packet_len.h"
}}

namespace wsn_energy;

enum COMMAND_AND_RESULT
{
	// physics event
	NODE_STARTUP  = 0; // turn on a mote
	NODE_DESTRUCT = 1; // turn off a mote (or) note runs out of energy
	OUT_OF_ENERGY = 2; // out of energy flag
	
	// self event
	RPL_CONSTRUCT = 3; // perform broadcasting DIO
	RPL_SOLICIT   = 4; // request DIS

	// radio
 	LAYER_RADIO     			= 10; // kind
 	
 	LAYER_RADIO_SWITCH_TRANSMIT	= 11; // switch to transmit mode
 	LAYER_RADIO_SWITCH_LISTEN	= 12; // switch to listening mode
 	LAYER_RADIO_SWITCH_SLEEP    = 13; // switch to sleep mode
 	
 	LAYER_RADIO_BEGIN_TRANSMIT  = 14; // begin transmitting
 	LAYER_RADIO_BEGIN_LISTEN    = 15; // begin listening
 	
 	LAYER_RADIO_END_TRANSMIT	= 16; // ending transmitting
 	LAYER_RADIO_END_LISTENING  	= 17; // ending listening
 	
 	LAYER_RADIO_CCA_NOT_VALID   = 18; // channel is not clear
	LAYER_RADIO_NOT_FREE	   	= 19; // radio is currently working
	LAYER_RADIO_PACKET_OVERSIZE = 20; // packet is too big
	LAYER_RADIO_SEND_OK			= 21; // send okay
	
	LAYER_RADIO_RECV_OK			= 22; // packet is okay
	LAYER_RADIO_RECV_CORRUPT	= 23; // packet is corrupt
	
	// rdc
	LAYER_RDC                	= 30; // kind
	
	LAYER_RDC_SEND				= 31; // sending a message
	LAYER_RDC_SEND_OK			= 32; // already sent a message
	LAYER_RDC_SEND_NOT_OK		= 33; // failed to send a message
	
	LAYER_RDC_WAIT_ACK			= 34; // waiting for an ACK
	
	LAYER_RDC_LISTEN_ON			= 35; // turn receiver on
	LAYER_RDC_LISTEN_OFF		= 36; // turn receiver off
	
	LAYER_RDC_RECV_OK			= 37; // receiving a okay message
	LAYER_RDC_RECV_ACK			= 38; // receiving an ACK
	
	// mac
	LAYER_MAC 		    = 50; // kind
	
	LAYER_MAC_SEND_OK	= 51; // transmitting + receiving ACK
	LAYER_MAC_NO_ACK  	= 52; // transmitting + no ACK
	
	LAYER_MAC_DEFER		= 53; // radio is busy
	LAYER_MAC_ERR		= 54; // internal error (???)

	LAYER_MAC_RECV_OK	= 55; // receiving an okay message

	// net
	LAYER_NET       	  = 70;	// kind
	
	LAYER_NET_CHECK_BUFFER = 71; // check message on buffer
	
	LAYER_NET_SEND_OK	   = 72; // successfully sent a message on buffer
	LAYER_NET_SEND_FAIL	   = 73; // failurely sent a message on buffer
	
	NET_ICMP_DIO    	  = 74;	// ICMP DIO message
	NET_ICMP_DIS    	  = 75;	// ICMP DIS message
	NET_ICMP_ACK    	  = 76;	// ICMP ACK message
	
	NET_DATA        	  = 77; // normal data message
	
	NET_ICMP_REQUEST_ACK  = 78; // ICMP sending ACK request
	
	// event
	LAYER_APP		 = 90; 			// kind
	
	APP_WORKING_FLAG = 91; // data from another node 
	APP_SENSING_FLAG = 92; // data from sensor
	APP_ENVIRON_FLAG = 93; // data from enviroment
}

packet Raw{
    int note; // control message 

    int radioSendId;
    int radioRecvId;
}

packet FrameRDC{
	int note;  // control message
}

packet FrameMAC{
    int note;  // control message

	int senderMacAddress; // sender MAC address
	int recverMacAddress; // recver MAC address

	int sequenceNumber;   // sequence number
}

packet IpPacket{
    int note; 	// control message
    
	int type;	// type message (DIO, DIS, Data)

    int senderIpAddress; // sender IP address
    int recverIpAddress; // recver IP address

    bool isRequestAck; // is request ACK ?
}

packet Data extends IpPacket{
	string value; // data to be sent to server
}

packet DIO  extends IpPacket{
	int dodagID; // DODAGID
	int version; // version
	unsigned long rank;   // rank 
	double secondCriteria; // energy-history
}

packet DIS  extends IpPacket{
	int convergence;
}

packet ACK extends IpPacket{
	double energy;
}