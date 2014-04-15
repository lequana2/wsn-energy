/*
 * hopEnergy.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#include <of/hopEnergy.h>

#ifndef ANNOTATE_DEFAULT_ROUTE
#define ANNOTATE_DEFAULT_ROUTE 1
#endif

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

void hopEnergy::updatePreferredParent(std::list<RPL_neighbor*> parentList, RPL_neighbor*& currentPreferredParent, int moteID)
{
  // delete old preferred parent (if needed)
  if (ANNOTATE_DEFAULT_ROUTE && currentPreferredParent != NULL)
  {
    char channelParent[20];
    sprintf(channelParent, "out %d to %d", moteID,
    simulation.getModule(currentPreferredParent->neighborID)->getParentModule()->getId());
    simulation.getModule(moteID)->gate(channelParent)->setDisplayString("ls=,0");
  }

  // Incase of update after purging route
  if (parentList.size() == 0)
  {
    currentPreferredParent = NULL;
    return;
  }

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

  currentPreferredParent = preferredParent;

  // draw new preferred parent (if exist)
  if (ANNOTATE_DEFAULT_ROUTE && currentPreferredParent != NULL)
  {
    char channelParent[20];
    sprintf(channelParent, "out %d to %d", moteID,
    simulation.getModule(currentPreferredParent->neighborID)->getParentModule()->getId());
    simulation.getModule(moteID)->gate(channelParent)->setDisplayString("ls=purple,1");
  }
}

} /* namespace wsn_energy */
