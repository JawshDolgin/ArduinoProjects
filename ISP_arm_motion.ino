
#include <Servo.h>

Servo myservo;
uint8_t pos = 0;
uint8_t trigPin = 7;
uint8_t echoPin = 8;
// defines variables
long duration;
uint16_t distance;
void setup() {
  myservo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void lift(){
delay(1000);
myservo.write(90);
delay(1000);
myservo.write(0);
}

void loop() {
  // Clears the trigPin
  myservo.write(0);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  distance = constrain(distance, 0, 30);
  Serial.print("Distance: ");
  Serial.println(distance);
    if(distance <= 5){
      lift();
    }
//  delay(1000);
//
//  pos = map(distance, 0, 30, 0, 180);
//  myservo.write(pos);
}
