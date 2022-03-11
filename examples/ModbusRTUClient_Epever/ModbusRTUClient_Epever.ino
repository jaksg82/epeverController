/*
  Modbus RTU Client for Epever Controller

  This sketch creates a Modbus RTU Client that interact wih an Epever Contoller.
  
  Circuit:
   - MKR board
   - MKR 485 shield
     - ISO GND connected to GND of the Modbus RTU server (pin 7-8 of rj45 connector)
     - Z connected to A of the Modbus RTU server (pin 5-6 of rj45 connector)
     - Y connected to B of the Modbus RTU server (pin 3-4 of rj45 connector)
     - Jumper positions
       - FULL set to OFF (HALF)
       - Z \/\/ Y set to ON

  created 10 March 2022
  by Simone Giacomoni
*/

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <epeverController.h>

// Initialize the Controller object
epeverController epNode;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Modbus RTU Client for Epever Controller");

  // start the Modbus RTU client
  if (!ModbusRTUClient.begin(115200)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
  ModbusRTUClient.setTimeout(2000);

  epNode = epeverController(1);
}

void loop() {
  
  // read RTC Register values
  Serial.print("Reading RTC from Holding Registers ... ");

  // read multiple values from slave with: id, page, address and count
  if (!ModbusRTUClient.requestFrom(epNode.nodeID, epNode.RtcAdr.type, epNode.RtcAdr.start, epNode.RtcAdr.count)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    if(ModbusRTUClient.available() >= epNode.RtcAdr.count) {
      uint16_t buf[epNode.RtcAdr.count];
      for(int i = 0; i < epNode.RtcAdr.count; i++) {
        buf[i] = ModbusRTUClient.read();
      }
      // Update the RTC node with the buffered values
      epNode.nodeRtc = epRtc(buf);
      // Create a char array (string) to store the returned formatted string
      char timeString[epNode.nodeRtc.rtcStringSize];
      // Call the string formatting function
      epNode.nodeRtc.getRtcStr(timeString);
      // Output the string to the serial
      Serial.println(timeString);
    }
    // Purge extra values. Should be empty but clean anyway
    flushReadBuffer(); 
  }

  
  
  delay(10000);
  Serial.println();
}


void flushReadBuffer() {
  while (ModbusRTUClient.available()) {
    ModbusRTUClient.read();
  }
}

//------
// ModBus Read Functions
//------
/*
void readRtcHR(int adr, int cnt) {
  Serial.print("Reading RTC Input Register values ... ");

  // read cnt Input Register values from (slave) id , address adr
  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, adr, cnt)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    if(ModbusRTUClient.available() >= cnt) {
      uint16_t hr0, hr1, hr2;
      hr0 = ModbusRTUClient.read();   // Minutes and Seconds
      hr1 = ModbusRTUClient.read();   // Days and Hours
      hr2 = ModbusRTUClient.read();   // Years and Months
      epRtc eptime(hr0, hr1, hr2);
      Serial.println(eptime.getStr(true));
    }
    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }
}


void readLiveData(int adr, int cnt) {
  Serial.print("Reading Live Input values ... ");

  // read 10 Discrete Input values from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, adr, cnt)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");

    uint16_t hr0, hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr8, hr9, hr10, hr11, dummy;
    if(ModbusRTUClient.available() >= cnt) {
      hr0 = ModbusRTUClient.read();    // Panel Volts
      hr1 = ModbusRTUClient.read();    // Panel Amperes
      hr2 = ModbusRTUClient.read();    // Panel Watts (1 of 2)
      hr3 = ModbusRTUClient.read();    // Panel Watts (2 of 2)
      hr4 = ModbusRTUClient.read();    // Battery Volts
      hr5 = ModbusRTUClient.read();    // Battery Amperes
      hr6 = ModbusRTUClient.read();    // Battery Watts (1 of 2)
      hr7 = ModbusRTUClient.read();    // Battery Watts (2 of 2)
      dummy = ModbusRTUClient.read();
      dummy = ModbusRTUClient.read();
      dummy = ModbusRTUClient.read();
      dummy = ModbusRTUClient.read();
      hr8 = ModbusRTUClient.read();    // Load Volts
      hr9 = ModbusRTUClient.read();    // Load Amperes
      hr10 = ModbusRTUClient.read();   // Load Watts (1 of 2)
      hr11 = ModbusRTUClient.read();   // Load Watts (2 of 2)
      epLive epLd(hr0, hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr8, hr9, hr10, hr11);
      Serial.print("Live Panel:   ");
      Serial.println(epLd.getPanelStr());
//      Serial.print(hr0, HEX);
//      Serial.print("|");
//      Serial.print(hr1, HEX);
//      Serial.print("|");
//      Serial.print(hr2, HEX);
//      Serial.print("|");
//      Serial.print(hr3, HEX);
//      Serial.println();
      Serial.print("Live Battery: ");
      Serial.println(epLd.getBatteryStr());
//      Serial.print(hr4, HEX);
//      Serial.print("|");
//      Serial.print(hr5, HEX);
//      Serial.print("|");
//      Serial.print(hr6, HEX);
//      Serial.print("|");
//      Serial.print(hr7, HEX);
//      Serial.println();
      Serial.print("Live Load:    ");
      Serial.println(epLd.getLoadStr());
//      Serial.print(hr8, HEX);
//      Serial.print("|");
//      Serial.print(hr9, HEX);
//      Serial.print("|");
//      Serial.print(hr10, HEX);
//      Serial.print("|");
//      Serial.print(hr11, HEX);
//      Serial.println();
    }
    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }

}
*/
