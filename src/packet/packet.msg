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

enum MESSAGE
{
	// specialize event
	NODE_STARTUP  = 0;
	NODE_DESTRUCT = 1;
	OUT_OF_ENERGY = 2;
	RPL_CONSTRUCT = 3;
	RPL_SOLICIT   = 4;

	// radio
 	LAYER_RADIO     		= 10; // kind
 	LAYER_RADIO_END_TRANS	= 11;
 	LAYER_RADIO_END_RECV    = 12;
	LAYER_RADIO_OK			= 13;
	LAYER_RADIO_COL 		= 14;

	// rdc
	LAYER_RDC        = 20; // kind
	
	// mac
	LAYER_MAC     = 31; // kind

	// net
	LAYER_NET     = 32; // kind
	NET_ICMP_DIO  = 40;
	NET_ICMP_DIS  = 41;
	NET_DATA      = 42;
	
	// event
	LAYER_APP		 = 50; // kind
	APP_WORKING_FLAG = 51; 
	APP_ENVIRON_FLAG = 52;
	APP_SENSING_FLAG = 53;
}

packet Raw{
    int typeRadioLayer;
    int len;
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