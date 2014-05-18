/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to hopEnergy.h
 */

#include <of/hopEnergy.h>
#include "count.h"
#include "energest.h"

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

  return parent1;
}

unsigned long hopEnergy::calculateRank(RPL_neighbor* parent)
{
  if (simulation.getModuleByPath("WSN")->par("usingELB").boolValue())
  {
    double percentRemaining = check_and_cast<Energest*>(
    simulation.getModule(parent->neighborID))->residualEnergy / MAX_POWER;

    // hop increment = 256
    // energy level  = 256
    return parent->neighborRank + 256 + percentRemaining * 256;
  }
  else
  {
    return parent->neighborRank + 1;
  }
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
