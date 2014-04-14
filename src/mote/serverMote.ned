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
import wsn_energy.core.transport.iTransport;
import wsn_energy.core.net.iNet;
import wsn_energy.core.mac.iMAC;
import wsn_energy.core.rdc.iRDC;
import wsn_energy.core.radio.iRadio;
import wsn_energy.core.energest.Energest;
import wsn_energy.core.bytecount.Count;

//
// TODO auto-generated type
//
module ServerMote
{
    parameters:
        string appType;
        string traType;
        string netType;
        string macType;
        string rdcType;
        string radioType;

        int axisX @unit(m);
        int axisY @unit(m);
        int trRange @unit(m);
        int coRange @unit(m);

        @display("p=$axisX,$axisY;i=abstract/db;is=m");

    submodules:
        app: <appType> like iApp;
        tra: <traType> like iTransport;
        net: <netType> like iNet;
        mac: <macType> like iMAC;
        rdc: <rdcType> like iRDC;
        radio: <radioType> like iRadio {
            parameters:
                trRange = trRange;
                coRange = coRange;
        }
        energest: Energest;
        count: Count;
    connections allowunconnected:
        app.lowerOut --> tra.upperIn;
        app.lowerIn <-- tra.upperOut;

        tra.lowerOut --> net.upperIn;
        tra.lowerIn <-- net.upperOut;

        net.lowerOut --> mac.upperIn;
        net.lowerIn <-- mac.upperOut;

        mac.lowerOut --> rdc.upperIn;
        mac.lowerIn <-- rdc.upperOut;

        rdc.lowerOut --> radio.upperIn;
        rdc.lowerIn <-- radio.upperOut;
}
