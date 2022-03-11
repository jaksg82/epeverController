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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef EPCONTROLLER_H
#define EPCONTROLLER_H

// Defines copied from ArduinoModbus
#define COILS             0
#define DISCRETE_INPUTS   1
#define HOLDING_REGISTERS 2
#define INPUT_REGISTERS   3

#include "epRtc.h"
#include "epLive.h"
#include "epStats.h"
#include "epFlags.h"
#include "epConverters.h"
#include "epAddress.h"

/*  struct epAddress {
    int type;
    int start;
    int count;
  } address_obj;
*/

  class epeverController {
    public:
    // Modbus registry addresses
    epAddress RtcAdr = epAddress(HOLDING_REGISTERS, 0x9013, 3);
    epAddress LiveAdr = epAddress(INPUT_REGISTERS, 0x3100, 16);
    epAddress StatisticAdr = epAddress(INPUT_REGISTERS, 0x3300, 22);
    epAddress BatterySocAdr = epAddress(INPUT_REGISTERS, 0x311A, 1);
    epAddress BatteryCurrentAdr = epAddress(INPUT_REGISTERS, 0x331B, 2);
    epAddress StatusFlagsAdr = epAddress(INPUT_REGISTERS, 0x3200, 2);
    
    // Holding values
    uint16_t nodeID = 1;
    uint16_t batterySOC = 0;
    uint32_t batteryCurrent = 0;
    epRtc nodeRtc;
    epLive nodeLive;
    epStats nodeStats;
    epFlags nodeFlags;
    
    // Constructor
    epeverController();
    epeverController(uint16_t id);

    // Output String functions
    const uint8_t CsvHeaderSize = 128;
    const uint8_t CsvValueSize = 128;
    void getCsvHeader(char* retStr);
    void getCsvValues(char* retStr);

  }; // class epController

#endif