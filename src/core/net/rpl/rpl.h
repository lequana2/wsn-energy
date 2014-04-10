/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: RPL logic, trickler timer, DIO processing, next-hop decision
 */

#ifndef RPL_H_
#define RPL_H_

#include <list>
#include "packet_m.h"

#define RANK_INFINITY 0xffff

namespace wsn_energy {

/* forward declaration */
class IPv6;
class ObjectiveFunction;

class NodeQuality
{
  public:
    double hopCount;
    double energy;
};

class LinkQuality
{
  public:
    double etx;
};

class RPL_neighbor
{
  public:
    int neighborID;
    unsigned long neighborRank;

    NodeQuality nodeQuality;
    LinkQuality linkQuality;
};

class RPL_dag
{
  public:
    bool joined;
    int dodagID;
    int version;
    // Self rank
    unsigned long rank;

    // upward route
    RPL_neighbor *preferredParent;

    // neighbor information
    std::list<RPL_neighbor*> parentList;
    std::list<RPL_neighbor*> siblingList;

    // Objective Function
    ObjectiveFunction *of;
};

class RPL
{
  private:
    IPv6 *net;

    void processDIO(DIO*);
    void processDIS(DIS*);

  public:
    RPL_dag rplDag;

    RPL(IPv6 *net);

    void rpl_set_root();
    void rpl_init();

    void sendDIO();
    void sendDIS(int);

    void processICMP(IpPacket*);
};

} /* namespace wsn_energy */

#endif /* RPL_H_ */
