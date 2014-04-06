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

class Host
{
  public:
    int moteID;
    Raw* onAir;
    std::list<int> moteIDWithinTransmissionRange;
    std::list<int> moteIDWithinCollisionRange;
};

class World : public cSimpleModule
{
  private:
    int numberClient;

    void arrangeMotes(); // Arrange nodes in positions
    void connectNodes(); // Connect adjacent nodes

    void deployConnection(RadioDriver*);                // deploy all valid connection for a given radio
    int validateConnection(RadioDriver*, RadioDriver*); // check validation between 2 radio

    void considerSignal(mySignal*);     // register on-air signal

  protected:
    void initialize();
    void handleMessage(cMessage *msg);
    void finish();

  public:
    std::ostringstream oss;     // string buffer
    std::list<Host*> hosts;   // array of host list (Host)
    std::list<mySignal*> signals; // array of on-air signal (mySignal)

    void registerHost(RadioDriver*, Raw*);    // register transmitting mote
    void releaseHost(RadioDriver*);           // unregister transmitting mote
    void stopListening(RadioDriver*);  // recver mote stop listening

    double calculateDistance(RadioDriver*, RadioDriver*);  // calculate distance between 2 motes
    double calculateDistance(int, int, int, int);        // calculate distance according to 2D coordinate
};

} /* namespace wsn_energy */

#endif /* ENVIROMENT_H_ */
