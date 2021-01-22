// PROJECT  :MatrixMadeEZ
// PURPOSE  :Demo program of the MatrixMadeEZ Device (original design by H. Reed)
// AUTHOR   :C. D'Arcy
// DATE     :2018 09 15
// uC       :328
// STATUS   :Working
// REFERENCE:https://cdn-shop.adafruit.com/datasheets/1079datasheet.pdf
// NOTES    :Place a Voltage Divider (pot?) on the DM pin for dimming (Knight Light?)
uint8_t data = 11;        // DA: SER IN (Serial Input)
uint8_t clk = 10;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 9;       // LA: RCK (Register Clock)
uint8_t colData [] = {0x00, 0x01, 0x03, 0x1F, 0x3F, 0x7F, 0xFF}; // with both colData and rowData = 0x01,
uint8_t rowData [] = {0x00, 0x02, 0x04, 0x08, 0x10, 0x20,0x40}; //...only the top left LED should light up
uint8_t j = 0;

void setup() {
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);     //
}

void loop() {
  j = j == 7 ? j = 0 : j + 1;
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, colData[j]);
  shiftOut(data, clk, LSBFIRST, rowData[j]);
  digitalWrite(latch, HIGH);
  delay(100);
}
