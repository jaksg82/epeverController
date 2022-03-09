#include <stdio.h>
#include <stdint.h>
//#include <string>
#include <stdlib.h>

#ifndef EPCONTROLLER_H
#define EPCONTROLLER_H

namespace epever {


#include "epRtc.h"
#include "epLive.h"
#include "epStats.h"
#include "epFlags.h"

  struct epAddress {
    int start;
    int count;
  } address_obj;

  class epController {
    public:
    // Modbus registry addresses
    struct epAddress RtcAdr = {0x9013, 3};
    struct epAddress LiveAdr = {0x3100, 16};
    struct epAddress StatisticAdr = {0x3300, 22};
    struct epAddress BatterySocAdr = {0x311A, 1};
    struct epAddress BatteryCurrentAdr = {0x331B, 2};
    struct epAddress StatusFlagsAdr = {0x3200, 2};
    
    // Holding values
    uint16_t nodeID = 1;
    uint16_t batterySOC = 0;
    uint32_t batteryCurrent = 0;
    epRtc nodeRtc;
    epLive nodeLive;
    epStats nodeStats;
    epFlags nodeFlags;
    
    // Constructor
    epController(uint16_t id);

    // Converting functions
    static uint32_t combine16to32(uint16_t valL, uint16_t valH);
    static uint8_t getFirstByte(uint16_t value);
    static uint8_t getSecondByte(uint16_t value);
    
    // Output String functions
    static void fmtNum(uint8_t val, char* retStr[], uint8_t* retSize);
    void getCsvHeader(char* retStr, uint8_t* retSize);
    void getCsvValues(char* retStr, uint8_t* retSize);

  }; // class epController
}; // namespace

#endif