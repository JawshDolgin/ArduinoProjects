uint8_t data = 11;        // DA: SER IN (Serial Input)
uint8_t clk = 10;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 9;       // LA: RCK (Register Clock)
uint8_t tPose [] = { 0x18, 0x18, 0xFF, 0x3C, 0x3C, 0x3C, 0x24, 0x24};
uint8_t row = 0;

void setup() {
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);     //
}

void loop() {
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, tPose[row]);
  shiftOut(data, clk, LSBFIRST, 1 << row);
  digitalWrite(latch, HIGH);
//  delay(100);
  row = row < 8 ? row + 1 : 0;
}
