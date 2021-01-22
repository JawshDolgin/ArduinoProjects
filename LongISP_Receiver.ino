//Project:
//Author:
//Date: YY/MM/DD
//Status
#include <RF24.h>
RF24 radio(9, 10);              //CE (Chip Enable/Disable), CSN(SS)
byte addresses[][6] = {"1Node", "2Node"};
#define CHANNEL 20
uint8_t in1 = 2;
uint8_t in2 = 3;
uint8_t in3 = 4;
uint8_t in4 = 5;
//uint8_t ebA = A0;
//uint8_t ebB = A1;
uint8_t rLed = A2;
uint8_t gLed = A3;
uint8_t bLed = A4 ;
boolean redState = 0;
boolean blueState = 0;
boolean greenState = 0;
uint16_t xVal = 0;
uint16_t yVal = 0;


void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
//  pinMode(ebA, OUTPUT);
//  pinMode(ebB, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
  radio.begin();                          //invoke the radio object
  radio.setPALevel(RF24_PA_MAX);          //close range so minimum power sufficient
  radio.setChannel(CHANNEL);              //Tx and Rx communication on same channel  //https://tmrh20.github.io/RF24/classRF24.html#af2e409e62d49a23e372a70b904ae30e1
  radio.openWritingPipe(addresses[1]);    //select ONE addresses to write to
  radio.openReadingPipe(1, addresses[0]); //receiver and transmit are reversed
  radio.startListening();
}

void goForward() {
  //Set motor A to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //Set motor B to forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void goBackward() {
  //Set motor A to backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //Set motor B to backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  //Set motor A to backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //Set motor B to forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
//  analogWrite(ebA, 180);
//  analogWrite(ebB, 180);
}

void turnRight() {
  //Set motor A to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //Set motor B to backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
//  analogWrite(ebA, 180);
//  analogWrite(ebB, 180);
}

void loop()
{
  if (radio.available()) {
    radio.read(&redState, sizeof(redState));
    radio.read(&blueState, sizeof(blueState));
    radio.read(&greenState, sizeof(greenState));
    radio.read(&xVal, sizeof(xVal));
    delay(10);
    radio.read(&yVal, sizeof(yVal));
  }
  if (redState) {
    digitalWrite(rLed, HIGH);
  } else
  {
    digitalWrite(rLed, LOW);
  }
  if (blueState) {
    digitalWrite(bLed, HIGH);
  } else
  {
    digitalWrite(bLed, LOW);
  }
  if (greenState) {
    digitalWrite(gLed, HIGH);
  } else
  {
    digitalWrite(gLed, LOW);
  }
  while(xVal>800){
    turnRight();
  }
  while(xVal<300){
    turnLeft();
  }
  while(yVal>800){
    goForward(); 
  }
  while(yVal<300){
    goBackward();
  }
}
