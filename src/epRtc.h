#ifndef EPRTC_H
#define EPRTC_H

namespace epever {

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "epController.h"

class epRtc {
  private:
  time_t storeTime;

  public:
  // Constructor
  epRtc();
  epRtc(uint16_t hr0, uint16_t hr1, uint16_t hr2);

  // String
  void getRtcStr(char* retStr[], uint8_t* retSize);

  // Stored values
  time_t getRtc() { return storeTime; }

}; //class
}; //namespace

#endif