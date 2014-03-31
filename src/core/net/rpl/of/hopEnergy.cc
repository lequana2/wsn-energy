/*
 * hopEnergy.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#include <of/hopEnergy.h>

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
    else if ((*iterator)->neighborRank == preferredParent->neighborRank
        && (*iterator)->nodeQuality.energy > preferredParent->nodeQuality.energy)
      preferredParent = *iterator;
  }

  return preferredParent;
}

} /* namespace wsn_energy */
