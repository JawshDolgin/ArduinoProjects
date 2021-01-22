// PROJECT  :IRLEDControl 
// PURPOSE  :ACES Adaptation of Shirriff's IRrecvDump Example 
// DEVICE   :Arduino + Sharp GP1UX511QS (38kHz, 8.5m,5V) + Bicolor LED
// AUTHOR   :C. D'Arcy
// DATE     :2019 03 24
// uC       :328
// COURSE   :ICS3U
// STATUS   :Working
// REF1     :IRremote library (https://github.com/z3t0/Arduino-IRremote)
// REF2     :https://en.wikibooks.org/wiki/C_Programming/Preprocessor_directives_and_macros
// REF3     :Shirriff's IR Blog:http://www.righto.com/search?q=IR
// REF4     :Find IR Codes: http://irdb.tk/find
//GO into serial monitor and press buttons to find which button has which HEX code
#include <IRremote.h>
#define RECV_PIN 11         //GP1UX511QS: pin 1 (VOUT: IR receiver as appliance) 
#define GND 10              //GP1UX511QS: pin 2 0V
#define VCC 9               //GP1UX511QS: pin 3 5V
//Compiler Preprocessor Directives...
#define DEBUG               //conditional serial monitoring (See: REF2)
//#define NEC               //https://www.sbprojects.net/knowledge/ir/nec.php
//#define SONY              //https://www.sbprojects.net/knowledge/ir/sirc.php
//#define SHARP             //
#define GENERIC           //Generic...labelled: LCD Remote
//#define SMARTBOARD          //DES Smartboard Remote Control
#ifdef NEC                  //
  #define ON_OFF 0x61A028D7
#else
  #ifdef SMARTBOARD                  
    #define ON_OFF 0xD15348B7  
  #else
    #ifdef GENERIC
      #define ON_OFF 0xE4CD1208
    #endif
  #endif
#endif
#define TERMINATOR 0xFFFFFFFF   //
IRrecv irrecv(RECV_PIN);
decode_results results;         //results data structure
#define RED PD7                 //Red anode
#define GREEN PD6               //Green anode

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();          //Start the Detector
  pinMode(VCC, OUTPUT);         //identify supply lines
  pinMode(GND, OUTPUT);         //
  digitalWrite(VCC, HIGH);      //provide 5V supply
  digitalWrite(GND, LOW);       //provide GND supply

  DDRD |= 1 << RED | 1 << GREEN;      //set LED leads to output
  PORTD &= ~(1 << RED | 1 << GREEN);  //ground 'em both
  showRed();                          //start with red to confirm
}

void showRed() {            //turn on the Red lamp
  PORTD &= ~(1 << GREEN);   //set Green lead LOW
  PORTD |= (1 << RED);      //set Red lead HIGH
}

void showGreen() {          //turn on the Green lamp
  PORTD &= ~(1 << RED);     //set Red lead LOW
  PORTD |= (1 << GREEN);    //set Green lead HIGH    
}

void loop() {
  if (irrecv.decode(&results)) {    //if there's a signal, demodulate and record
    #ifdef DEBUG                    //suspend this code when deployed 
      Serial.println(results.value, HEX);
    #endif
    if (results.value == ON_OFF){
        showGreen();
        delay(3000);
        showRed();
    }
    irrecv.resume();                //prepare for next IR signal
  }
}
