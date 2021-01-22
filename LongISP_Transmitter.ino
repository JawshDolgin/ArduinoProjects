//Project:
//Author:
//Date: YY/MM/DD
//Status
#include <RF24.h>
RF24 radio(9, 10);              //CE (Chip Enable/Disable), CSN(SS)
byte addresses[][6] = {"1Node", "2Node"};
#define CHANNEL 20
uint8_t joyX = A0;
uint8_t joyY = A1;
uint8_t gLed = 6;
uint8_t rLed = 7;
uint8_t bLed = 5;

void setup() {
  // put your setup code here, to run once:
  radio.begin();                          //invoke the radio object
  radio.setPALevel(RF24_PA_MAX);          //close range so minimum power sufficient
  radio.setChannel(CHANNEL);              //Tx and Rx communication on same channel
  //https://tmrh20.github.io/RF24/classRF24.html#af2e409e62d49a23e372a70b904ae30e1
  radio.openWritingPipe(addresses[0]);    //Transmit assumes these pipes
  radio.openReadingPipe(1, addresses[1]);
  radio.stopListening();
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  pinMode(rLed, OUTPUT);
}

void loop() {
  uint8_t redState = digitalRead(rLed);
  radio.write(&redState, sizeof(redState));
  uint8_t blueState = digitalRead(bLed);
  radio.write(&blueState, sizeof(blueState));
  uint8_t greenState = digitalRead(gLed);
  radio.write(&greenState, sizeof(greenState));
  uint8_t xVal = analogRead(joyX);
  radio.write(&xVal, sizeof(joyX));
  uint8_t yVal = analogRead(joyY);
  delay(5);
  radio.write(&yVal, sizeof(joyY));
}
