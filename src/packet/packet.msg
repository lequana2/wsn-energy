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
	LAYER_RADIO   = 10; // kind
 	TRX_BROADCAST = 11; // from upper
 	RCX_BROADCAST = 12;
	TOF_BROADCAST = 13;
	ROF_BROADCAST = 14;
	TX_OK         = 15; // to upper
	TX_ERR		  = 16; 
	TX_COLLISION  = 17;
	TX_NOACK      = 18;

	// rdc
	LAYER_RDC     = 21; // kind
	
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
    int type;
    int len;
    bool bitError;
    int radioSendId;
    int radioRecvId;
}

packet Frame extends Raw{
	int type;
	int senderMacAddress;
	int recverMacAddress;
}

packet IpPacket extends Frame{
    int type;
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