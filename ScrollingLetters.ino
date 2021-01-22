//Project :
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :
#include <EEPROM.h>
#include <TimerOne.h>
#define FASTEST 30000
#define SLOWEST 300000
volatile uint8_t shifts = 0;
uint8_t prevShifts = shifts = 0;
uint64_t index = 0;
uint16_t rowBuffers[8];
uint8_t dataPin = 11;
uint8_t clkPin = 10;
uint8_t latchPin = 9;
uint8_t dimPin = 8;
String message;
boolean debug = false;
boolean speedControl = true;

void setup() {
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(clkPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dimPin, OUTPUT);
  Timer1.initialize((SLOWEST + FASTEST) >> 1);
  Timer1.attachInterrupt(updateImage);
  message = "JOSH DOLGIN ACES '20";
  if (debug) Serial.println(message);
  loadBackBuffer(message.charAt(index));
}

void loadBackBuffer(uint8_t ascii) {
  uint16_t address = ascii << 3;
  for (uint8_t row = 0; row < 8; row++) {
    rowBuffers[row] |= EEPROM.read(address++) << 8;
    if (debug) Serial.println(lowByte(rowBuffers[row]), BIN);
  }
}

void updateImage (void) {
  shifts++;
}

void loop() {
  while (shifts == prevShifts) {
    for (uint8_t row = 0; row < 8; row++) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clkPin, LSBFIRST, lowByte(rowBuffers[row]));
      shiftOut(dataPin, clkPin, LSBFIRST, 1 << row);
      digitalWrite(latchPin, HIGH);
    }
  }
  prevShifts = shifts;
  if (shifts % 8 == 0) {
    index = (index + 1) % message.length();
    loadBackBuffer(message.charAt(index));
  }

  for (uint8_t row = 0; row < 8; row++)
  rowBuffers[row] >>= 1;

  if (speedControl) {
    noInterrupts();
    Timer1.setPeriod(map(analogRead(0), 0, 1024, FASTEST, SLOWEST));
    interrupts();
  }
}
