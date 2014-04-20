/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Managing position, signal
 */

#ifndef ENVIROMENT_H_
#define ENVIROMENT_H_

#include <omnetpp.h>
#include "mySignal.h"
#include "radio.h"
#include "packet_m.h"

#ifndef CONNECTION_STATUS
#define CONNECTION_STATUS
#define NO_CONNECTION 0 // out of range
#define WITHIN_TRANS  1 // within transmission range
#define WITHIN_COLLI  2 // within collision range
#endif

namespace wsn_energy {

// mote distance information, neccessary to calculate transmit/collision range
class MoteDistance
{
    int moteID; // the ID of destination mote
    double distance; // distance from self to the destination mode
};

// mote information, to manage signals
class Mote
{
  public:
    int moteID; // id of mote
    std::list<MoteDistance> moteNeighborDistance; // WSN distance with other motes

    Raw* onAir; // on air packet
    double transmitPower; // WSN transmitting power, need for calculating transmitting range
    std::list<int> moteIDWithinTransmissionRange; // WSN need to be replaced by
    std::list<int> moteIDWithinCollisionRange; // WSN need to be replaced by

    double receiveSensitivity; // WSN receiving sensitivity
    int incomingSignal; // WSN number of incoming signal
    bool resultCCA; // WSN result of CCA
};

class World : public cSimpleModule
{
  private:
    int numberClient; // total number of client
    std::ostringstream oss;     // string buffer

    void arrangeMotes(); // Arrange nodes in positions
    void connectNodes(); // Connect adjacent nodes

    void deployConnection(RadioDriver*);                // deploy all valid connection for a given radio
    int validateConnection(RadioDriver*, RadioDriver*); // check validation between 2 radio

    void considerSignal(mySignal*);     // register on-air signal

  protected:
    void initialize();
    void finish();

  public:
    std::list<Mote*> hosts;   // array of host list (Host)
    std::list<mySignal*> signals; // array of all on-air signal (mySignal)

    Mote& searchMote(int moteID); // WSN search mode on mote list given its ID

    void registerHost(RadioDriver*, Raw*);    // register transmitting mote
    void releaseHost(RadioDriver*);           // unregister transmitting mote

    void suddenBeginListening(RadioDriver*); // recver begin listening
    void suddenStopListening(RadioDriver*);   // recver stop listening

    void checkCCAResult(); // WSN check CCA result (???)
    bool isFreeChannel(RadioDriver*); // WSN check is free channel

    double calculateDistance(RadioDriver*, RadioDriver*);  // calculate distance between 2 motes
    double calculateDistance(int, int, int, int);        // calculate distance according to 2D coordinate
};

} /* namespace wsn_energy */

#endif /* ENVIROMENT_H_ */
