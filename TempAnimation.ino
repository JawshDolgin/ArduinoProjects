#define clk 10
#define data 8
#define latch 7
#define OE 6
#define SPEED 5
uint16_t temp = 0;
uint8_t value [] = { 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
void setup() {
  for (uint8_t i = clk; i > OE; i--) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
 temp = analogRead(A0);
 temp = constrain(temp, 140, 170);
 digitalWrite(latch, LOW);
 shiftOut(data, clk, LSBFIRST, temp);
 digitalWrite(latch, HIGH);
 delay(50);
}
