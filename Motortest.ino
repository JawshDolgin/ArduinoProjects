//Project :
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :

//In rover
uint8_t in1 = 2;
uint8_t in2 = 3;
uint8_t in3 = 4;
uint8_t in4 = 5;
uint8_t ebA = A0;
uint8_t ebB = A1;
uint8_t rLed = A2;
uint8_t gLed = A3;
uint8_t bLed = A4 ;
uint8_t speed = 0;
//Remote
uint8_t joyX = A5;
uint8_t joyY = A6;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ebA, OUTPUT);
  pinMode(ebB, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
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
  analogWrite(ebA, 180);
  analogWrite(ebB, 180);
}

void turnRight() {
  //Set motor A to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //Set motor B to backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ebA, 180);
  analogWrite(ebB, 180);
}

void loop() {
  while (analogRead(joyX) > 550) {
    goForward();
    speed = map(analogRead(joyX), 540, 1023, 0, 255);
    analogWrite(ebA, speed);
    analogWrite(ebB, speed);
  }
  while (analogRead(joyX) < 490) {
    goBackward();
    speed = map(analogRead(joyX), 0, 490, 0, 255);
    analogWrite(ebA, speed);
    analogWrite(ebB, speed);
  }
  while (analogRead(joyY) > 900) {
    turnLeft();
  }
    while (analogRead(joyY) > 150) {
    turnRight();
  }
  
}
