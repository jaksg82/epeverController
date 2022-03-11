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
  nodeID = 1;
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

void epeverController::getCsvHeader(char* retStr) {
  char ret[CsvHeaderSize] = "CSVHeader";
  *retStr = *ret;
}

void epeverController::getCsvValues(char* retStr) {
  char ret[CsvValueSize] = "CSVHeader";
  *retStr = *ret;
}
