//Project : To measure the distance using an IR motion sensor and displaying
//it on a bargrapg using a 595 shift register IC
//Author : Joshua Dolgin
//Date  : 2018/10/27
//Status : Working
#include <SharpIR.h>//Includes the Sharp infared sensor library
#define model 430 //Defines the model of infared sensor
uint8_t latchPin = 9; //Pin connected to ST_CP (latch) of 74HC595
uint8_t clockPin = 10; //Pin connected to SH_CP (clock) of 74HC595
uint8_t dataPin = 8; //Pin connected to DS (data) of 74HC595
uint8_t infaredSensor = A0; //Uses 8 bit unsigned integer to rename pin A0
SharpIR SharpIR(infaredSensor, 430); //Measures the distance away from the sensor
//Creates an array of binary values
uint8_t digitMap[] = {0b11111111, 0b01111111, 0b00111111, 0b00011111,
                      0b000001111, 0b00000111, 0b00000011, 0b00000001
                     };
void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(dataPin, OUTPUT); //Sets dataPin to OUTPUT
  pinMode(clockPin, OUTPUT);//Sets clockPin to OUTPUT
  pinMode(latchPin, OUTPUT);//Sets latchPin to OUTPUT
}
void loop() {
  uint8_t dis = SharpIR.distance(); // this returns the distance to the object you're measuring
  dis = constrain(dis, 4, 30); //Constrains the value between 4 and 30
  Serial.println("Average distance in centimetres");
  Serial.println(dis); //Prints the average distance of centimetres
  dis = map(dis, 4, 30, 8, 1); //Maps the value between 4 and 30 to an integer between 0 and 8
  Serial.println("Amount of LED's");
  Serial.println(dis); //Prints the amount of LEDs that should be lit up
  for (uint8_t j = 0; j < dis; j++) {
    digitalWrite(latchPin, LOW);  //ground latchPin and hold low for as long as you are transmitting
    shiftOut(dataPin, clockPin, MSBFIRST, digitMap[j]);
  }
  digitalWrite(latchPin, HIGH);//Returns the latch pin to high
  delay(1000);
}
