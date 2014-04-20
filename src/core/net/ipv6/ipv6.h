/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: network layer, IPv6
 */

#ifndef NET_H_
#define NET_H_

#include <myModule.h>
#include "rpl.h"

namespace wsn_energy {

class IPv6 : public myModule
{
  private:
    IpPacket *pendingPacket;
    void preparePacketToBeSent();

  protected:
    void initialize();
    void finish();

    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

  public:
    std::list<IpPacket*> ipPacketQueue; // Buffer message to send, public scope for debugging

    RPL *rpl; // using RPL as routing protocol

    void multicast(IpPacket*); // multicast to all neighbor
    void unicast(IpPacket*);   // unicast with default route
};

}
;
// namespace

#endif /* NET_H_ */
