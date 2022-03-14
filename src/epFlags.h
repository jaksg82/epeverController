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

/*   // battery status
  struct {
    uint8_t volt;        // d3-d0  Voltage:     00H Normal, 01H Overvolt, 02H UnderVolt, 03H Low Volt Disconnect, 04H Fault
    uint8_t temp;        // d7-d4  Temperature: 00H Normal, 01H Over warning settings, 02H Lower than the warning settings
    uint8_t resistance;  // d8     abnormal 1, normal 0
    uint8_t rated_volt;  // d15    1-Wrong identification for rated voltage
  } status_batt ;

  char batt_volt_status[][20] = {
    "Normal",
    "Overvolt",
    "Low Volt Disconnect",
    "Fault"
  };

  char batt_temp_status[][16] = {
    "Normal",
    "Over WarnTemp",
    "Below WarnTemp"
  };

    char charger_charging_status[][12] = {
    "Off",
    "Float",
    "Boost",
    "Equlization"
  };

 */
#ifndef EPFLAGS_H
#define EPFLAGS_H

#include <stdio.h>
#include <stdint.h>

class epFlags {
private:
  static const uint8_t flagStringSize = 48;
  uint8_t voltMode, tempMode, resistance, ratedVolt, chargerMode;

  char voltStatus[4][8] = {
      "Normal",
      "OverV",
      "LowV",
      "Fault"};

  char tempStatus[3][8] = {
      "Normal",
      "OverT",
      "LowT"};

  char chargingStatus[4][8] = {
      "Off",
      "Float",
      "Boost",
      "Equaliz"};

public:
  // Constructor
  epFlags();
  epFlags(uint16_t buf[2]);
  epFlags(uint16_t hr0, uint16_t hr1);

  // Get csv strings
  uint8_t getFlagsStrSize() { return flagStringSize; }
  char *getFlagsStr();
  
}; // class

#endif