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
#include <string.h>

#ifndef EPCONTROLLER_H
#define EPCONTROLLER_H

#include "epRtc.h"
#include "epLive.h"
#include "epStats.h"
#include "epFlags.h"
#include "epConverters.h"
#include "epAddress.h"

class epeverController {
  private:
  // Defines copied from ArduinoModbus
  static const uint8_t coils = 0;            // #define COILS 0
  static const uint8_t discreteInputs = 1;   // #define DISCRETE_INPUTS 1
  static const uint8_t holdingRegisters = 2; // #define HOLDING_REGISTERS 2
  static const uint8_t inputRegisters = 3;   // #define INPUT_REGISTERS 3
  static const uint16_t csvHeaderSize = 280;
  static const uint16_t csvValueSize = 290;

public:
  // Modbus registry addresses
  epAddress RtcAdr = epAddress(holdingRegisters, 0x9013, 3);
  epAddress LiveAdr = epAddress(inputRegisters, 0x3100, 27);
  epAddress StatisticAdr = epAddress(inputRegisters, 0x3300, 29);
  //epAddress BatterySocAdr = epAddress(inputRegisters, 0x311A, 1); // Incorporated in epLive
  //epAddress BatteryCurrentAdr = epAddress(inputRegisters, 0x331B, 2);  // Incorporated in epStats
  epAddress StatusFlagsAdr = epAddress(inputRegisters, 0x3200, 2);

  // Holding values
  uint16_t nodeID = 1;
  //uint16_t batterySOC = 0;
  //uint32_t batteryCurrent = 0;
  epRtc nodeRtc;
  epLive nodeLive;
  epStats nodeStats;
  epFlags nodeFlags;

  // Constructor
  epeverController();
  epeverController(uint16_t id);

  // Output String functions
  uint16_t getCsvHeaderSize() { return csvHeaderSize; }
  uint16_t getCsvValueSize() { return csvValueSize; }
  char *getCsvHeader();
  char *getCsvValues();

}; // class epController

#endif