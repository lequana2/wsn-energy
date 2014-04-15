/*
 * hopEnergy.h
 *
 *  Created on: Mar 31, 2014
 *      Author: quan
 *  
 *  Functioning:
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
    void updatePreferredParent(std::list<RPL_neighbor*>, RPL_neighbor*&, int);
};

} /* namespace wsn_energy */

#endif /* HOPENERGY_H_ */
