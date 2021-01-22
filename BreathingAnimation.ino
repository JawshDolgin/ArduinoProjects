//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define clk 10
#define data 8
#define latch 7
#define OE 6
#define SPEED 5
uint8_t delta = 1;
uint8_t value [] = { 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
uint8_t animation = 0;
uint8_t brightness = 1;

void setup() {
  for (uint8_t i = clk; i > OE; i--) {
    pinMode(i, OUTPUT);
  }
  changeAnimation();
}

void changeAnimation() {
  digitalWrite(latch, LOW);
  shiftOut(data, clk, MSBFIRST, value[animation]);
  digitalWrite(latch, HIGH);
}

void loop() {  
  delay(SPEED);
  analogWrite(OE, brightness);
  brightness = brightness + delta;
  if (brightness == 255 || brightness == 0)
  {
    delta = -delta;
  }
  if (brightness == 0) {
    animation == 7 ? animation = 0 : animation++;
    changeAnimation();
    brightness++;
  }
}
