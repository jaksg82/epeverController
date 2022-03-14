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

#ifndef EPCONVERTERS_H
#define EPCONVERTERS_H

#include <stdint.h>

class epConverters {
  public:
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

  static uint32_t makeTime(uint8_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second) {   
    // assemble time elements into time_t 
    // note year argument is offset from 1970 (see macros in time.h to convert to other formats)
    // previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9

    static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0
    int i;
    uint32_t seconds;
    /* Useful Constants */
    uint32_t SecXmin = 60ul;
    uint32_t SecXhour = 3600ul;
    uint32_t SecXday = SecXhour * 24ul;
    //uint32_t DAYS_PER_WEEK = 7UL;
    //uint32_t SECS_PER_WEEK = SECS_PER_DAY * DAYS_PER_WEEK;
    //uint32_t SECS_PER_YEAR = SECS_PER_DAY * 365UL; // TODO: ought to handle leap years
    uint32_t SecY2K = 946684800ul; // the time at the start of y2k

    // seconds from 1970 till 1 jan 00:00:00 of the given year
    seconds= SecY2K + (Year * (SecXday * 365));
    for(i = 0; i < Year; i++) {
      if(isLeapYear(i)) {
        seconds += SecXday;   // add extra days for leap years
      }
    }
  
    // add days for this year, months start from 1
    for(i = 1; i < Month; i++) {
      if((i == 2) && isLeapYear(Year)) { 
        seconds += SecXday * 29;
      } else {
        seconds += SecXday * monthDays[i-1];  //monthDay array starts from 0
      }
    }
    seconds+= (Day-1) * SecXday;
    seconds+= Hour * SecXhour;
    seconds+= Minute * SecXmin;
    seconds+= Second;
    return (uint32_t)seconds; 
}

  // leap year calculator expects year argument as years offset from 1970
  static bool isLeapYear(int Y) {
    return ( ((1970+(Y))>0) && !((1970+(Y))%4) && ( ((1970+(Y))%100) || !((1970+(Y))%400) ) );
  }

};

#endif
