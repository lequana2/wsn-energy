/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: multi-objective function hop/energy
 */

#ifndef HOPENERGY_H_
#define HOPENERGY_H_

#include "objectiveFunction.h"

namespace wsn_energy {

class hopEnergy : public ObjectiveFunction
{
  public:
    RPL_neighbor* bestParent(RPL_neighbor*, RPL_neighbor*);
    unsigned long calculateRank(RPL_neighbor*);
    RPL_neighbor* updatePreferredParent(std::list<RPL_neighbor*>);
};

} /* namespace wsn_energy */

#endif /* HOPENERGY_H_ */
