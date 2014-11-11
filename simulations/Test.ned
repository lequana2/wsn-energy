package wsn_energy.simulations;

import wsn_energy.mote.ClientMote;
import wsn_energy.mote.ServerMote;
import wsn_energy.util.world.World;
import wsn_energy.util.statistic.Statistic;

//
// Sample network, consisting of a source and a sink.
//
network Test
{
    parameters:
        int timeLimit;
        int setupDelay;

        int topology;

        bool usingFLR;
        bool usingELB;
        bool usingHDC;

        int width @unit(m);
        int height @unit(m);

        int numberClient;

        int serverX @unit(m);
        int serverY @unit(m);

        int scheme;
        int rand;

        int ssRange @unit(m);

        @display("bgs=6,m;bgb=$width,$height,#C6C6FF,#0000FF,2");

    submodules:
        test1: ServerMote {
            parameters:
                axisX = 10m;
                axisY = 10m;
        }
        test2: ClientMote {
            parameters:
                axisX = 10m;
                axisY = 50m;
        }
        test3: ClientMote {
            parameters:
                axisX = 10m;
                axisY = 10m;
        }
        test4: ClientMote {
            parameters:
                axisX = 10m;
                axisY = 50m;
        }
        world: World;
    connections allowunconnected:
}