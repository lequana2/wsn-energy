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

namespace wsn_energy;

enum PACKET_SIZE{
	PHY_HEADER     =  6;    // PHY 802.15.4 header 6 bytes
	
	PACKET_802154  =  127;  // MAC 802.15.4 payload 127 bytes
	ACK_LEN		   =  5;	// MAC 802.15.4 ACK 5 bytes (header + footer)
	MAC_LEN		   =  25;   // MAC 802.15.4 ACK 25 bytes (address long)
	
	DIO_LEN		   =  24; 	// ICMPv6 RPL DODAG INFORMATION OBJECT
	DIS_LEN		   =  10;   // ICMPv6 RPL DODAG INFORMATION SOLICITATION
	
	DATA		   = 1; 	// 1 bytes ????
}

enum MESSAGE
{
	// specialize event
	NODE_STARTUP  = 0; // turn on a mote
	NODE_DESTRUCT = 1; // turn off a mote (or) note runs out of energy
	OUT_OF_ENERGY = 2; // out of energy flag
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
	
	LAYER_RADIO_RECV_OK			= 21; // packet is okay
	LAYER_RADIO_RECV_CORRUPT	= 22; // packet is corrupt
	
	// rdc
	LAYER_RDC                	= 30; // kind
	
	LAYER_RDC_SEND				= 31; // sending a message
	
	LAYER_RDC_WAIT_ACK			= 32; // waiting for an ACK
	
	LAYER_RDC_LISTEN_ON			= 33; // turn receiver on
	LAYER_RDC_LISTEN_OFF		= 34; // turn receiver off
	
	LAYER_RDC_RECV_OK			= 35; // receiving a okay message
	LAYER_RDC_RECV_ACK			= 36; // receiving an ACK
	
	// mac
	LAYER_MAC 		    = 50; // kind
	
	LAYER_MAC_SEND_OK	= 51; // transmitting + receiving ACK
	LAYER_MAC_NO_ACK  	= 52; // transmitting + no ACK
	
	LAYER_MAC_DEFER		= 53; // radio is busy
	LAYER_MAC_ERR		= 54; // internal error (???)

	LAYER_MAC_RECV_OK	= 55; // receiving an okay message

	// net
	LAYER_NET     = 70; // kind
	NET_ICMP_DIO  = 71; // ICMP DIO message
	NET_ICMP_DIS  = 72; // ICMP DIS message
	NET_DATA      = 73; // normal data message
	
	// event
	LAYER_APP		 = 90; // kind
	APP_WORKING_FLAG = 91; // data from another node 
	APP_SENSING_FLAG = 92; // data from sensor
	APP_ENVIRON_FLAG = 93; // data from enviroment
}

packet Raw{
    int typeRadioLayer;
    int len = 0;
    bool bitError;
    int radioSendId;
    int radioRecvId;
}

packet Frame extends Raw{
	int typeMacLayer;
	int senderMacAddress;
	int recverMacAddress;
	int sequenceNumber;
}

packet IpPacket extends Frame{
    int typeNetLayer;
    int senderIpAddress;
    int recverIpAddress;
}

packet Data extends IpPacket {
	int value;
}

packet DIO extends IpPacket {
	int dodagID;
	unsigned long rank;
	int version;
}

packet DIS extends IpPacket {
	int convergence;
}