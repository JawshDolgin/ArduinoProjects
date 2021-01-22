// PROJECT  :ShiftOut7SegmentHexAnimation
// PURPOSE  :Introduction to the 595 Shift Register and Hex Animation
// DEVICE   :Arduino+74HC585
// AUTHOR   :C. D'Arcy
// DATE     :2018 10 24
// uC       :328
// COURSE   :ICS3U
// STATUS   :Not (Yet) Working

//Pin connected to ST_CP (latch) of 74HC595
uint8_t latchPin = 9;
//Pin connected to SH_CP (clock) of 74HC595
uint8_t clockPin = 10;
//Pin connected to DS (data) of 74HC595
uint8_t dataPin = 8;

uint8_t digitMap[] = {0b11111111, 0b01111111, 0b00111111, 0b00011111, 0b000001111, 0b00000111, 0b00000011, 0b00000001, 0b00000000};
uint8_t numElements = sizeof(digitMap);
uint8_t digit2Map[] = {0b00000000, 0b10000001, 0b11000011, 0b11100111, 0b11111111};
uint8_t num2Elements = sizeof(digit2Map);


#define DURATION 500      //define the speed of the animation

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  for (uint8_t j = 0; j < numElements; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digitMap[j]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(DURATION);
  }
  for (uint8_t j = numElements; j > 0; j--) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digitMap[j]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(DURATION);
  }
  for (uint8_t j = 0; j < num2Elements; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit2Map[j]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(DURATION);
  }
  for (uint8_t j = num2Elements; j > 0; j--) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit2Map[j]);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(DURATION);
  }


}
