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

package wsn_energy.util.statistic;

//
// Statistics Collector
//
simple Statistic
{
    parameters:
        double pollTSEInterval = default(0.5);

        @signal[total_sensor_energy](type="double");
        @statistic[totalEnergy](title="Total energy"; source="total_sensor_energy"; record=vector);

        @signal[recv_packet](type="int");
        @statistic[numRecvPacket](title="Number of received packets"; source="recv_packet"; record=last);

        @signal[lost_packet](type="int");
        @statistic[numLostPacket](title="Number of lost packets"; source="lost_packet"; record=last);

        @signal[sens_data](type="int");
        @statistic[sensData](title="Number of sens data"; source="sens_data"; record=last);

        @signal[recv_data](type="int");
        @statistic[recvData](title="Number of received data"; source="recv_data"; record=last);

        @display("p=-50,80;i=block/table2");
}
