// Debug
bool enableSerialPrint = false;

// MCP23017
#define MCP23X17_addr1 0x25
#define MCP23X17_addr2 0x26

// ads1115
#define ADS1115_addr1 0x48

//Switch Button
#define buttonSwitch_1 15
#define buttonSwitch_2 14
#define buttonSwitch_3 13
#define buttonSwitch_4 12
#define buttonSwitch_5 11

//Pot Switch Button
#define buttonSwitchPot_1 3
#define buttonSwitchPot_2 2
#define buttonSwitchPot_3 1
#define buttonSwitchPot_4 0
#define buttonSwitchPot_5 4
#define buttonSwitchPot_6 5

//Rotary 1 Buttons
#define rotary1_1 11
#define rotary1_2 12
#define rotary1_3 13
#define rotary1_4 14
#define rotary1_5 15
#define rotary1_enc_1 9
#define rotary1_enc_2 10

//Rotary 2 Buttons
#define rotary2_1 0
#define rotary2_2 1
#define rotary2_3 2
#define rotary2_4 3
#define rotary2_5 4
#define rotary2_enc_1 6
#define rotary2_enc_2 5

/*
  Potentiometers
*/
#define POTENTIOMETER_PIN1 A1 //25
#define POTENTIOMETER_PIN2 A10 //27
#define POTENTIOMETER_PIN3 A12 //13
#define POTENTIOMETER_PIN4 A8 //15
#define POTENTIOMETER_PIN5 A9 //33
#define POTENTIOMETER_PIN6 A7 //32

// Joystick Values
int joystickMaxValue = 26598; // Max possible value
int joystickSensitivityValue = 500; // This is used for the joystick sensitivity

/*
  SX1280 has the following connections:
  NSS pin:   2
  DIO1 pin:  26
  NRST pin:  14
  BUSY pin:  21
*/
 
SX1280 radio = new Module(2, 26, 14, 21);

/*
* \param freq Carrier frequency in MHz. Defaults to 2400.0 MHz.
* \param bw LoRa bandwidth in kHz. Defaults to 812.5 kHz.
* \param sf LoRa spreading factor. Defaults to 9.
* \param cr LoRa coding rate denominator. Defaults to 7 (coding rate 4/7).
* \param syncWord 2-byte LoRa sync word. Defaults to RADIOLIB_SX128X_SYNC_WORD_PRIVATE (0x12).
* \param power Output power in dBm. Defaults to 10 dBm.
* \param preambleLength LoRa preamble length in symbols. Defaults to 12 symbols.
 */
float SX1280_freq = 2400.0; // Allowed values are in range from 2400.0 to 2500.0 MHz.
float SX1280_bw = 812.5; // Allowed values are 203.125, 406.25, 812.5 and 1625.0 kHz.
uint8_t SX1280_sf = 9; // Allowed values range from 5 to 12.
uint8_t SX1280_cr = 7; // Allowed values range from 5 to 8.
uint8_t SX1280_syncWord = RADIOLIB_SX128X_SYNC_WORD_PRIVATE;
int8_t SX1280_power = 10; // Allowed values are in range from -18 to 13 dBm.
uint16_t SX1280_preambleLength = 12; // Allowed values range from 1 to 65535.
