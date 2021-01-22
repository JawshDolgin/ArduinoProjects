


uint8_t latchPin = 9; //Pin connected to ST_CP (latch) of 74HC595
uint8_t clockPin = 10; //Pin connected to SH_CP (clock) of 74HC595
uint8_t dataPin = 8;
uint8_t trigPin = 7;
uint8_t echoPin = 8;
long duration;
uint16_t distance;
// defines variables
uint8_t digitMap[] = {0b11111111, 0b01111111, 0b00111111, 0b00011111,
                      0b000001111, 0b00000111, 0b00000011, 0b00000001
                     };

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(dataPin, OUTPUT); //Sets dataPin to OUTPUT
  pinMode(clockPin, OUTPUT);//Sets clockPin to OUTPUT
  pinMode(latchPin, OUTPUT);//Sets latchPin to OUTPUT
  Serial.begin(9600);
}

void loop() {

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
  uint8_t dis = map(distance, 4, 30, 1, 8);
  for (uint8_t j = 0; j < dis; j++) {
    digitalWrite(latchPin, LOW);  //ground latchPin and hold low for as long as you are transmitting
    shiftOut(dataPin, clockPin, MSBFIRST, digitMap[j]);
  }
  digitalWrite(latchPin, HIGH);//Returns the latch pin to high
  delay(1000);

}
