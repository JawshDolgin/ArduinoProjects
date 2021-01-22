#define clk 10
#define data 8
#define latch 7
#define OE 6
#define SPEED 5
#define yVal 1
#define xVal 0
#define BUTTON 3
#define COUNT 2000
uint8_t LED[] = { 3, 4, 5 };
uint8_t numLED = sizeof(LED);
int16_t temp = 0;
uint8_t value [] = { 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
uint8_t animation = 0;
uint8_t light = 1;
uint8_t delta = 1;
uint16_t pos = 0;
uint16_t brightness = 0;
uint8_t increment = 0;
uint8_t whatAnimation = 0;

void setup() {
  for (uint8_t i = clk; i > OE; i--) {
    pinMode(i, OUTPUT);
  }
  for (uint8_t x = 0; x < numLED; x++) {
    pinMode(LED[x], OUTPUT);
  }
}
void animation1() { //Breathing sketch Sketch
  delay(SPEED);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, MSBFIRST, value[animation]);
  digitalWrite(latch, HIGH);
  analogWrite(OE, light);
  light = light + delta;
  if (light == 255 || light == 0)
  {
    delta = -delta;
  }
  if (light == 0) {
    animation == 7 ? animation = 0 : animation++;
    brightness++;
  }
}

void adjustBrightness() {
  brightness = analogRead(yVal);
  analogWrite(OE, brightness);
}

void animation2() {
  for (uint8_t i = 0; i < numLED; i++) {
    digitalWrite(LED[i], HIGH);
    delay(COUNT);
    digitalWrite(LED[i], LOW);
  }
}

void animation3() {
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


void loop() {
  if (analogRead(xVal) > 900) {
    whatAnimation++;
  }
  switch (whatAnimation % 2) {
    case 0:
      animation1();
      break;
    case 1:
      animation2();
      break;
    case 2:
      animation3();
      break;
  }
}
