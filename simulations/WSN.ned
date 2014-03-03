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

import wsn_energy.apps.server.Server;
import wsn_energy.apps.client.Client;
import wsn_energy.world.Enviroment;

//
// Sample network, consisting of a source and a sink.
//
network WSN
{
    parameters:
        int numberClient;
        int trRange;
        int coRange;
        int width;
        int height;
        double redundancy;
        double energy;
        @display("bgb=1000,1000,#C6C6FF,#0000FF,2");
    submodules:
        server: Server {
            parameters:
                numberClient = numberClient;
                trRange = trRange;
                coRange = coRange;
                energy = energy;
                redundancy = redundancy;
                axisX = width / 2;
                axisY = 0;
                @display("p=$axisX,$axisY");
        }
        client[numberClient]: Client {
            parameters:
                numberClient = numberClient;
                trRange = trRange;
                coRange = coRange;
                energy = energy;
                redundancy = redundancy;
                axisX = 0;
                axisY = 0;
        }
        enviroment: Enviroment {
            parameters:
                @display("p=-10,-10");
        }
    connections allowunconnected:
}
