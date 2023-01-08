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
int potSensitivityValue = 2;

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

float frequency     = 2400.0;
int bitRate         = 520;
int codingRate      = 2;
int outputPower     = 8;
float dataShaping   = 1.0;
uint8_t syncWord[]  = {0x01, 0x23, 0x45, 0x67};
int crcValue        = 0;
