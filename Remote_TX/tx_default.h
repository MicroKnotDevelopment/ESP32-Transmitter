/**
 * tx_default.h
 * set the current default values
 */

void defaultValues() {
  // J1
  packageData.structure.j1x = 127; // left-right
  packageData.structure.j1y = 127; // up-down

  // J2
  packageData.structure.j2x = 127; // left-right
  packageData.structure.j2y = 127; // up-down

  // Pots
  packageData.structure.p1 = 0;
  packageData.structure.p2 = 0;
  packageData.structure.p3 = 0;
  packageData.structure.p4 = 0;
  packageData.structure.p5 = 0;
  packageData.structure.p6 = 0;
  packageData.structure.p1s = 0;
  packageData.structure.p2s = 0;
  packageData.structure.p3s = 0;
  packageData.structure.p4s = 0;
  packageData.structure.p5s = 0;
  packageData.structure.p6s = 0;

  // Switches
  packageData.structure.s1 = 0;
  packageData.structure.s2 = 0;
  packageData.structure.s3 = 0;
  packageData.structure.s4 = 0;
  packageData.structure.s5 = 0;

  // Ano Rotary Encoder - Left
  packageData.structure.re1_up = 0;
  packageData.structure.re1_down = 0;
  packageData.structure.re1_left = 0;
  packageData.structure.re1_right = 0;
  packageData.structure.re1_center = 0;
  packageData.structure.re1_dir = 0;

  // Ano Rotary Encoder - Right
  packageData.structure.re2_up = 0;
  packageData.structure.re2_down = 0;
  packageData.structure.re2_left = 0;
  packageData.structure.re2_right = 0;
  packageData.structure.re2_center = 0;
  packageData.structure.re2_dir = 0;
}
