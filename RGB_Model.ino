//Project : RGBModel
//Author : Joshua Dolgin
//Date  : 2018/11/16
//Status : Not Working
//Reference :
#include <TimerOne.h>
uint8_t groundPin = 4;
uint8_t number[] = {3, 5, 6};
uint8_t level[] = {16, 2, 255};
uint8_t numElements = sizeof(number);
uint8_t index = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(groundPin, OUTPUT); //geound the CC
  digitalWrite(groundPin, LOW);
  for (uint8_t i = 0; i < numElements; i++) {
    pinMode(number[i], OUTPUT);
  }

  Timer1.attachInterrupt(parallelArrays);
}

void parallelArrays() {
  analogWrite(number[index], 0);
  index = index + 1 % numElements;
  analogWrite(number[index], level[index]);
}

void loop() {}
