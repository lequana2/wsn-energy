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

package wsn_energy.mote;

import wsn_energy.apps.iApp;
import wsn_energy.core.net.iNet;
import wsn_energy.core.mac.iMAC;
import wsn_energy.core.rdc.iRDC;
import wsn_energy.platform.radio.iRadio;
import wsn_energy.platform.battery.Battery;

//
// TODO auto-generated type
//
module ServerMote
{
    parameters:
        string appType;
        string netType;
        string macType;
        string rdcType;
        string radioType;
        
        int axisX;
        int axisY;
        int trRange;
        int coRange;
        @display("i=abstract/db;is=s;p=$axisX,$axisY");

    submodules:
        app: <appType> like iApp;
        net: <netType> like iNet;
        mac: <macType> like iMAC;
        rdc: <rdcType> like iRDC;
        radio: <radioType> like iRadio {
            parameters:
                trRange = trRange;
                coRange = coRange;
        }
        battery: Battery;
        
    connections allowunconnected:
        app.lowerOut --> net.upperIn;
        app.lowerIn <-- net.upperOut;

        net.lowerOut --> mac.upperIn;
        net.lowerIn <-- mac.upperOut;

        mac.lowerOut --> rdc.upperIn;
        mac.lowerIn <-- rdc.upperOut;

        rdc.lowerOut --> radio.upperIn;
        rdc.lowerIn <-- radio.upperOut;
}
