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
  if (parent1->neighborRank < parent2->neighborRank)
    return parent1;

  if (parent1->neighborRank > parent2->neighborRank)
    return parent2;

  if (parent1->nodeQuality.energy > parent2->nodeQuality.energy)
    return parent1;

  if (parent1->nodeQuality.energy < parent2->nodeQuality.energy)
    return parent2;

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

  std::list<RPL_neighbor*>::iterator iterator = parentList.begin();
  RPL_neighbor *preferredParent = *iterator;

  for (; iterator != parentList.end(); iterator++)
  {
    // Better rank
    if ((*iterator)->neighborRank < preferredParent->neighborRank)
      preferredParent = *iterator;
    // Same rank but better energy
    else if ((*iterator)->neighborRank == preferredParent->neighborRank)
    {
      if ( simulation.getModuleByPath("WSN")->par("usingELB").boolValue()
          && check_and_cast<Count*>(
          simulation.getModule((*iterator)->neighborID)->getParentModule()->getSubmodule("count"))->residualEnergy
              < check_and_cast<Count*>(
              simulation.getModule(preferredParent->neighborID)->getParentModule()->getSubmodule("count"))->residualEnergy)
        preferredParent = *iterator;
    }
  }

  return preferredParent;
}

} /* namespace wsn_energy */
