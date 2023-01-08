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
TaskHandle_t task_txSetData;
TaskHandle_t task_txSendData;

/**
 * Use core 0 to read the inputs
 */
void func_txSetData( void * pvParameters ){
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
 * Use core 1 to send the data
 */
void func_txSendData( void * pvParameters ){
    while(true){
      /*
        Radio Transmit
      */
      if(transmittedFlag) {
        enableInterrupt = false;
        transmittedFlag = false;
        radio.finishTransmit();
        int state = radio.startTransmit(packageData.byteArray, sizeof(packageData.byteArray));
        enableInterrupt = true;
      }
      
      if (enableSerialPrint) {
        Serial.print("[SX1280] Transmitting packet ( ");
        Serial.print(sizeof(packageData.byteArray));
        Serial.print(" ) ... ");
        Serial.println("");
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
    func_txSetData,   // Function to implement the task
    "task_txSetData", // Name of the task
    10000,            // Stack size in words
    NULL,             // Task input parameter
    4,                // Priority of the task
    &task_txSetData,  // Task handle
    taskCore1         // Core where the task should run
  );

  xTaskCreatePinnedToCore(
    func_txSendData,    // Function to implement the task
    "task_txSendData",  // Name of the task 
    10000,              // Stack size in words 
    NULL,               // Task input parameter
    3,                  // Priority of the task
    &task_txSendData,   // Task handle
    taskCore2           // Core where the task should run
  );

}

void loop() {
}
