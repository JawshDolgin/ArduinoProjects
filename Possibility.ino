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
uint8_t colData [] = {0x00, 0x81, 0xC3, 0xE7, 0xFF}; // with both colData and rowData = 0x01,
uint8_t rowData [] = {0x00, 0x81, 0xC3, 0xE7, 0xFF}; //...only the top left LED should light up
uint8_t j = 0;

void setup() {
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);     //
}

void loop() {
  j = j == 4 ? j = 0 : j + 1;
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, colData[j]);
  shiftOut(data, clk, LSBFIRST, rowData[j]);
  digitalWrite(latch, HIGH);
  delay(100);
}
