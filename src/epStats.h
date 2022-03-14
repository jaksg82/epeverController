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

/* // statistics
  union {
    struct {
  
      // 4*1 = 4
      uint16_t  pVmax;
      uint16_t  pVmin;
      uint16_t  bVmax;
      uint16_t  bVmin;
  
      // 4*2 = 8
      uint32_t  consEnerDay;
      uint32_t  consEnerMon;
      uint32_t  consEnerYear;
      uint32_t  consEnerTotal;
  
      // 4*2 = 8
      uint32_t  genEnerDay;
      uint32_t  genEnerMon;
      uint32_t  genEnerYear;
      uint32_t  genEnerTotal;
  
      // 1*2 = 2
      uint32_t  c02Reduction;
     
    } s;
    uint16_t  buf[22];  
  } stats;
 */

#ifndef EPSTATS_H
#define EPSTATS_H

#include <stdio.h>
#include <stdint.h>

#include "epConverters.h"

class epStats {
  private:
  uint16_t pVmax, pVmin, bVmax, bVmin;
  uint32_t consEnerDay, consEnerMon, consEnerYear, consEnerTotal;
  uint32_t genEnerDay, genEnerMon, genEnerYear, genEnerTotal;
  uint32_t c02Reduction, batteryCurrent;
  
  static const uint8_t statsStringSize = 140;
  //static char statsStr[statsStringSize];

  public:

  // ----------------------------------------------------------------------------
  // Constructors
  // ----------------------------------------------------------------------------
  epStats();
  epStats(uint16_t buf[29]);

  // ----------------------------------------------------------------------------
  // Get the csv strings
  // ----------------------------------------------------------------------------
  uint8_t getStatsStrSize() { return statsStringSize; }
  //void getVoltsStr(char* retStr[], uint8_t* retSize);
  //void getConsumedStr(char* retStr[], uint8_t* retSize);
  //void getGeneratedStr(char* retStr[], uint8_t* retSize);
  char* getStatsStr();

}; // class

#endif