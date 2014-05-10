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

#ifndef CONTIKIMAC_H_
#define CONTIKIMAC_H_

#include "rdc.h"
#include "packet_m.h"

namespace wsn_energy {

class contikiMAC : public RDCdriver
{
  protected:
    virtual void sendPacket(Frame*);

    virtual void sendSuccess(Frame*);
    virtual void sendFailure();

    virtual void receiveSuccess(Frame*);
    virtual void receiveFailure();
};

} /* namespace wsn_energy */

#endif /* RDC_H_ */
