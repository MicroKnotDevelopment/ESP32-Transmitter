/**
 * util.h
 */

// Enable the INPUT_PULLUP for the Potentiometers
void potentiometersInit() {
  pinMode(POTENTIOMETER_PIN1, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN2, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN3, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN4, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN5, INPUT_PULLUP);
  pinMode(POTENTIOMETER_PIN6, INPUT_PULLUP);
}

// Enable the INPUT_PULLUP for the MCP1
void mcp1Init() {
  mcp1.begin_I2C(MCP23X17_addr1);

  //  Switches
  mcp1.pinMode(buttonSwitch_1, INPUT_PULLUP);
  mcp1.pinMode(buttonSwitch_2, INPUT_PULLUP);
  mcp1.pinMode(buttonSwitch_3, INPUT_PULLUP);
  mcp1.pinMode(buttonSwitch_4, INPUT_PULLUP);
  mcp1.pinMode(buttonSwitch_5, INPUT_PULLUP);

  //  Rotary Switch 2 - Buttons
  mcp1.pinMode(rotary2_1, INPUT_PULLUP);
  mcp1.pinMode(rotary2_2, INPUT_PULLUP);
  mcp1.pinMode(rotary2_3, INPUT_PULLUP);
  mcp1.pinMode(rotary2_4, INPUT_PULLUP);
  mcp1.pinMode(rotary2_5, INPUT_PULLUP);

  //  Rotary Switch 2 - Encoder
  mcp1.pinMode(rotary2_enc_1, INPUT_PULLUP);
  mcp1.pinMode(rotary2_enc_2, INPUT_PULLUP);

  // Ano Rotary Encoder #2
  encoder2 = new RotaryEncoder(
    mcp1.digitalRead(rotary2_enc_1),
    mcp1.digitalRead(rotary2_enc_2),
    RotaryEncoder::LatchMode::TWO03,
    false,
    false
  );
}

// Enable the INPUT_PULLUP for the MCP2
void mcp2Init() {
  mcp2.begin_I2C(MCP23X17_addr2);

  mcp2.pinMode(buttonSwitchPot_1, INPUT_PULLUP);
  mcp2.pinMode(buttonSwitchPot_2, INPUT_PULLUP);
  mcp2.pinMode(buttonSwitchPot_3, INPUT_PULLUP);
  mcp2.pinMode(buttonSwitchPot_4, INPUT_PULLUP);
  mcp2.pinMode(buttonSwitchPot_5, INPUT_PULLUP);
  mcp2.pinMode(buttonSwitchPot_6, INPUT_PULLUP);

  // Rotary Switch 1 - Buttons
  mcp2.pinMode(rotary1_1, INPUT_PULLUP);
  mcp2.pinMode(rotary1_2, INPUT_PULLUP);
  mcp2.pinMode(rotary1_3, INPUT_PULLUP);
  mcp2.pinMode(rotary1_4, INPUT_PULLUP);
  mcp2.pinMode(rotary1_5, INPUT_PULLUP);

  // Rotary Switch 1 - Encoder
  mcp2.pinMode(rotary1_enc_1, INPUT_PULLUP);
  mcp2.pinMode(rotary1_enc_2, INPUT_PULLUP);

  // Ano Rotary Encoder #1
  encoder1 = new RotaryEncoder(
    mcp2.digitalRead(rotary1_enc_1),
    mcp2.digitalRead(rotary1_enc_2),
    RotaryEncoder::LatchMode::TWO03,
    false,
    false
  );
}

// sx1280 init
void sx1280Init() {
  if(enableSerialPrint) {
    Serial.print(F("[SX1280] Initializing ... ")); 
  }
  // carrier frequency:           2400.0 MHz
  // bandwidth:                   812.5 kHz
  // spreading factor:            9
  // coding rate:                 7
  // output power:                10 dBm
  // preamble length:             12 symbols
  // CRC:                         enabled
  int state = radio.begin(SX1280_freq, SX1280_bw, SX1280_sf, SX1280_cr, SX1280_syncWord, SX1280_power, SX1280_preambleLength);

  if(enableSerialPrint) {
    if (state == RADIOLIB_ERR_NONE) {
      //Serial.println(F("success!"));
    } else {
      Serial.print(F("failed, code "));
      Serial.println(state);
      while (true);
    }
  }
}

// ads1115 init
void ads1115Init() {
  ads.setDataRate(RATE_ADS1115_860SPS);
  ads.setGain(GAIN_ONE);
  ads.begin(ADS1115_addr1);
}
