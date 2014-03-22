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

//#include <cc2420.h>

namespace wsn_energy {
class cc2420;
} /* namespace wsn_energy */

namespace wsn_energy {

class Transmission
{
  public:
    Transmission(cc2420 *sender, cc2420 *recver);

    virtual cc2420* getSender();
    virtual cc2420* getRecver();

    virtual bool isCollided();
    virtual void corrupted();

  private:
    cc2420 *sender;
    cc2420 *recver;
    bool collision;
};

} /* namespace wsn_energy */

#endif /* TRANMISSION_H_ */
