// PROJECT  :BinaryCodeModulation
// PURPOSE  :Demonstration of Binary Code Modulation (BCM) aka Bit Angle Modulation (BAM)
//          :An alternative to PWM. This code uses TimerOne library so PWM on pins 9&10 n/a
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 11 22
// uC       :328
// COURSE   :ICS3U
// STATUS   :Working
// REFERENCE:http://www.batsocks.co.uk/readme/art_bcm_3.htm
#include <TimerOne.h>                 //Handy library to provide Timer1 interrupts                 
#define MCU_FREQ  16000000L           //Base frequency of the Arduino
#define Hz 2000                       //This appears to be a good target frequency
#define NUMBITS 8                     //Full byte modulation
#define RESOLUTION (1<<NUMBITS)       //Brackets are required!
#define POTA 15                       //A----|
#define POTC A2                       //  C--|
#define POTB 17                       //B----|
// determine the duration of the LSB to achieve desired Hz for given number of bits
volatile uint32_t period = MCU_FREQ / Hz / RESOLUTION;
uint8_t data;                         //Binary Code to be mod. (analog input)
volatile uint8_t i = 0;               //Bit index [bit7:0]
uint8_t LED = 14;                     //Display LED pin as verification
boolean logging = false;              //Logging option
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);               //Enable LED display
  Timer1.initialize(period);          //Set base multiple for interrupt duration
  Timer1.attachInterrupt(modulate);   //ISR (Interrupt Service Routine)
  pinMode(POTA, OUTPUT);              //Enable POT pin A
  digitalWrite(POTA, HIGH);           //
  pinMode(POTB, OUTPUT);              //Enable POT pin B
  digitalWrite(POTB, LOW);            //
}

//Here's the BCM magic...
void modulate() {
  digitalWrite(LED, data & (1 << i++)); //Bit value defines state of LED
  Timer1.setPeriod(period << i);        //Bit position (weight) defines delay
  i &= (NUMBITS - 1);                   //Constrain to closed interval: [0,7]
}

void loop() {
  data = analogRead(POTC) >> 2;         //Map POT reading to closed interval: [0,255]
  if (logging) Serial.println(data);    //Optional logging
}
