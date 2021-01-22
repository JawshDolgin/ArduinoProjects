// PROJECT  :RGBModelICC (In Class Code)
// PURPOSE  :Explore data modeling options for an RGBLED
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 11 14-22
// uC       :328
// COURSE   :ICS3U
// STATUS   :Working
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/DataModelingExercises.html
#include <TimerOne.h>
uint8_t ccPin = 4;                      //the longest lead is the common cathode lead
volatile uint8_t index = 0;             //used to index each of the leads in rotation
//Parallel Arrays                       //Model 1
uint8_t number[] = {3, 5, 6};           //pin numbers for each of the three leads
uint8_t level[] = {16, 2, 255};         //analog levels for each lead
//uint8_t numElements = sizeof(number); //autodetermine the number of leads

// Matrix structure (added duration...) //Model 2
uint8_t RGBLED[3][3] = {{3, 16, 1}, {5, 2, 2}, {6, 255, 6} };
//uint8_t numElements = sizeof(RGBLED) /sizeof(RGBLED[0]) ; //autodetermine the number of leads

// Use of structs                       //Model 2
struct LED {                            //tightest binding of realted parameters
  uint8_t number;                       //pn number
  uint8_t level;                        //PWM value
  uint8_t duration;                     //length of time to display in seconds
};
//identical syntax for initially populating the data structure 
LED device [3] = {{3, 16, 6}, {5, 2, 1}, {6, 255, 6} };
uint8_t numElements = sizeof(device) / sizeof(LED); //autodetermine the number of leads

void setup() {
  Serial.begin(9600);
  pinMode(ccPin, OUTPUT);                   //declare the CC (common cathode) pin for writing to
  digitalWrite(ccPin, LOW);                 //provide a sink for the current to flow into
  //declare all other leads to be used for output
  for (uint8_t i = 0; i < numElements; i++) {
    //pinMode(number[i], OUTPUT);
    //pinMode(RGBLED[i][0], OUTPUT);        //Column 0 contains the pin number
    pinMode(device[i].number, OUTPUT);      //number field contains the pin number
  }

  Timer1.initialize(1000000);                 //request a notification at regular intervals (us)
  //  Timer1.attachInterrupt(parallelArrays); //provide the name of our interrupt service routine
  //  Timer1.attachInterrupt(matrixStructure);//provide the name of our interrupt service routine
  Timer1.attachInterrupt(arrayStructs);       //provide the name of our interrupt service routine
}

void parallelArrays() {
  analogWrite(RGBLED[index][1], 0);           //turn off the current LED (ground the anode lead)
  index = (index + 1) % numElements;          //cyclic advancement in array index
  analogWrite(number[index], level[index]);   //apply the analog voltage level to the new LED
}

void matrixStructure() {
  analogWrite(number[index], 0);                  //turn off the current LED (ground the anode lead)
  index = (index + 1) % numElements;              //cyclic advancement in array index
  analogWrite(RGBLED[index][0], RGBLED[index][1]);//apply the analog voltage level to the new LED
  Timer1.setPeriod(RGBLED[index][2] * 1000000);
}

void arrayStructs() {
  analogWrite(device[index].number, 0);           //turn off the current LED (ground the anode lead)
  index = (index + 1) % numElements;              //cyclic advancement in array index
  analogWrite(device[index].number, device[index].level); //apply the analog voltage level to the new LED
  Timer1.setPeriod(device[index].duration * 1E6); //1E6 shoft form of 1000000
}

void loop() {}                              //nothing to do but sit back and watch the action
