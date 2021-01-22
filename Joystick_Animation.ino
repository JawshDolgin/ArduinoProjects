//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define clk 10
#define data 8
#define latch 7
#define OE 6
#define yVal 1
#define xVal 0
uint8_t value [] = { 0x01, 0x02, 0x04, 0x8, 0x10, 0x20, 0x40, 0x80};
uint8_t animation = 0;
uint16_t pos = 0;
uint16_t brightness = 0;
uint8_t increment = 0;

void setup() {
  for (uint8_t i = clk; i > OE; i--) {
    pinMode(i, OUTPUT);
  }
    pinMode(yVal, INPUT);
    pinMode(xVal, INPUT);
}

void adjustBrightness() {
  brightness = analogRead(yVal);
  analogWrite(OE, brightness);
}
void loop() {
  pos = analogRead(xVal);
  while (pos > 900) {
    for (uint8_t x = increment; x < 7; x++) {
      digitalWrite(latch, LOW);
      shiftOut(data, clk, LSBFIRST, value[x]);
      digitalWrite(latch, HIGH);
      increment = x;
      adjustBrightness();
    }
  } while (pos < 300) {
    for (uint8_t x = increment; x > 0; x--) {
      digitalWrite(latch, LOW);
      shiftOut(data, clk, LSBFIRST, value[x]);
      digitalWrite(latch, HIGH);
      increment = x;
      adjustBrightness();
    }
  }
}
