// PROJECT  :MatrixMadeEZ
// PURPOSE  :Demo program of the MatrixMadeEZ Device (original design by H. Reed)
// AUTHOR   :C. D'Arcy
// DATE     :2018 09 15
// uC       :328
// STATUS   :Working
// REFERENCE:https://cdn-shop.adafruit.com/datasheets/1079datasheet.pdf
// NOTES    :Place a Voltage Divider (pot?) on the DM pin for dimming (Knight Light?)
#include <TimerOne.h>
uint8_t data = 11;        // DA: SER IN (Serial Input)
uint8_t clk = 10;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 9;       // LA: RCK (Register Clock)
//uint8_t colData = 0x01;   // with both colData and rowData = 0x01,
//uint8_t rowData = 0x01;  // ...only the top left LED should light up
uint8_t letters[4][8] = { { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},
  { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},
  { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},
  { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}
};
uint8_t which = 0;
uint8_t row = 0;

void setup() {
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);     //
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(change);
}
void change() {
  which = (which + 1) % 4;
}


void loop() {

  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, letters[which][row]);
  shiftOut(data, clk, LSBFIRST, 1 << row);
  digitalWrite(latch, HIGH);
  row = row < 8 ? row + 1 : 0;


}
