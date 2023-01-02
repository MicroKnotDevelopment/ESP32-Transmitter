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

static int taskCore1 = 0;
static int taskCore2 = 1;
TaskHandle_t task_rxSetData;
TaskHandle_t task_rxSendData;

/**
 * Use core 0 to read the inputs
 */
void func_rxSetData( void * pvParameters ){
    while(true){
      /*
        ads1115 read
      */
      joysticksSetData();
    
      /*
        Rotary 1
      */
      anoRotaryEncoder1SetData();
      
      /*
        Rotary 2
      */
      anoRotaryEncoder2SetData();

      /*
        Potentiometers
      */
      potentiometersSetData();
    
      // Switches
      switchesSetData();
    }
}

/**
 * Use core 0 to send the data
 */
void func_rxSendData( void * pvParameters ){
    while(true){
      /*
        Radio Transmit
      */
      if (enableSerialPrint) {
        Serial.print("[SX1280] Transmitting packet ( ");
        Serial.print(sizeof(packageData.byteArray));
        Serial.print(" ) ... ");
      }
      
      int state = radio.transmit(packageData.byteArray, sizeof(packageData.byteArray));

      if (enableSerialPrint) {
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
    }
}

void setup() {
  if(enableSerialPrint) {
    Serial.begin(115200);
  }

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

  xTaskCreatePinnedToCore(
    func_rxSetData,   // Function to implement the task
    "task_rxSetData", // Name of the task
    10000,            // Stack size in words
    NULL,             // Task input parameter
    0,                // Priority of the task
    &task_rxSetData,  // Task handle
    taskCore1         // Core where the task should run
  );
 
  xTaskCreatePinnedToCore(
    func_rxSendData,    // Function to implement the task
    "task_rxSendData",  // Name of the task 
    10000,              // Stack size in words 
    NULL,               // Task input parameter
    1,                  // Priority of the task
    &task_rxSendData,   // Task handle
    taskCore2           // Core where the task should run
  );
}

void loop() {
}
