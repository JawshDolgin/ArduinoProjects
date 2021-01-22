//Project: Receiver code for Bi-Wheeled rover
//Author: Josh Dolgin
//Date: 2019/06/26
//Status: Working
#include <RF24.h>
RF24 radio(9, 10);              //CE (Chip Enable/Disable), CSN(SS)
byte addresses[][6] = {"1Node", "2Node"};
#define CHANNEL 14 // 2.414 GHz
uint8_t in1 = 6;
uint8_t in2 = 5;
uint8_t in3 = 4;
uint8_t in4 = 3; // Motor control pins
uint8_t rLed = A0;
uint8_t bLed = A1;
uint8_t gLed = A2; // LED pins

struct package // Data structure to receive
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
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  radio.begin();                          //invoke the radio object
  radio.setPALevel(RF24_PA_MIN);          //close range so minimum power sufficient
  radio.setChannel(CHANNEL);              //Tx and Rx communication on same channel  //https://tmrh20.github.io/RF24/classRF24.html#af2e409e62d49a23e372a70b904ae30e1
  radio.openWritingPipe(addresses[1]);    //select ONE addresses to write to
  radio.openReadingPipe(1, addresses[0]); //receiver and transmit are reversed
  radio.startListening(); // Receiver
}
void stationary() { //Stay still
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void goForward() { 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void goBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void loop() {
  if (radio.available())
  {
    while (radio.available())
    {
      radio.read(&data, sizeof(data) ); // Read the data
    }
    Serial.print(data.xVal);
    Serial.print("  ");
    Serial.print(data.yVal);
    Serial.print("  ");
    Serial.print(data.R);
    Serial.print("  ");
    Serial.print(data.B);
    Serial.print("  ");
    Serial.println(data.G); // Print the data on the Serial monitor
  }
  if (data.xVal < 150 && data.xVal > 100 && data.yVal < 150 && data.yVal > 100) { 
// if the joystick is in the middle
    Serial.println("Nothing");
    stationary();
  }
  if (data.xVal < 150 && data.xVal > 100) {
    if (data.yVal > 151) {
      Serial.println("FORWARD");
      goForward();
    }
    if (data.yVal < 99) {
      Serial.println("BACKWARD");
      goBackward();
    }
  }
  if (data.xVal > 151) {
    Serial.println("LEFT");
    turnRight();
  } else if (data.xVal < 99) {
    Serial.println("RIGHT");
    turnLeft();
  }
  digitalWrite(rLed, ~data.R); //inversion of the Boolean value
  digitalWrite(bLed, ~data.B);
  digitalWrite(gLed, ~data.G); 
  delay(100);
}
