// PROJECT  :DataAveraging
// PURPOSE  :Demonstrates a technique for stabilizing data streams as in sensor readings
// COURSE   :ICS4U
// AUTHOR   :C. D'Arcy
// DATE     :2020 01 24  (in class)
// MCU      :Independent
// STATUS   :Working

#define NUMELEMENTS 50        //decide on size of history list...
uint8_t history[NUMELEMENTS]; //history list of elelemnts in the data stream
#define VCC 1<<PC0
#define GND 1<<PC2
uint32_t total = 0;;

void setup() {
  Serial.begin(9600);
  DDRC |= VCC | GND;
  PORTC |= VCC;
}

// this function updates the history list with the latest readings
// and calculates (and returns) the most recent average of the data set
void getAverage() {
  total = 0;     //make sure the total is large enough
  for (uint8_t i = 1; i < NUMELEMENTS; i++) {
    total = total + analogRead(A1);
  }
  total = total/(NUMELEMENTS-1);;
}

void loop() {
getAverage();
Serial.println(total);
}
