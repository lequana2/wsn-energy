//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

/*
 * This is simulation of the on the air tranmission
 * The sender and receiver is recorded
 * If the tranmission is spoiled, isCollided should return true;
 */
#ifndef TRANMISSION_H_
#define TRANMISSION_H_

#include "core.h"

namespace wsn_energy {

class Transmission
{
  public:
    Transmission(Core *sender, Core *recver);

    virtual Core* getSender();
    virtual Core* getRecver();

    virtual bool isCollided();
    virtual void collide();

  private:
    Core *sender;
    Core *recver;
    bool collision;
};

} /* namespace wsn_energy */

#endif /* TRANMISSION_H_ */
