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
    bool isHavingPendingPacket;

  public:
    RPL *rpl; // using RPL as routing protocol
    std::list<IpPacket*> buffer; // Buffer message to send, public scope for debugging

    void multicast(IpPacket*);      // broadcast
    void unicast(IpPacket*, int);   // unicast with destination IP address

  protected:
    virtual void initialize();

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);
};

}
;
// namespace

#endif /* NET_H_ */
