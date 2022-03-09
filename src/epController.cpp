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