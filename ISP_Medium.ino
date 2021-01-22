dt//Project : Smart trash can
//Author : Joshua Dolgin
//Date  : 2019/02/21
//Status : Working
#include <Servo.h> //includes servo library
#include <SharpIR.h>//Includes the Sharp infared sensor library
#define model 430 //Defines the model of infared sensor
#define ENDROTATION 0 //defines a variable to end rotation
#define STARTROTATION 90//defines variable at which to start rotation
Servo myservo;
uint8_t latchPin = 4; //Pin connected to ST_CP (latch) of 74HC595
uint8_t clockPin = 5; //Pin connected to SH_CP (clock) of 74HC595
uint8_t dataPin = 3; //Pin connected to DS (data) of 74HC595
uint8_t pos = 0; // position of the servo
uint8_t trigPin = 7; // trigger pin on HC-SRO4
uint8_t echoPin = 8; // echo pin on HC-SRO4
uint8_t infaredSensor = A0; //Uses 8 bit unsigned integer to rename pin A0
SharpIR SharpIR(infaredSensor, 430); //Measures the distance away from the sensor
//Creates an array of binary values
long duration; // creates a variable to measure duration
uint16_t distance; // creates an unsigned 16 bit integer to measure distance
uint8_t digitMap[] = {0b11111111, 0b00111111, 0b000001111, 0b00000011}; // creates an array

void setup() {
  Serial.begin(9600);
  while (!Serial);
  myservo.attach(9); // attach servo to pin 9
  pinMode(trigPin, OUTPUT); // sets trigger pin to OUTPUT
  pinMode(echoPin, INPUT); // sets echo pin to INPUT
  pinMode(dataPin, OUTPUT); //Sets dataPin to OUTPUT
  pinMode(clockPin, OUTPUT);//Sets clockPin to OUTPUT
  pinMode(latchPin, OUTPUT);//Sets latchPin to OUTPUT
}

void lift() {
  delay(2000); // delay 2 seconds
  myservo.write(ENDROTATION); // write the servo to the end of rotation
  delay(1000); // delay 1 second
  myservo.write(STARTROTATION); // write the servo to start position
}

void checkDepth() {
  uint8_t dis = SharpIR.distance(); // this returns the distance to the object you're measuring
  dis = constrain(dis, 4, 8); //Constrains the value between 4 and 30
  Serial.println("Internal Distance");
  Serial.println(dis); //Prints the average distance of centimetres
  dis = map(dis, 4, 8, 1, 4); //Maps the value between 4 and 30 to an integer between 0 and 8
  for (uint8_t j = 0; j < dis; j++) {
    digitalWrite(latchPin, LOW);  //ground latchPin and hold low for as long as you are transmitting
    shiftOut(dataPin, clockPin, MSBFIRST, digitMap[j]); // shifts out the value in the array at cell "j"
  }
  digitalWrite(latchPin, HIGH);//Returns the latch pin to high
  delay(1000); //delay 1 second
}

void scanTray() {
  myservo.write(STARTROTATION); //puts the servo to start of rotation
  digitalWrite(trigPin, LOW); // writes the trigger pin low
  delayMicroseconds(2); //delay 2 microsecond
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); //writes the trig pin high
  delayMicroseconds(10); // delay 10 microseconds
  digitalWrite(trigPin, LOW); // write trigger pin low
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  distance = constrain(distance, 0, 30);
  Serial.print(" External Distance ");
  Serial.println(distance);
  if (distance <= 5) {
    lift(); //execute lift function
    checkDepth(); // check depth
  }
}

void loop() {
  scanTray(); // execute the scan tray function
  checkDepth(); // execute the check depth function
}
