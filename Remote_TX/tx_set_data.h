/**
 * tx_read.h
 */

void potentiometersSetData() {
  /*
    Potentiometer Values
  */
  packageData.structure.p1 = map(analogRead(POTENTIOMETER_PIN1), 0, 4095, 255, 0);
  packageData.structure.p2 = map(analogRead(POTENTIOMETER_PIN2), 0, 4095, 255, 0);
  packageData.structure.p3 = map(analogRead(POTENTIOMETER_PIN3), 0, 4095, 255, 0);
  packageData.structure.p4 = map(analogRead(POTENTIOMETER_PIN4), 0, 4095, 255, 0);
  packageData.structure.p5 = map(analogRead(POTENTIOMETER_PIN5), 0, 4095, 0, 255);
  packageData.structure.p6 = map(analogRead(POTENTIOMETER_PIN6), 0, 4095, 255, 0);
  
  /*
    Potentiometer Switches
  */
  packageData.structure.p1s = !mcp2.digitalRead(buttonSwitchPot_1);
  packageData.structure.p2s = !mcp2.digitalRead(buttonSwitchPot_2);
  packageData.structure.p3s = !mcp2.digitalRead(buttonSwitchPot_3);
  packageData.structure.p4s = !mcp2.digitalRead(buttonSwitchPot_4);
  packageData.structure.p5s = !mcp2.digitalRead(buttonSwitchPot_5);
  packageData.structure.p6s = !mcp2.digitalRead(buttonSwitchPot_6);
}

void switchesSetData() {
  packageData.structure.s1 = mcp1.digitalRead(buttonSwitch_1);
  packageData.structure.s2 = mcp1.digitalRead(buttonSwitch_2);
  packageData.structure.s3 = mcp1.digitalRead(buttonSwitch_3);
  packageData.structure.s4 = mcp1.digitalRead(buttonSwitch_4);
  packageData.structure.s5 = mcp1.digitalRead(buttonSwitch_5);
}

void anoRotaryEncoder2SetData() {
  static int pos2 = 0;
  int newPos2 = encoder2->getPosition(),
  direction2 = 0;

  packageData.structure.re2_up      = !mcp1.digitalRead(rotary2_2);
  packageData.structure.re2_down    = !mcp1.digitalRead(rotary2_4);
  packageData.structure.re2_left    = !mcp1.digitalRead(rotary2_3);
  packageData.structure.re2_right   = !mcp1.digitalRead(rotary2_5);
  packageData.structure.re2_center  = !mcp1.digitalRead(rotary2_1);

  rotary2_enc1 = mcp1.digitalRead(rotary2_enc_1);
  rotary2_enc2 = mcp1.digitalRead(rotary2_enc_2);

  encoder2->tick(rotary2_enc1, rotary2_enc2);

  packageData.structure.re2_dir = 0;
  if (pos2 != newPos2) {
    pos2 = newPos2;
    direction2 = (int)encoder2->getDirection();
  }
  packageData.structure.re2_dir = direction2;
}

void anoRotaryEncoder1SetData() {
  static int pos1 = 0;
  int newPos1 = encoder1->getPosition(),
      direction1 = 0;

  encoder1->tick(
    mcp2.digitalRead(rotary1_enc_1),
    mcp2.digitalRead(rotary1_enc_2)
  );

  packageData.structure.re1_dir = 0;
  if (pos1 != newPos1) {
    pos1 = newPos1;
    direction1 = (int)encoder1->getDirection();
  }
  
  packageData.structure.re1_dir     = direction1;
  packageData.structure.re1_up      = !mcp2.digitalRead(rotary1_4);
  packageData.structure.re1_down    = !mcp2.digitalRead(rotary1_2);
  packageData.structure.re1_left    = !mcp2.digitalRead(rotary1_3);
  packageData.structure.re1_right   = !mcp2.digitalRead(rotary1_1);
  packageData.structure.re1_center  = !mcp2.digitalRead(rotary1_5);
}

void joysticksSetData() {
  //Joystick AutoCalibration

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  j1xMiddle = j1xMiddle > 0 ? j1xMiddle : adc0;
  j1yMiddle = j1yMiddle > 0 ? j1yMiddle : adc1;
  
  j2xMiddle = j2xMiddle > 0 ? j2xMiddle : adc2;
  j2yMiddle = j2yMiddle > 0 ? j2yMiddle : adc3;

  // Right Joystick
  // Right - Left
  adc0_map = map(adc0, 0, joystickMaxValue, 0, 255);

  // Top - Bottom
  adc1_map = map(adc1, 0, joystickMaxValue, 0, 255);

  // Left Joystick
  // Right - Left
  adc2_map = map(adc2, 0, joystickMaxValue, 0, 255);

  // Top - Bottom
  adc3_map = map(adc3, 0, joystickMaxValue, 0, 255);

  // Left Joystick
  packageData.structure.j1x = (adc2 > j1xMiddle + joystickDiffValue || adc2 < j1xMiddle - joystickDiffValue || adc2 < 0 ) ? adc2_map : 127; // up-down
  packageData.structure.j1y = (adc3 > j1yMiddle + joystickDiffValue || adc3 < j1yMiddle - joystickDiffValue || adc3 < 0 ) ? adc3_map : 127; // left-right

  // Right Joystick
  packageData.structure.j2x = (adc0 > j2xMiddle + joystickDiffValue || adc0 < j2xMiddle - joystickDiffValue || adc0 < 0 ) ? adc0_map : 127; // up-down
  packageData.structure.j2y = (adc1 > j2yMiddle + joystickDiffValue || adc1 < j2yMiddle - joystickDiffValue || adc1 < 0 ) ? adc1_map : 127; // left-right
}
