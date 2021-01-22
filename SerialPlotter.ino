//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
uint8_t GND = A0;
uint8_t VCC = A1;
uint8_t joyY = A2;
uint8_t joyX = A3;
uint8_t numValue = 10;



void setup() {
  Serial.begin(9600);
  pinMode(VCC, OUTPUT);
  pinMode(GND, OUTPUT);
  digitalWrite(VCC, HIGH);
  digitalWrite(GND, LOW);

}

void loop() {
  uint32_t xAvg = 0;
  uint32_t yAvg = 0;
  for (uint8_t j = 0; j < numValue; j++) {
    xAvg = xAvg + analogRead(joyX);
    yAvg = yAvg + analogRead(joyY);
  }
xAvg = xAvg/numValue;
yAvg = yAvg/numValue;
Serial.print(xAvg);
Serial.print("  ");
Serial.println(yAvg);
}
