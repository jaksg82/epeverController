 /* // statistics
  union {
    struct {
  
      // 4*1 = 4
      uint16_t  pVmax;
      uint16_t  pVmin;
      uint16_t  bVmax;
      uint16_t  bVmin;
  
      // 4*2 = 8
      uint32_t  consEnerDay;
      uint32_t  consEnerMon;
      uint32_t  consEnerYear;
      uint32_t  consEnerTotal;
  
      // 4*2 = 8
      uint32_t  genEnerDay;
      uint32_t  genEnerMon;
      uint32_t  genEnerYear;
      uint32_t  genEnerTotal;
  
      // 1*2 = 2
      uint32_t  c02Reduction;
     
    } s;
    uint16_t  buf[22];  
  } stats;
 */

#ifndef EPSTATS_H
#define EPSTATS_H
#include <stdio.h>
#include <stdint.h>
namespace epever {

class epStats {
  private:
  uint16_t pVmax, pVmin, bVmax, bVmin;
  uint32_t consEnerDay, consEnerMon, consEnerYear, consEnerTotal;
  uint32_t genEnerDay, genEnerMon, genEnerYear, genEnerTotal;
  uint32_t c02Reduction;
  String fmtNum(uint8_t val);
  uint32_t combined(uint16_t valL, uint16_t valH);
    
  public:
  epStats(uint16_t buf[22]);
  String getVoltsStr();
  String getConsumedStr();
  String getGeneratedStr();
  String getCsvStr();
  String getCsvHdrStr();
};
}
#endif