#include "epStats.h"

uint32_t epStats::combined(uint16_t low, uint16_t high)
{
  return (static_cast<uint32_t>(high) << 16) + static_cast<uint32_t>(low);
}

epStats::epStats(uint16_t buf[22]) {
  pVmax = buf[0];
  pVmin = buf[1];
  bVmax = buf[2];
  bVmin = buf[3];
  consEnerDay = combined(buf[4], buf[5]);
  consEnerMon = combined(buf[6], buf[7]);
  consEnerYear = combined(buf[8], buf[9]);
  consEnerTotal = combined(buf[10], buf[11]);
  genEnerDay = combined(buf[12], buf[13]);
  genEnerMon = combined(buf[14], buf[15]);
  genEnerYear = combined(buf[16], buf[17]);
  genEnerTotal = combined(buf[18], buf[19]);
  c02Reduction = combined(buf[20], buf[21]);
}

String epStats::getVoltsStr() {
  String ret = "PVmin: " + String(pVmin);
  ret += ", PVmax: ";
  ret += String(pVmax);
  ret += ", BVmin: ";
  ret += String(bVmin);
  ret += ", BVmax: ";
  ret += String(bVmax);
  return ret;
}

String epStats::getConsumedStr() {
  String ret = "Consumed  Day: " + String(consEnerDay);
  ret += ", Month: ";
  ret += String(consEnerMon);
  ret += ", Year: ";
  ret += String(consEnerYear);
  ret += ", Total: ";
  ret += String(consEnerTotal);
  return ret;
}

String epStats::getGeneratedStr() {
  String ret = "Generated Day: " + String(genEnerDay);
  ret += ", Month: ";
  ret += String(genEnerMon);
  ret += ", Year: ";
  ret += String(genEnerYear);
  ret += ", Total: ";
  ret += String(genEnerTotal);
  return ret;
}

String epStats::getCsvHdrStr() {
  return "PVmin,PVmax,BVmin,BVmax,ConsEnerDay,ConsEnerMonth,ConsEnerYear,ConsEnerTotal,GenEnerDay,GenEnerMonth,GenEnerYear,GenEnerTotal,CO2Reduction";
}
String epStats::getCsvStr() {
  String ret = String(pVmin) + ",";
  ret += String(pVmax) + ",";
  ret += String(bVmin) + ",";
  ret += String(bVmax) + ",";
  ret += String(consEnerDay) + ",";
  ret += String(consEnerMon) + ",";
  ret += String(consEnerYear) + ",";
  ret += String(consEnerTotal) + ",";
  ret += String(genEnerDay) + ",";
  ret += String(genEnerMon) + ",";
  ret += String(genEnerYear) + ",";
  ret += String(genEnerTotal) + ",";
  ret += String(c02Reduction);
  return ret;
}