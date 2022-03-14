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

// live data
//  union {
//    struct {
//      int16_t  pV;
//      int16_t  pI;
//      int32_t  pP;
//      int16_t  bV;
//      int16_t  bI;
//      int32_t  bP;
//      uint16_t  dummy[4];
//      int16_t  lV;
//      int16_t  lI;
//      int32_t  lP;
//    } l;
//    uint16_t  buf[16];
//  } live;
#ifndef EPLIVE_H
#define EPLIVE_H

#include <stdio.h>
#include <stdint.h>

#include "epConverters.h"

class epLive {
  private:
  int16_t pV, pI, bV, bI, lV, lI;  // Volts & Amperes to be scaled
  int32_t pP, bP, lP;              // Watts to be scaled
  uint16_t batSoc;                 // Percentage of battery capacity
  static const uint8_t liveStringSize = 68;

  public:
  // Constructors
  epLive();
  epLive(uint16_t buf[27]);
  
  // Expose Live values
  float BatteryVolts() { return bV / 100.0f; }
  float BatteryAmperes() { return bI / 100.0f; }
  float BatteryWatts() { return bP / 100.0f; }
  float PanelVolts() { return pV / 100.0f; }
  float PanelAmperes() { return pI / 100.0f; }
  float PanelWatts() { return pP / 100.0f; }
  float LoadVolts() { return lV / 100.0f; }
  float LoadAmperes() { return lI / 100.0f; }
  float LoadWatts() { return lP / 100.0f; }
  uint16_t BatterySOC() { return batSoc; }

  // Get the csv strings
  uint8_t getLiveStrSize() { return liveStringSize; }
  char* getLiveStr();

};


#endif