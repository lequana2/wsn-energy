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
    bool isWaiting;

  public:
    // RPL
    RPL *rpl;

    // Buffer message to send
    std::list<IpPacket*> buffer;

    void multicast(IpPacket*);
    void unicast(IpPacket*, int);

  protected:
    virtual void initialize();
    virtual void finish();

    virtual void processSelfMessage(cPacket*);
    virtual void processUpperLayerMessage(cPacket*);
    virtual void processLowerLayerMessage(cPacket*);
};

}
;
// namespace

#endif /* NET_H_ */
