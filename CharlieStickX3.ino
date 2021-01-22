//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define PinCon 0
#define PinState 1
#define LED_COUNT 12
#define numPin 4
uint8_t stick[] = {10, 11, 12, 13, 2, 3, 4, 5, A3, A2, A1, A0};
int configuration[LED_COUNT][2][4] = {
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // 1
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, // 2
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // 3
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // 4
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // 5
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // 6
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // 7
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW } }, // 8
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // 9
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // 10
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // 11
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW } }  // 12
};

void setup() {
}

void loop() {
  for (uint8_t l = 0; l < LED_COUNT; l++) {
    for (uint8_t i = 0; i < numPin; i++) {
      pinMode(stick[i], configuration[l][PinCon][i]);
      digitalWrite(stick[i], configuration[l][PinState][i]);
      pinMode(stick[i + (1 << 2)], configuration[l][PinCon][i]);
      digitalWrite(stick[i + (1 << 2)], configuration[l][PinState][i]);
       pinMode(stick[i + (1 << 3)], configuration[l][PinCon][i]);
      digitalWrite(stick[i + (1 << 3)], configuration[l][PinState][i]);
    }
    delay(100);
  }
  for (uint8_t l = 10; l > 0; l--) {
    for (uint8_t i = 0; i < numPin; i++) {
      pinMode(stick[i], configuration[l][PinCon][i]);
      digitalWrite(stick[i], configuration[l][PinState][i]);
      pinMode(stick[i + (1 << 2)], configuration[l][PinCon][i]);
      digitalWrite(stick[i + (1 << 2)], configuration[l][PinState][i]);
      pinMode(stick[i + (1 << 3)], configuration[l][PinCon][i]);
      digitalWrite(stick[i + (1 << 3)], configuration[l][PinState][i]);
    }
    delay(100);
  }
}
