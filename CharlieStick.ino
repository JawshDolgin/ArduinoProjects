//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define PinCon 0 
#define PinState 1
#define LED_COUNT 12 
#define numPin 4 //How many pins are used for the stick
uint8_t stick[] = {10, 11, 12, 13}; //What pins are being used
uint8_t configuration[LED_COUNT][2][4] = {
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
  for (uint8_t l = 0; l < LED_COUNT; l++) { //Runs as many times as there are LED's
    for (uint8_t i = 0; i < numPin; i++) { //Runs as many times as the pins on the Matrix
      pinMode(stick[i], configuration[l][PinCon][i]); //Sets the pin configuration
      digitalWrite(stick[i], configuration[l][PinState][i]); //Sets the pin state 
    }
    delay(100);
  }
  for (uint8_t l = 11; l > 0; l--) { //Counts back down
    for (uint8_t i = 0; i < numPin; i++) {
      pinMode(stick[i], configuration[l][PinCon][i]); //Sets pin configuration 
      digitalWrite(stick[i], configuration[l][PinState][i]); //Sets pin state
    }
    delay(100);
  }
}
