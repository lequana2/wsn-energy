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
	// PHY
	PHY_HEADER     =  6;    // PHY 802.15.4 header 6 bytes
	
	// MAC
	PACKET_802154  =  127;  // MAC 802.15.4 payload 127 bytes
	ACK_LEN		   =  5;	// MAC 802.15.4 ACK 5 bytes (header + footer)
	
	// NET
	
	// APP
}

enum MESSAGE
{
	// specialize event
	NODE_STARTUP  = 0;
	NODE_DESTRUCT = 1;
	OUT_OF_ENERGY = 2;
	RPL_CONSTRUCT = 3;
	RPL_SOLICIT   = 4;

	// radio
 	LAYER_RADIO     			= 10; // kind
 	LAYER_RADIO_SWITCH_TRANSMIT	= 11; // switch to transmit mode
 	LAYER_RADIO_SWITCH_LISTEN	= 12; // switch to listening mode
 	LAYER_RADIO_SWITCH_SLEEP    = 13; // switch to sleep mode
 	LAYER_RADIO_BEGIN_TRANSMIT  = 14; // begin transmitting
 	LAYER_RADIO_BEGIN_LISTEN    = 15; // begin listening
 	LAYER_RADIO_END_TRANSMIT	= 16; // ending transmitting
 	LAYER_RADIO_END_RECEIVING  	= 17; // ending receiving
 	LAYER_RADIO_CCA_NOT_VALID   = 18; // channel is not clear
 	LAYER_RADIO_RECV_OK			= 19; // packet is okay
	LAYER_RADIO_RECV_CORRUPT	= 20; // packet is corrupt
	LAYER_RADIO_NOT_FREE	   	= 21; // radio is currently working
	
	// rdc
	LAYER_RDC                	= 30; // kind
	LAYER_RDC_SEND				= 31; // sending a message
	LAYER_RDC_LISTEN_ON			= 32; // turn receiver on
	LAYER_RDC_LISTEN_OFF		= 33; // turn receiver off
	LAYER_RDC_WAIT_ACK			= 34; // waiting for an ACK
	
	// mac
	LAYER_MAC 		    = 50; // kind
	LAYER_MAC_SEND_OK	= 51; // transmitting + receiving ACK
	LAYER_MAC_NO_ACK  	= 52; // transmitting + no ACK
	LAYER_MAC_DEFER		= 53; // radio is busy
	LAYER_MAC_ERR		= 54; // internal error (???)

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