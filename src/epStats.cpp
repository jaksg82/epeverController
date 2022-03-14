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

#include "epStats.h"

// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------

epStats::epStats() {
  pVmax = 0;
  pVmin = 0;
  bVmax = 0;
  bVmin = 0;
  consEnerDay = 0;
  consEnerMon = 0;
  consEnerYear = 0;
  consEnerTotal = 0;
  genEnerDay = 0;
  genEnerMon = 0;
  genEnerYear = 0;
  genEnerTotal = 0;
  c02Reduction = 0;
}

epStats::epStats(uint16_t buf[29]) {
  pVmax = buf[0];
  pVmin = buf[1];
  bVmax = buf[2];
  bVmin = buf[3];
  consEnerDay = epConverters::combine16to32(buf[4], buf[5]);
  consEnerMon = epConverters::combine16to32(buf[6], buf[7]);
  consEnerYear = epConverters::combine16to32(buf[8], buf[9]);
  consEnerTotal = epConverters::combine16to32(buf[10], buf[11]);
  genEnerDay = epConverters::combine16to32(buf[12], buf[13]);
  genEnerMon = epConverters::combine16to32(buf[14], buf[15]);
  genEnerYear = epConverters::combine16to32(buf[16], buf[17]);
  genEnerTotal = epConverters::combine16to32(buf[18], buf[19]);
  c02Reduction = epConverters::combine16to32(buf[20], buf[21]);
  batteryCurrent = epConverters::combine16to32(buf[27], buf[28]);
}

// ----------------------------------------------------------------------------
// Get the csv strings
// ----------------------------------------------------------------------------

char* epStats::getStatsStr() {
  static char ret[statsStringSize];
  float pVmins = pVmin / 100.0f;
  float pVmaxs = pVmax / 100.0f;
  float bVmins = bVmin / 100.0f;
  float bVmaxs = bVmax / 100.0f;
  float ced = consEnerDay / 100.0f;
  float cem = consEnerMon / 100.0f;
  float cey = consEnerYear / 100.0f;
  float cet = consEnerTotal / 100.0f;
  float ged = genEnerDay / 100.0f;
  float gem = genEnerMon / 100.0f;
  float gey = genEnerYear / 100.0f;
  float get = genEnerTotal / 100.0f;
  float co2s = c02Reduction / 100.0f;
  float batCs = batteryCurrent / 100.0f;
  sprintf(ret, "%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%7.2f,%7.2f,%8.2f,%8.2f,%7.2f,%7.2f,%8.2f,%8.2f,%7.2f", batCs, pVmins, pVmaxs, bVmins, bVmaxs, ced, cem, cey, cet, ged, gem, gey, get, co2s);
  
  return ret;
}