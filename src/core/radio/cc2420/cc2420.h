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

#ifndef CC2420_H_
#define CC2420_H_

#include "radio.h"

/*
 * Specification for CC2420
 */
#define FREQUENCY          2400.0  // MHz
#define TXPOWER_LEVEL_MAX    31.0  // level max
#define TXPOWER_LEVEL_MIN     0.0  // level min
#define TXPOWER_MAX           0.0  // dBm
#define TXPOWER_MIN         -90.0  // dBm
#define TXPOWER_CURRENT_MAX  17.4  // mA
#define RXPOWER_CURRENT      18.8  // mA
#define IDPOWER_CURRENT       1.8  // mA
#define SUPPLY_VOLTAGE        1.8  // V
#define SLPOWER

namespace wsn_energy {

class cc2420 : public RadioDriver
{
  public:
    virtual void performCCA();

    virtual double getTxPower();
    virtual double getRxPower();
    virtual double getIdPower();
};

} /* namespace wsn_energy */

#endif /* CC2420_H_ */
