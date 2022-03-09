#include "epLive.h"

epever::epLive::epLive() {
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

epever::epLive::epLive(uint16_t buf[16]) {
  pV = buf[0];
  pI = buf[1];
  pP = epever::epController::combine16to32(buf[2], buf[3]);
  bV = buf[4];
  bI = buf[5];
  bP = epever::epController::combine16to32(buf[6], buf[7]);
  lV = buf[8];
  lI = buf[9];
  lP = epever::epController::combine16to32(buf[10], buf[11]);
}

epever::epLive::epLive(uint16_t w0, uint16_t w1, uint16_t w2, uint16_t w3, uint16_t w4, uint16_t w5, uint16_t w6, uint16_t w7, uint16_t w8, uint16_t w9, uint16_t w10, uint16_t w11) {
  pV = w0;
  pI = w1;
  pP = epever::epController::combine16to32(w2, w3);
  bV = w4;
  bI = w5;
  bP = epever::epController::combine16to32(w6, w7);
  lV = w8;
  lI = w9;
  lP = epever::epController::combine16to32(w10, w11);
}

void epever::epLive::setPanelData(uint16_t val0, uint16_t val1, uint16_t val2, uint16_t val3) {
  pV = val0;
  pI = val1;
  pP = epever::epController::combine16to32(val2, val3);
}

void epever::epLive::setBatteryData(uint16_t val0, uint16_t val1, uint16_t val2, uint16_t val3) {
  bV = val0;
  bI = val1;
  bP = epever::epController::combine16to32(val2, val3);
}

void epever::epLive::setLoadData(uint16_t val0, uint16_t val1, uint16_t val2, uint16_t val3) {
  lV = val0;
  lI = val1;
  lP = epever::epController::combine16to32(val2, val3);
}


void epever::epLive::getPanelStr(char* retStr[], uint8_t* retSize) {
  *retSize = (uint8_t)26;
  char ret[26];
  float pVs = pV / 100.0f;
  float pIs = pI / 100.0f;
  float pPs = pP / 100.0f;
  sprintf(ret, "%6.2fV, %6.2fA, %6.2fW", pVs, pIs, pPs);
  *retStr = ret;
}

void epever::epLive::getBatteryStr(char* retStr[], uint8_t* retSize) {
  *retSize = (uint8_t)26;
  char ret[26];
  float bVs = bV / 100.0f;
  float bIs = bI / 100.0f;
  float bPs = bP / 100.0f;
  sprintf(ret, "%6.2fV, %6.2fA, %6.2fW", bVs, bIs, bPs);
  *retStr = ret;
}

void epever::epLive::getLoadStr(char* retStr[], uint8_t* retSize) {
  *retSize = (uint8_t)26;
  char ret[26];
  float lVs = lV / 100.0f;
  float lIs = lI / 100.0f;
  float lPs = lP / 100.0f;
  sprintf(ret, "%6.2fV, %6.2fA, %6.2fW", lVs, lIs, lPs);
  *retStr = ret;
}
