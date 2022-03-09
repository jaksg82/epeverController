#include "epRtc.h"

epever::epRtc::epRtc(uint16_t hr0, uint16_t hr1, uint16_t hr2) {
  uint8_t y, M, d, h, m, s;
  m = epever::epController::getFirstByte(hr0);
  s = epever::epController::getSecondByte(hr0);
  d = epever::epController::getFirstByte(hr1);
  h = epever::epController::getSecondByte(hr1);
  y = epever::epController::getFirstByte(hr2);
  M = epever::epController::getSecondByte(hr2);
  struct tm *timeInfo;
  timeInfo->tm_year = 100 + y; // Add 2000 and subtract 1900
  timeInfo->tm_mon = M - 1; // Zero based counter
  timeInfo->tm_mday = d;
  timeInfo->tm_hour = h;
  timeInfo->tm_min = m;
  timeInfo->tm_sec = s;
  timeInfo->tm_isdst = 0;
  storeTime = mktime(timeInfo);
}

void epever::epRtc::getRtcStr(char* retStr[], uint8_t* retSize) {
  *retSize = (uint8_t)16;
  char ret[16];
  struct tm *timeInfo = gmtime(&storeTime);
  strftime(ret, 16, "%Y%m%d-%H%M%S", timeInfo);
  *retStr = ret;
}
