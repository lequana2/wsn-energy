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

#ifndef NULLRADIO_H_
#define NULLRADIO_H_

#include "radio.h"

namespace wsn_energy {

class nullRadio : public RadioDriver
{
  private:
    virtual void transmit_on(Raw *raw);
    virtual void transmit_off();

  protected:
    virtual bool isClearChannel();

    virtual double getTxPower();
    virtual double getRxPower();
};

} /* namespace wsn_energy */

#endif /* NULLRADIO_H_ */
