// live data
//  union {
//    struct {
//      int16_t  pV;
//      int16_t  pI;
//      int32_t  pP;
//      int16_t  bV;
//      int16_t  bI;
//      int32_t  bP;
//      uint16_t  dummy[4];
//      int16_t  lV;
//      int16_t  lI;
//      int32_t  lP;
//    } l;
//    uint16_t  buf[16];
//  } live;
#ifndef EPLIVE_H
#define EPLIVE_H

//#include <Arduino.h>
#include <stdio.h>
#include <stdint.h>

namespace epever {
#include "epController.h"

class epLive {
  private:
  int16_t pV, pI, bV, bI, lV, lI;  // Volts & Amperes
  int32_t pP, bP, lP;              // Watts

  public:
  epLive();
  epLive(uint16_t buf[16]);
  epLive(uint16_t w0, uint16_t w1, uint16_t w2, uint16_t w3, uint16_t w4, uint16_t w5, uint16_t w6, uint16_t w7, uint16_t w8, uint16_t w9, uint16_t w10, uint16_t w11);
  void setPanelData(uint16_t val0, uint16_t val1, uint16_t val2, uint16_t val3);
  void setBatteryData(uint16_t val0, uint16_t val1, uint16_t val2, uint16_t val3);
  void setLoadData(uint16_t val0, uint16_t val1, uint16_t val2, uint16_t val3);
  void getPanelStr(char* retStr[], uint8_t* retSize);
  void getBatteryStr(char* retStr[], uint8_t* retSize);
  void getLoadStr(char* retStr[], uint8_t* retSize);

};

};

#endif