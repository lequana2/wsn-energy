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

enum COMMAND_AND_RESULT{
	// enviroment event
	NODE_STARTUP  = 0; // turn on a mote
	
	// hardware event
	OUT_OF_ENERGY = 1; // out of energy flag
	NODE_DESTRUCT = 2; // turn off a mote (or) note runs out of energy
	
	// logical event
	RPL_CONSTRUCT = 3; // perform broadcasting DIO
	RPL_SOLICIT   = 4; // request DIS

	// radio control strobe (self)
	LAYER_RADIO_BEGIN_CCA       = 10; // radio begin CCA
	LAYER_RADIO_END_CCA         = 11; // radio end CCA
	
	// switch mode
 	LAYER_RADIO_SWITCH_TRANSMIT	= 12; // switch to transmit mode
 	LAYER_RADIO_SWITCH_LISTEN	= 13; // switch to listening mode
 	LAYER_RADIO_SWITCH_IDLE     = 14; // switch to sleep mode
 	
 	// in mode
 	LAYER_RADIO_BEGIN_TRANSMIT  = 15; // begin transmitting
	LAYER_RADIO_END_TRANSMIT	= 16; // ending transmitting

	// in mode
 	LAYER_RADIO_LISTENING    = 17; // begin listening
 	LAYER_RADIO_IDLING  	 = 18; // ending listening
 	
 	// radio transmitting result (to rdc)
	LAYER_RADIO_SEND_OK			    = 19; // send okay
	LAYER_RADIO_PACKET_OVERSIZE     = 21; // packet is too big

	// radio receiving result (to rdc)
	LAYER_RADIO_RECV_OK			= 22; // packet is okay
	LAYER_RADIO_RECV_NOT_OK		= 23; // packet is either corrupt or incomplete

	// rdc command (to radio)
	LAYER_RDC_SEND				= 30; // sending a message
	
	// feedback from radio
	LAYER_RDC_SEND_OK			= 31; // already sent a message
	LAYER_RDC_SEND_ERR   		= 32; // failed to send a message

	// rdc transmitting result (to radio)
	LAYER_RDC_LISTEN_ON			= 33; // turn receiver on
	LAYER_RDC_LISTEN_OFF		= 34; // turn receiver off
	
	// rdc receiving result (to mac)
	LAYER_RDC_RECV_OK			= 35; // receiving a okay message
	LAYER_RDC_RECV_ACK			= 36; // receiving an ACK

	// mac control (self)
	LAYER_MAC_DEFER		= 50; // radio is busy
	
	// mac transmitting result (to net)
	LAYER_MAC_SEND_OK	= 51; // transmitting + receiving ACK
	LAYER_MAC_SEND_ERR	= 52; // internal error
	LAYER_MAC_NO_ACK  	= 53; // transmitting + no ACK

	// mac receiving result (to net)
	LAYER_MAC_RECV_OK	  = 54; // receiving an okay message
	LAYER_MAC_RECV_NOT_OK = 55; // receiving a corrupted message

	// mac control (to RDC)
	LAYER_MAC_SEND        = 56; // send a message

	// net self control (self)
	LAYER_NET_CHECK_BUFFER = 70; // check message on buffer
	
	// net transmitting result (self)
	LAYER_NET_SEND_OK	   = 71; // successfully sent a message on buffer
	LAYER_NET_SEND_NOT_OK  = 72; // failurely sent a message on buffer
	
	// net receiving result (self)
	LAYER_NET_RECV_OK	   = 73; // incoming message
	
	// app control message (self)
	APP_WORKING_FLAG = 90; // data from another node 
	APP_SENSING_FLAG = 91; // data from sensor
	APP_ENVIRON_FLAG = 92; // data from enviroment
	
	// CCA message
	CHANNEL_CCA_REQUEST = 100;
	CHANNEL_CLEAR   	= 101;
	CHANNEL_BUSY    	= 102;
	
	// command or data
	COMMAND             = 115;
	DATA				= 114;
}

enum IP_PACKET_TYPE
{
    // net packet type
	NET_ICMP_DIO    	  = 0;	// ICMP DIO message
	NET_ICMP_DIS    	  = 1;	// ICMP DIS message
	NET_ICMP_ACK    	  = 2;	// ICMP ACK message
	NET_DATA        	  = 3; // normal data message
};

packet Command{
	int note;
}

packet Raw{
	bool error; // is error message
    
    int note;   // control message 

    int radioSendId; 
    int radioRecvId;
}

packet FrameRDC{
	int note;  // control message
}

packet FrameMAC{
    int numberTransmission = 0; // meta-data: number transmission
    	
    int note;  // control message

	int senderMacAddress; // sender MAC address
	int recverMacAddress; // recver MAC address

	int sequenceNumber;   // sequence number
}

packet IpPacket{
    int note; 	// control message
    
	int type;	// type message (DIO, DIS, Data)

	bool isBroadcast;

    int senderIpAddress; // sender IP address
    int recverIpAddress; // recver IP address
}

packet DIO  extends IpPacket{
	int dodagID; // DODAGID
	int version; // version
	
	unsigned long rank;   // rank 
	
	double selfEnergy; // energy-history
}

packet DIS  extends IpPacket{
	int convergence;
}

packet UdpPacket{
    int note; 	// control message
    
    int sourceIpAddress; // sensor node IP address
	int sinkIpAddress;   // base station IP address
}

packet Data{
    int note; 	// control message
     
    double time;  // meta-data: timestamp upon sending
	string value; // data to be sent to server
}