// PROJECT  :Raymond RTC Appliance
// PURPOSE  :The purpose of this code is display the time from a RTC on four digit seven segment display.
// AUTHOR   :Nick Woollcombe
// DATE     :2019 05 14
// COURSE   :ICS3U
// STATUS   :Working
// NOTES    :Still need to do dimming feature.

#include <TimerOne.h>         //Include TimerOne.h
#include <EEPROM.h>           //Include EEPROM.h
#include <SparkFunDS1307RTC.h>//Include SparkFun library
#include <Wire.h>             //Include Wire.h library
#define SQW_INPUT 2           //RTC input pin
#define DATA 13               //Data pin
#define CLK 11                //Clock pin 
#define LATCH 12              //Latch pin
#define SQW_INPUT_PIN 2       // Input pin to read SQW
#define SQW_OUTPUT_PIN 8      // LED to indicate SQW's state
uint8_t digitsData = 0;       //Digits data to be displayed
uint8_t segmentsData = 0;     //Segments data to be displayed
uint8_t binary = 0;           //Binary number for interrupt
uint8_t hourTen;              //Hours' tens digit
uint8_t hourOne;              //Hours' ones digit
uint8_t minuteTen;            //Minutes' tens digit
uint8_t minuteOne;            //Minutes' ones digit

void setup() {
  pinMode(DATA, OUTPUT);                      //Sets DATA pin to output pin
  pinMode(CLK, OUTPUT);                       //Sets CLK pin to output pin
  pinMode(LATCH, OUTPUT);                     //Sets LATCH pin to output pin
  Timer1.initialize(1000000);                 //Initializes Timer1 with 1 second
  Timer1.attachInterrupt(interruptFunction);  //When Timer1 runs, redirect to interruptFunction()
  pinMode(SQW_INPUT, INPUT_PULLUP);           //Sets SQW_INPUT to be INPUT_PULLUP
  rtc.begin();                                //Initializes the library
  rtc.autoTime();                             //Sets the rtc to the current time
  Serial.begin(9600);                         //Begin serial monitor at 9600
  pinMode(SQW_INPUT_PIN, INPUT_PULLUP);       //Turn square wave input into input pullup
  pinMode(SQW_OUTPUT_PIN, OUTPUT);            //Turn square wave output into output pin
  digitalWrite(SQW_OUTPUT_PIN, digitalRead(SQW_INPUT_PIN));
  rtc.begin();                              //Begin RTC library
  rtc.writeSQW(SQW_SQUARE_1);               //Start square wave
  //rtc.autoTime();                           //Autoset Time
  rtc.setTime(15, 51, 10, 2, 14, 5, 19);  //Manually set time
  rtc.set12Hour();                          //Use rtc.set12Hour to set to 12-hour mode
}

void interruptFunction() {               //Function that flips binary between 1 and 0
  binary++;                              //Add one
  binary = binary % 2;                   //Find remainder when dividing by 12
}

void blinkColons() {                     //Function to blink colons every second
  if (binary == 0) {
    digitalWrite(LATCH, LOW);                    //Set latch to low
    shiftOut(DATA, CLK, LSBFIRST, 0b00010000);   //shiftOut digits data
    shiftOut(DATA, CLK, LSBFIRST, 0b11111111);   //shiftOut segments data
    digitalWrite(LATCH, HIGH);                   //Set latch to high
  }
  if (binary == 1) {
    digitalWrite(LATCH, LOW);                    //Set latch to low
    shiftOut(DATA, CLK, LSBFIRST, 0b00010000);   //shiftOut digits data
    shiftOut(DATA, CLK, LSBFIRST, 0b000000000);  //shiftOut segments data
    digitalWrite(LATCH, HIGH);                   //Set latch to high
  }
}

void loop() {
  displayOnSevenSegments();      //Run displayOnMatrix() method
  rtc.update();                  //Update clock values
}

void updateClockValues() {
  if (rtc.hour() > 9) {              //If hour is 10, 11 or 12
    hourTen = 1;                     //Hours digit is 1
    hourOne = int(rtc.hour()) % 10;  //Hours digit is hour remainder 10
  }
  if (rtc.hour() <= 9) {             //If hours is 9 or lower
    hourTen = 10;                    //Blank tens digit
    hourOne = int(rtc.hour());       //Hours digit is same as the actual hour value
  }

  //SWITCH STATEMENT
  if (rtc.minute() > 49) {            //For getting minutes 10s digit
    minuteTen = 5;
  } else if (rtc.minute() > 39) {     //For getting minutes 10s digit
    minuteTen = 4;
  } else if (rtc.minute() > 29) {     //For getting minutes 10s digit
    minuteTen = 3;
  } else if (rtc.minute() > 19) {     //For getting minutes 10s digit
    minuteTen = 2;
  } else if (rtc.minute() > 9) {      //For getting minutes 10s digit
    minuteTen = 1;
  } else if (rtc.minute() < 10) {     //For getting minutes 10s digit
    minuteTen = 0;
  }


  int minuteOne = int(rtc.minute()) % 10;   //Minutes one digit is actual minutes remainder 10
}
int findValuesforSegments(int digit) {      //Function takes inputs in form of single integer, and outputs binary code for segment display.
  int binaryArray[] = {0b00000011, 0b10011111, 0b00100101, 0b00001101, 0b10011001, 0b01001001, 0b01000001, 0b00011111, 0b00000001, 0b00011001, 0b11111111};
  segmentsData = binaryArray[digit];
  return segmentsData;                      //Return the binary code
}

void displayOnSevenSegments() {
  int minuteOne = int(rtc.minute()) % 10;                            //Set the minutes one digit with modulo
  digitalWrite(LATCH, LOW);                                          //Set LATCH to low (accept new values)
  shiftOut(DATA, CLK, LSBFIRST, 0b00000001);                         //shiftOut digits data
  shiftOut(DATA, CLK, LSBFIRST, findValuesforSegments(minuteOne));   //shiftOut segments data
  digitalWrite(LATCH, HIGH);                                         //Set LATCH to high
  blinkColons();                                                     //Blink the colons if second has elapsed
  digitalWrite(LATCH, LOW);                                          //Set LATCH to low (accept new values)
  shiftOut(DATA, CLK, LSBFIRST, 0b00000010);                         //shiftOut digits data
  shiftOut(DATA, CLK, LSBFIRST, findValuesforSegments(minuteTen));   //shiftOut segments data
  digitalWrite(LATCH, HIGH);                                         //Set LATCH to high
  blinkColons();                                                     //Blink the colons if second has elapsed
  digitalWrite(LATCH, LOW);                                          //Set LATCH to low (accept new values)
  shiftOut(DATA, CLK, LSBFIRST, 0b00000100);                         //shiftOut digits data
  shiftOut(DATA, CLK, LSBFIRST, findValuesforSegments(hourOne));     //shiftOut segments data
  digitalWrite(LATCH, HIGH);                                         //Set LATCH to high
  blinkColons();                                                     //Blink the colons if second has elapsed
  digitalWrite(LATCH, LOW);                                          //Set LATCH to low (accept new values)
  shiftOut(DATA, CLK, LSBFIRST, 0b00001000);                         //shiftOut digits data
  shiftOut(DATA, CLK, LSBFIRST, findValuesforSegments(hourTen));     //shiftOut segments data
  digitalWrite(LATCH, HIGH);                                         //Set LATCH to high
  blinkColons();                                                     //Blink the colons if second has elapsed
  updateClockValues();                                               //Update the clock values (that produce binary data)
}
