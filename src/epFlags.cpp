/*
  This file is part of the epeverController library.
  Copyright (c) 2022 Simone Giacomoni All rights reserved.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

#include "epFlags.h"

// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
epFlags::epFlags() {
  voltMode = 0;
  tempMode = 0;
  resistance = 0;
  ratedVolt = 0;
  chargerMode = 0;
}

epFlags::epFlags(uint16_t buf[2]) {
  voltMode = buf[0] & 0b1111;
  tempMode = (buf[0]  >> 4 ) & 0b1111;
  resistance = (buf[0]  >>  8 ) & 0b1;
  ratedVolt = (buf[0]  >> 15 ) & 0b1;
  chargerMode = (buf[1] & 0b0000000000001100) >> 2;
}

epFlags::epFlags(uint16_t hr0, uint16_t hr1) {
  voltMode = hr0 & 0b1111;
  tempMode = (hr0  >> 4 ) & 0b1111;
  resistance = (hr0  >>  8 ) & 0b1;
  ratedVolt = (hr0  >> 15 ) & 0b1;
  chargerMode = (hr1 & 0b0000000000001100) >> 2;
}

void epFlags::getFlagsStr(char* retStr[], uint8_t* retSize) {
  *retSize = (uint8_t)44;
  char ret[44];
  sprintf(ret, "%2x,%s,%2x,%s,%3d,%3d,%2x,%s", voltMode, voltStatus[voltMode], tempMode, tempStatus[tempMode], resistance, ratedVolt, chargerMode, chargingStatus[chargerMode]);
  *retStr = ret;
}