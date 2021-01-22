uint8_t clk  = 10;
uint8_t data = 8;
uint8_t latch = 7;
uint8_t VCC = 1;
uint8_t tempPin = A0;
uint16_t tempurature = 0;


void setup() {
  pinMode(clk, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
}

void loop() {
tempurature = analogRead(tempPin);
tempurature = constrain(tempurature, 140, 172);
tempurature = (tempurature-140)>>2;
digitalWrite(latch, LOW);
shiftOut(data, clk, MSBFIRST, (1<<tempurature)-1);
digitalWrite(latch, HIGH);
}
