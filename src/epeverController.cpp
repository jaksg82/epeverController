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

#include "epeverController.h"

epeverController::epeverController() {
  nodeID = 1; // Default ID
  nodeRtc = epRtc();
  nodeLive = epLive();
  nodeStats = epStats();
  nodeFlags = epFlags();
}

epeverController::epeverController(uint16_t value) {
  nodeID = value;
  nodeRtc = epRtc();
  nodeLive = epLive();
  nodeStats = epStats();
  nodeFlags = epFlags();
}

char * epeverController::getCsvHeader() {
  static char ret[csvHeaderSize] = "ID,DateTime,PanelV,PanelA,PanelW,BatV,BatA,BatW,LoadV,LoadA,LoadW,BatSOC,BatCurrent,PanelVmin,PanelVmax,BatVmin,BatVmax,ConsDay,ConsMonth,ConsYear,ConsTotal,GenDay,GenMonth,GenYear,GenTotal,Co2red,VoltMode,VoltStatus,TempMode,TempStatus,Resist,RatedV,ChargerMode,ChargerStatus";
  return ret;
}

char * epeverController::getCsvValues() {
  // nodeID = 3;
  // rtcStringSize = 16;
  // liveStringSize = 68;
  // statsStringSize = 140;
  // flagStringSize = 48;
  // total required size = 280 + 4commas = 284;
  static char ret[csvValueSize];
  char epc[6];
  sprintf(epc, "%3u", nodeID);
  strcat(ret, epc);
  strcat(ret, ",");
  strcat(ret, nodeRtc.getRtcStr());
  strcat(ret, ",");
  strcat(ret, nodeLive.getLiveStr());
  strcat(ret, ",");
  strcat(ret, nodeStats.getStatsStr());
  strcat(ret, ",");
  strcat(ret, nodeFlags.getFlagsStr());
  return ret;
}
