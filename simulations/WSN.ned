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

import wsn_energy.mote.ClientMote;
import wsn_energy.mote.ServerMote;
import wsn_energy.util.world.World;
import wsn_energy.util.statistic.Statistic;

//
// Sample network, consisting of a source and a sink.
//
network WSN
{
    parameters:
        int topology;
        
        int numberClient;

        int trRange @unit(m);
        int coRange @unit(m);
        int ssRange @unit(m);

        int width   @unit(m);
        int height  @unit(m);

        double redundancy;
        double energy;

        int isPolling;
        double polling;

        @display("bgs=6,m;bgb=$width,$height,#C6C6FF,#0000FF,2");

    submodules:
        server: ServerMote {
            parameters:
                trRange = trRange;
                coRange = coRange;
//                axisX = width  / 2;
//                axisY = height / 2;
				axisX = 0;
				axisY = 0;
        }
        client[numberClient]: ClientMote {
            parameters:
                trRange = trRange;
                coRange = coRange;
                axisX = 0;
                axisY = 0;
        }
        world: World {
            parameters:
                numberClient = numberClient;
        }
        statistic: Statistic;
    connections allowunconnected:
}
