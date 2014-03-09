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

enum MESSAGE{
	// radio event
 	TRX_BROADCAST = 4;
 	RCX_BROADCAST = 3;
	TOF_BROADCAST = 2;
	ROF_BROADCAST = 1;
	
	// information event
	WORKING_FLAG = 5;
	ENVIRON_FLAG = 6;
	
	// specialize event
	RPL_CONSTRUCT = 7;
	RPL_SOLICIT   = 8;
}

enum IP_CODE {
	// IP
	IP_ICMP = 0;
	IP_DATA = 1;
}

enum RPL_CODE {
	// RPL
	ICMP_DIO_CODE = 0;
	ICMP_DIS_CODE = 1;
}

packet Raw{
    int radioSendId;
    int radioRecvId;
    int type;
}

packet IpPacket extends Raw{
    int sendID;
    int recvID;
    int type;
}

packet Data extends IpPacket {
	int value;
}

packet ICMP extends IpPacket{
    int icmp_code;
}

packet DIO extends ICMP{
	int dodagID;
	int rank;
	int version;
}

packet DIS extends ICMP{
	int flags;
	int reserved;
	int options; 
	int convergence;
}
