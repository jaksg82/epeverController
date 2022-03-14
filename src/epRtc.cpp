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

#include "epRtc.h"

epRtc::epRtc() {
  storeTime = 0;
}
epRtc::epRtc(uint16_t buf[]) {
  //uint8_t y, M, d, h, m, s;
  m = epConverters::getFirstByte(buf[0]);
  s = epConverters::getSecondByte(buf[0]);
  d = epConverters::getFirstByte(buf[1]);
  h = epConverters::getSecondByte(buf[1]);
  y = epConverters::getFirstByte(buf[2]);
  M = epConverters::getSecondByte(buf[2]);
  storeTime = epConverters::makeTime(y, M, d, h, m, s);
}
epRtc::epRtc(uint16_t hr0, uint16_t hr1, uint16_t hr2) {
  //uint8_t y, M, d, h, m, s;
  m = epConverters::getFirstByte(hr0);
  s = epConverters::getSecondByte(hr0);
  d = epConverters::getFirstByte(hr1);
  h = epConverters::getSecondByte(hr1);
  y = epConverters::getFirstByte(hr2);
  M = epConverters::getSecondByte(hr2);
  storeTime = epConverters::makeTime(y, M, d, h, m, s);
}

char* epRtc::getRtcStr() {
  static char timeStr[rtcStringSize];
  sprintf(timeStr, "20%02d%02d%02d-%02d%02d%02d", y, M, d, h, m, s);
  return timeStr;
}
