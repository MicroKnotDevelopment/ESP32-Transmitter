// Include the required libraries and config files

#include <RadioLib.h>
#include <RotaryEncoder.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#include "init.h"
#include "config.h"
#include "tx_package.h"
#include "tx_default.h"
#include "tx_set_data.h"
#include "util.h"

void setup() {
  Serial.begin(115200);

  // Load the default values
  defaultValues();

  // Enable the INPUT_PULLUP for the potentiometers
  potentiometersInit();

  /*
    MCP23017
  */
  // MCP1 - Init
  mcp1Init();

  // MCP2 - Init
  mcp2Init();

  // SX1280
  sx1280Init();

  // ads1115
  ads1115Init();
}

void loop() {

  /*
    ads1115 read
  */
  joysticksSetData();

  /*
    Potentiometers
  */
  potentiometersSetData();

  // Switches
  switchesSetData();

  /*
    Rotary 2
  */
  anoRotaryEncoder2SetData();

  /*
    Rotary 1
  */
  anoRotaryEncoder1SetData();

  /*
    Radio Transmit
  */
  Serial.print(F("[SX1280] Transmitting packet ... "));
  
  int state = radio.transmit(packageData.byteArray, sizeof(packageData.byteArray));

  if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));
  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F("too long!"));
  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);
  }
}
