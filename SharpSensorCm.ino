//Project :
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :

#include <SharpIR.h>
#define model 430
//Pin connected to ST_CP (latch) of 74HC595
//uint8_t latchPin = 9;
//Pin connected to SH_CP (clock) of 74HC595
//uint8_t clockPin = 10;
//Pin connected to DS (data) of 74HC595
//uint8_t dataPin = 8;
uint8_t ir = A0;
SharpIR SharpIR(ir, 430);
//uint8_t digitMap[] = {0b00000001, 0b00000011, 0b00000111, 0b000001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111};
//uint8_t numElements = sizeof(digitMap);


void setup() {
  Serial.begin(9600);
  while (!Serial);
//  pinMode(dataPin, OUTPUT);
//  pinMode(clockPin, OUTPUT);
//  pinMode(latchPin, OUTPUT);

}

void loop() {
  uint8_t dis = SharpIR.distance(); // this returns the distance to the object you're measuring
  Serial.println("Average distance in centimetres");  // returns it to the serial monitor
  Serial.println(dis);
  dis = constrain(dis, 4, 30);
  dis = map(dis, 4, 30, 1, 8);
  Serial.println("Amount of LED's");  // returns it to the serial monitor
  Serial.println(dis);
//  for (uint8_t j = 0; j < dis; j++) {
//    //ground latchPin and hold low for as long as you are transmitting
//    digitalWrite(latchPin, LOW);
//    shiftOut(dataPin, clockPin, MSBFIRST, digitMap[j]);
//    //return the latch pin high to signal chip that it
//    //no longer needs to listen for information
//    delay(500);
//  }
//  digitalWrite(latchPin, HIGH);
}
