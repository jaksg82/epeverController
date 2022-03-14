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

  created 14 March 2022
  by Simone Giacomoni
*/

#include <TimeLib.h>
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#include <epeverController.h>

// Initialize the Controller object with the modbus ID value
// If no value is passed the default value of 1 is assigned
epeverController epNode(1); 

void setup() {
  // Initialize the default serial (USB) port for debug
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Modbus RTU Client for Epever Controller");

  // Start the Modbus RTU client
  if (!ModbusRTUClient.begin(115200)) {
    Serial.println("Failed to start Modbus RTU Client!");
    while (1);
  }
  ModbusRTUClient.setTimeout(2000);
}

void loop() {
  // --------------------------------------------------------------------------
  // Read Holding Registers that contain the RTC values
  // --------------------------------------------------------------------------
  Serial.print("Reading RTC from Holding Registers ... ");
  // Using the requestFrom method of ArduinoModbus library
  // Read multiple values from slave with: id, type, address and count
  // We pass the values stored in the epeverController object
  if (!ModbusRTUClient.requestFrom(epNode.nodeID, epNode.RtcAdr.type, epNode.RtcAdr.start, epNode.RtcAdr.count)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    if(ModbusRTUClient.available() >= epNode.RtcAdr.count) {
      // Store the requested values inside a buffer
      uint16_t buf[epNode.RtcAdr.count];
      for(int i = 0; i < epNode.RtcAdr.count; i++) {
        buf[i] = ModbusRTUClient.read();
      }
      // Update the RTC node with the buffered values to decode the contents
      epNode.nodeRtc = epRtc(buf);
      // Create a char array (string) to store the returned formatted string
      Serial.println("Retrieve a formatted string from epRtc object");
      char* timeString = epNode.nodeRtc.getRtcStr();
      // Output the string to the serial
      Serial.println(timeString);
      // The decoded time can be retrieved also as Arduino time for other use
      // time_t epeverTime = epNode.nodeRtc.getRtc();
    }
    // Purge extra values. Should be empty but clean anyway
    flushReadBuffer(); 
  }
  
  // Wait between two consecutive requests
  delay(200);
  
  // --------------------------------------------------------------------------
  // Read Input Registers that contain the Live values
  // --------------------------------------------------------------------------
  Serial.print("Reading Live from Input Registers ... ");
  // Using the requestFrom method of ArduinoModbus library
  // Read multiple values from slave with: id, type, address and count
  // We pass the values stored in the epeverController object
  if (!ModbusRTUClient.requestFrom(epNode.nodeID, epNode.LiveAdr.type, epNode.LiveAdr.start, epNode.LiveAdr.count)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    if(ModbusRTUClient.available() >= epNode.LiveAdr.count) {
      // Store the requested values inside a buffer
      uint16_t buf[epNode.LiveAdr.count];
      for(int i = 0; i < epNode.LiveAdr.count; i++) {
        buf[i] = ModbusRTUClient.read();
      }
      // Update the Live node with the buffered values to decode the contents
      Serial.println("Create epLive object...");
      epNode.nodeLive = epLive(buf);
      // Create a char array (string) to store the returned formatted string
      Serial.println("Retrieve a formatted string from epLive object");
      char* liveString = epNode.nodeLive.getLiveStr();
      // Output the string to the serial
      Serial.println(liveString);
      // The decoded live values can be retrieved separately for other use
      // float batV = epNode.nodeLive.BatteryVolts();
      // float batA = epNode.nodeLive.BatteryAmperes();
      // float batW = epNode.nodeLive.BatteryWatts();
      // float panV = epNode.nodeLive.PanelVolts();
      // float panA = epNode.nodeLive.PanelAmperes();
      // float panW = epNode.nodeLive.PanelWatts();
      // float loadV = epNode.nodeLive.LoadVolts();
      // float loadA = epNode.nodeLive.LoadAmperes();
      // float loadW = epNode.nodeLive.LoadWatts();
      // uint16_t batSOC = epNode.nodeLive.BatterySOC();
    }
    // Purge extra values. Should be empty but clean anyway
    flushReadBuffer(); 
  }

  // Wait between two consecutive requests
  delay(200);

  // --------------------------------------------------------------------------
  // Read Input Registers that contain the Statistic values
  // --------------------------------------------------------------------------
  Serial.print("Reading Statistic from Input Registers ... ");
  // Using the requestFrom method of ArduinoModbus library
  // Read multiple values from slave with: id, type, address and count
  // We pass the values stored in the epeverController object
  if (!ModbusRTUClient.requestFrom(epNode.nodeID, epNode.StatisticAdr.type, epNode.StatisticAdr.start, epNode.StatisticAdr.count)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    if(ModbusRTUClient.available() >= epNode.StatisticAdr.count) {
      // Store the requested values inside a buffer
      uint16_t buf[epNode.StatisticAdr.count];
      for(int i = 0; i < epNode.StatisticAdr.count; i++) {
        buf[i] = ModbusRTUClient.read();
      }
      // Update the Statistic node with the buffered values to decode the contents
      Serial.println("Create epStats object...");
      epNode.nodeStats = epStats(buf);
      // Create a char array (string) to store the returned formatted string
      Serial.println("Retrieve a formatted string from epStats object");
      char* statString = epNode.nodeStats.getStatsStr();
      // Output the string to the serial
      Serial.println(statString);
    }
    // Purge extra values. Should be empty but clean anyway
    flushReadBuffer(); 
  }

  // Wait between two consecutive requests
  delay(200);

  // --------------------------------------------------------------------------
  // Read Input Registers that contain the Status Flags values
  // --------------------------------------------------------------------------
  Serial.print("Reading Flags from Input Registers ... ");
  // Using the requestFrom method of ArduinoModbus library
  // Read multiple values from slave with: id, type, address and count
  // We pass the values stored in the epeverController object
  if (!ModbusRTUClient.requestFrom(epNode.nodeID, epNode.StatusFlagsAdr.type, epNode.StatusFlagsAdr.start, epNode.StatusFlagsAdr.count)) {
    Serial.print("failed! ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("success");
    if(ModbusRTUClient.available() >= epNode.StatusFlagsAdr.count) {
      // Store the requested values inside a buffer
      uint16_t buf[epNode.StatusFlagsAdr.count];
      for(int i = 0; i < epNode.StatusFlagsAdr.count; i++) {
        buf[i] = ModbusRTUClient.read();
      }
      // Update the Flags node with the buffered values to decode the contents
      Serial.println("Create epFlags object...");
      epNode.nodeFlags = epFlags(buf);
      // Create a char array (string) to store the returned formatted string
      Serial.println("Retrieve a formatted string from epFlags object");
      char* flagString = epNode.nodeFlags.getFlagsStr();
      // Output the string to the serial
      Serial.println(flagString);
    }
    // Purge extra values. Should be empty but clean anyway
    flushReadBuffer(); 
  }


  // Wait longer for the next update
  delay(30000);
}

// --------------------------------------------------------------------------
// Read all available values to empty the modbus response buffer
// --------------------------------------------------------------------------
void flushReadBuffer() {
  while (ModbusRTUClient.available()) {
    ModbusRTUClient.read();
  }
}

