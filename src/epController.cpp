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

#include "epController.h"

epever::epController::epController(uint16_t value) {
  nodeID = value;
  nodeRtc = epRtc();
  nodeLive = epLive();
  nodeStats = epStats();
  nodeFlags = epFlags();
}

// Converting functions

static uint32_t combine16to32(uint16_t low, uint16_t high) {
  return (static_cast<uint32_t>(high) << 16) + static_cast<uint32_t>(low);
}

static uint8_t getFirstByte(uint16_t value) {
  return (uint8_t)((value & 0xFF00) >> 8);
}

static uint8_t getSecondByte(uint16_t value) {
  return (uint8_t)(value & 0x00FF);
}


// Output String functions

void epever::epController::fmtNum(uint8_t val, char* retStr[], uint8_t* retSize) {
  *retSize = (uint8_t)2;
  char ret[2];
  sprintf(ret, "%02d", val);
  *retStr = ret;
}