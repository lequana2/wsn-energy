/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to hopEnergy.h
 */

#include <of/hopEnergy.h>
#include "count.h"

namespace wsn_energy {

RPL_neighbor* hopEnergy::bestParent(RPL_neighbor* parent1, RPL_neighbor* parent2)
{
  if (parent1 == NULL)
    return parent2;
  else if (parent2 == NULL)
    return parent1;

  if (parent1->neighborRank < parent2->neighborRank)
    return parent1;
  else if (parent1->neighborRank > parent2->neighborRank)
    return parent2;

  // WSN hack
  if (simulation.getModuleByPath("WSN")->par("usingELB").boolValue())
  {
    if (check_and_cast<Count*>(simulation.getModule(parent1->neighborID)->getParentModule()->getSubmodule("count"))->residualEnergy
        < check_and_cast<Count*>(simulation.getModule(parent2->neighborID)->getParentModule()->getSubmodule("count"))->residualEnergy)
      return parent1;
    else
      return parent2;
  }

//  if (parent1->nodeQuality.energy > parent2->nodeQuality.energy)
//    return parent1;
//  if (parent1->nodeQuality.energy < parent2->nodeQuality.energy)
//    return parent2;

  return parent1;
}

unsigned long hopEnergy::calculateRank(RPL_neighbor* parent)
{
  return parent->neighborRank + 1;
}

RPL_neighbor* hopEnergy::updatePreferredParent(std::list<RPL_neighbor*> parentList)
{
  // Incase of update after purging route
  if (parentList.size() == 0)
    return NULL;

  RPL_neighbor *preferredParent = NULL;

  for (std::list<RPL_neighbor*>::iterator it = parentList.begin(); it != parentList.end(); it++)
    preferredParent = bestParent(preferredParent, *it);

  return preferredParent;
}

} /* namespace wsn_energy */
