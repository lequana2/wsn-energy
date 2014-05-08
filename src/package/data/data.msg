//
//  created on : Mar 5, 2014
//      author : Mr.Quan LE
//      email  : lequana2@gmail.com
//
//  functioning: APP layer message
//

namespace wsn_energy;

// Data
packet Data{
    double time;  		// meta-data: timestamp upon sending
    
    int destinationPort; 	  // control-data: destination port
    int destinationIPAddress; // control-data: destination IP Address
    
	string value; 		// undefined length, data to be sent to server
}