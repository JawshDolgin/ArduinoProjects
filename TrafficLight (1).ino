//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define COUNT 1000
uint8_t LED[] = { 0, 1, 2 };
uint8_t numLED = sizeof(LED);

void setup() {
  for (uint8_t x = 0; x < numLED; x++) {
    pinMode(LED[x], OUTPUT);
  }
}

void loop() {
  for (uint8_t i = 0; i < numLED; i++) {
    digitalWrite(LED[i], HIGH);
    delay(COUNT);
    digitalWrite(LED[i], LOW);
  }
}
