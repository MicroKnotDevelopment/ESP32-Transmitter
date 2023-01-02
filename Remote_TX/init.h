// Rotary encoder
RotaryEncoder *encoder1 = nullptr;
RotaryEncoder *encoder2 = nullptr;

// MCP23017
/*
  Addr(BIN)  Addr(hex)   param
  010 0111    0x27        7
  010 0110    0x26        6
  010 0101    0x25        5
  010 0100    0x24        4
  010 0011    0x23        3
  010 0010    0x22        2
  010 0001    0x21        1
  010 0000    0x20        0
*/
Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;

int16_t
        // Potentiometer Values
        pot1, pot2, pot3, pot4, pot5, pot6,
        
        // Potentiometer AnalogRead
        pot1Read, pot2Read, pot3Read, pot4Read, pot5Read, pot6Read,

        // Potentiometer AnalogRead
        pot1LastValue, pot2LastValue, pot3LastValue, pot4LastValue, pot5LastValue, pot6LastValue,

        // Potentiometer On/Off values
        potSwitch1, potSwitch2, potSwitch3, potSwitch4, potSwitch5, potSwitch6,

        // On/Off switch values
        switch1, switch2, switch3, switch4, switch5,

        // ANO Rotary Navigation #1        
        rotary1_up, rotary1_down, rotary1_left, rotary1_right, rotary1_center, rotary1_enc1, rotary1_enc2,
        
        // ANO Rotary Navigation #2
        rotary2_up, rotary2_down, rotary2_left, rotary2_right, rotary2_center, rotary2_enc1, rotary2_enc2;


// ads1115
Adafruit_ADS1115 ads;
int16_t adc0, adc1, adc2, adc3, adc0_map, adc1_map, adc2_map, adc3_map, j1xMiddle, j1yMiddle, j2xMiddle, j2yMiddle;
