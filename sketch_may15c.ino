//Project: Transmitter Code for Bi-Whelled rover
//Author: Josh Dolgin
//Date: 2019/05/26
//Status: Working
#include <RF24.h>
RF24 radio(9, 10);              //CE (Chip Enable/Disable), CSN(SS)
byte addresses[][6] = {"1Node", "2Node"};
#define CHANNEL 14 //2.414GHz
uint8_t joyX = A0;
uint8_t joyY = A1;
uint8_t rLed = 7;
uint8_t bLed = 5;
uint8_t gLed = 6;


struct package //Create data structure
{
  uint8_t xVal = 0;
  uint8_t yVal = 0;
  boolean R = 0;
  boolean G = 0;
  boolean B = 0;
};
typedef struct package Package;
Package data;

void setup() {
  Serial.begin(9600);
  radio.begin();                          //invoke the radio object
  radio.setPALevel(RF24_PA_MIN);          //close range so minimum power sufficient
  radio.setChannel(CHANNEL);              //Tx and Rx communication on same channel
  //https://tmrh20.github.io/RF24/classRF24.html#af2e409e62d49a23e372a70b904ae30e1
  radio.openWritingPipe(addresses[0]);    //Transmit assumes these pipes
  radio.openReadingPipe(1, addresses[1]); 
  radio.stopListening(); //Transmit rather than receive
}
void loop() {
  data.xVal = analogRead(joyX) >> 2; //creates 8 bit integer rather than 10 
  data.yVal = analogRead(joyY) >> 2; //creates 8 bit integer rather than 10 
  data.R = digitalRead(rLed); //Receives R value
  data.B = digitalRead(bLed); //Receives b value
  data.G = digitalRead(gLed); //Receives g value
  radio.write(&data, sizeof(data)); //Sends the data structure 
  Serial.print(data.xVal);
  Serial.print("  ");
  Serial.print(data.yVal);
  Serial.print("  ");
  Serial.print(data.R);
  Serial.print("  ");
  Serial.print(data.B);
  Serial.print("  ");
  Serial.println(data.G); //Prints all of the data in the serial monitor
  delay(100);
}
