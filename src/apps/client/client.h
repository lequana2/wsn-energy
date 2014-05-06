/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Distributed client, collect data and forward to server
 */

#ifndef __WSN_ENERGY_SOURCE_H
#define __WSN_ENERGY_SOURCE_H

#include <myModule.h>

#ifndef UDP_PORT
#define UDP_PORT
#define UDP_SERVER_PORT 5678 // UDP port
#define UDP_CLIENT_PORT 8765 // UDP port
#endif

namespace wsn_energy {

class Client : public myModule
{
  private:
    int packetOrder;
    virtual void newData();

  protected:
    void initialize();

  public:
    void processSelfMessage(cPacket*);
    void processUpperLayerMessage(cPacket*);
    void processLowerLayerMessage(cPacket*);

    // Send message API using UDP/IP
    void sendMessage(char*,int,int,int);
};

}
;
// namespace

#endif
