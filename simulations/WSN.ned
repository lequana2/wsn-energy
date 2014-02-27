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

package wsn_energy.simulations;

import wsn_energy.server.Server;
import wsn_energy.client.Client;
import wsn_energy.core.Core;

//
// Sample network, consisting of a source and a sink.
//
network WSN
{
    parameters:
        int numberClient;
        int trRange;
        int ssRange;
        int width;
        int height;
        double redundancy;
        double energy;
        @display("bgb=1000,500,#C6C6FF,#0000FF,2");
    submodules:
        server: Server {
            parameters:
                numberClient = numberClient;
                trRange = trRange;
                ssRange = ssRange;
                energy = energy;
                redundancy = redundancy;
                axisX = width / 2;
                axisY = height / 2;
                @display("p=$axisX,$axisY");
        }
        client[numberClient]: Client {
            parameters:
                numberClient = numberClient;
                trRange = trRange;
                ssRange = ssRange;
                energy = energy;
                redundancy = redundancy;
//                axisX = intuniform(0, width);
//                axisY = intuniform(0, height);
				axisX = width / 4;
				axisY = height / 4;
                @display("p=$axisX,$axisY");
        }
    connections allowunconnected:
}
