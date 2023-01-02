/**
 * tx_read.h
 */

void potentiometersSetData() {
  /*
    Potentiometer Values
  */
  pot1Read = analogRead(POTENTIOMETER_PIN1);
  pot2Read = analogRead(POTENTIOMETER_PIN1);
  pot3Read = analogRead(POTENTIOMETER_PIN1);
  pot4Read = analogRead(POTENTIOMETER_PIN1);
  pot5Read = analogRead(POTENTIOMETER_PIN1);
  pot6Read = analogRead(POTENTIOMETER_PIN1);

  pot1LastValue = ((pot1LastValue > pot1Read + potSensitivityValue) || (pot1LastValue < pot1Read - potSensitivityValue)) ? pot1Read : pot1LastValue;
  pot2LastValue = ((pot2LastValue > pot2Read + potSensitivityValue) || (pot2LastValue < pot2Read - potSensitivityValue)) ? pot2Read : pot2LastValue;
  pot3LastValue = ((pot3LastValue > pot3Read + potSensitivityValue) || (pot3LastValue < pot3Read - potSensitivityValue)) ? pot3Read : pot3LastValue;
  pot4LastValue = ((pot4LastValue > pot4Read + potSensitivityValue) || (pot4LastValue < pot4Read - potSensitivityValue)) ? pot4Read : pot4LastValue;
  pot5LastValue = ((pot5LastValue > pot5Read + potSensitivityValue) || (pot5LastValue < pot5Read - potSensitivityValue)) ? pot5Read : pot5LastValue;
  pot6LastValue = ((pot6LastValue > pot6Read + potSensitivityValue) || (pot6LastValue < pot6Read - potSensitivityValue)) ? pot6Read : pot6LastValue;

  packageData.structure.p1 = map(pot1LastValue, 0, 4095, 255, 0);
  packageData.structure.p2 = map(pot2LastValue, 0, 4095, 255, 0);
  packageData.structure.p3 = map(pot3LastValue, 0, 4095, 255, 0);
  packageData.structure.p4 = map(pot4LastValue, 0, 4095, 255, 0);
  packageData.structure.p5 = map(pot5LastValue, 0, 4095, 0, 255);
  packageData.structure.p6 = map(pot6LastValue, 0, 4095, 255, 0);

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
  static int pos = 0;
  int encoder_direction = 0;

  packageData.structure.re2_up      = !mcp1.digitalRead(rotary2_2);
  packageData.structure.re2_down    = !mcp1.digitalRead(rotary2_4);
  packageData.structure.re2_left    = !mcp1.digitalRead(rotary2_3);
  packageData.structure.re2_right   = !mcp1.digitalRead(rotary2_5);
  packageData.structure.re2_center  = !mcp1.digitalRead(rotary2_1);

  encoder2->tick(
    mcp1.digitalRead(rotary2_enc_1),
    mcp1.digitalRead(rotary2_enc_2)
  );

  int newPos = encoder2->getPosition();

  packageData.structure.re2_dir = 0;
  if (pos != newPos) {
    pos = newPos;
    encoder_direction = (int)encoder2->getDirection();
  }
  packageData.structure.re2_dir = encoder_direction;
}

void anoRotaryEncoder1SetData() {
  static int pos = 0;
  int encoder_direction = 0;

  encoder1->tick(
    mcp2.digitalRead(rotary1_enc_1),
    mcp2.digitalRead(rotary1_enc_2)
  );
  int newPos = encoder1->getPosition();

  packageData.structure.re1_dir = 0;
  if (pos != newPos) {
    pos = newPos;
    encoder_direction = (int)encoder1->getDirection();
  }
  
  packageData.structure.re1_dir     = encoder_direction;
  packageData.structure.re1_up      = !mcp2.digitalRead(rotary1_4);
  packageData.structure.re1_down    = !mcp2.digitalRead(rotary1_2);
  packageData.structure.re1_left    = !mcp2.digitalRead(rotary1_3);
  packageData.structure.re1_right   = !mcp2.digitalRead(rotary1_1);
  packageData.structure.re1_center  = !mcp2.digitalRead(rotary1_5);
}

void joysticksSetData() {
  //Joystick center calibration
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
  packageData.structure.j1x = (adc2 > j1xMiddle + joystickSensitivityValue || adc2 < j1xMiddle - joystickSensitivityValue || adc2 < 0 ) ? adc2_map : 127; // up-down
  packageData.structure.j1y = (adc3 > j1yMiddle + joystickSensitivityValue || adc3 < j1yMiddle - joystickSensitivityValue || adc3 < 0 ) ? adc3_map : 127; // left-right

  // Right Joystick
  packageData.structure.j2x = (adc0 > j2xMiddle + joystickSensitivityValue || adc0 < j2xMiddle - joystickSensitivityValue || adc0 < 0 ) ? adc0_map : 127; // up-down
  packageData.structure.j2y = (adc1 > j2yMiddle + joystickSensitivityValue || adc1 < j2yMiddle - joystickSensitivityValue || adc1 < 0 ) ? adc1_map : 127; // left-right
}
