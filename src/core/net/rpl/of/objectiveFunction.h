/*
 * ObjectiveFunction.h
 *
 *  Created on: Mar 31, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#ifndef OBJECTIVEFUNCTION_H_
#define OBJECTIVEFUNCTION_H_

#include "rpl.h"

namespace wsn_energy {

class ObjectiveFunction
{
  public:
    virtual RPL_neighbor* bestParent(RPL_neighbor*, RPL_neighbor*) = 0;
    virtual double calculateRank(RPL_neighbor*) = 0;
    virtual RPL_neighbor* updatePreferredParent(std::list<RPL_neighbor*>) = 0;
};

} /* namespace wsn_energy */

#endif /* OBJECTIVEFUNCTION_H_ */
