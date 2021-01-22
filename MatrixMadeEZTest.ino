// PROJECT  :MatrixMadeEZ
// PURPOSE  :Demo program of the MatrixMadeEZ Device (original design by H. Reed)
// AUTHOR   :C. D'Arcy
// DATE     :2018 09 15
// uC       :328
// STATUS   :Working
// REFERENCE:https://cdn-shop.adafruit.com/datasheets/1079datasheet.pdf
// NOTES    :Place a Voltage Divider (pot?) on the DM pin for dimming (Knight Light?)
uint8_t vcc = 4;
uint8_t data = 3;        // DA: SER IN (Serial Input)
uint8_t clk = 2;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 1;       // LA: RCK (Register Clock)
uint8_t colData = 0x01;   // with both colData and rowData = 0x01,
uint8_t rowData = 0x01;  // ...only the top left LED should light up

void setup() {
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);     //
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc, HIGH);
}

void loop() {
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, colData);
  shiftOut(data, clk, LSBFIRST, rowData);
  digitalWrite(latch, HIGH);
  delay(100);
  rowData = rowData == 0x80 ? rowData = 0x01 : rowData << 1;
  colData = rowData;
}
