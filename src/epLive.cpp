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

#include "epLive.h"

// ----------------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------------
epLive::epLive() {
  pV = 0;
  pI = 0;
  pP = 0;
  bV = 0;
  bI = 0;
  bP = 0;
  lV = 0;
  lI = 0;
  lP = 0;
}

epLive::epLive(uint16_t buf[27]) {
  pV = buf[0];
  pI = buf[1];
  pP = epConverters::combine16to32(buf[2], buf[3]);
  bV = buf[4];
  bI = buf[5];
  bP = epConverters::combine16to32(buf[6], buf[7]);
  lV = buf[8];
  lI = buf[9];
  lP = epConverters::combine16to32(buf[10], buf[11]);
  batSoc = buf[26];
}

// ----------------------------------------------------------------------------
// Get the csv strings
// ----------------------------------------------------------------------------

char* epLive::getLiveStr() {
  static char ret[liveStringSize];
  float pVs = pV / 100.0f;
  float pIs = pI / 100.0f;
  float pPs = pP / 100.0f;
  float bVs = bV / 100.0f;
  float bIs = bI / 100.0f;
  float bPs = bP / 100.0f;
  float lVs = lV / 100.0f;
  float lIs = lI / 100.0f;
  float lPs = lP / 100.0f;
  sprintf(ret, "%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%3u", pVs, pIs, pPs, bVs, bIs, bPs, lVs, lIs, lPs, batSoc);
  
  return ret;
}
