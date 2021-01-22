//Project : 
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :
#include <RF24.h>
RF24 radio(9, 10);              //CE (Chip Enable/Disable), CSN(SS)
byte addresses[][6] = {"1Node", "2Node"};
#define CHANNEL 20

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  radio.begin();                          //invoke the radio object
  radio.setPALevel(RF24_PA_MIN);          //close range so minimum power sufficient
  radio.setChannel(CHANNEL);              //Tx and Rx communication on same channel
  //https://tmrh20.github.io/RF24/classRF24.html#af2e409e62d49a23e372a70b904ae30e1
  radio.openWritingPipe(addresses[0]);    //Transmit assumes these pipes
  radio.openReadingPipe(1, addresses[1]);
  radio.stopListening();
}

void loop() {
uint16_t yVal = analogRead(A0);
uint16_t xVal= analogRead(A1);
Serial.print("Your Y value is:");
Serial.print(yVal);
Serial.print("   Your X value is:");
Serial.println(xVal);
//uint16_t ledX = map(xVal, 0, 1023, 0, 255);
//uint16_t ledY = map(yVal, 0, 1023, 0, 255);
//Serial.print(ledX);
//Serial.println(ledY);
//analogWrite(11, ledX);
//analogWrite(10, ledY);
}
