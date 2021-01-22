// PROJECT  :RxTest
// PURPOSE  :To display an incoming byte from TxTemp on a Morland bargraph
// DEVICE   :Arduino + AVES nRF Breakout Board + nRF24L01
// AUTHOR   :C. D'Arcy
// DATE     :2019 02 09
// uC       :328p
// COURSE   :ICS3U
// STATUS   :Working (with TxTest)
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/CommunicationProtocols.html#RF1
//          :https://tmrh20.github.io/RF24/classRF24.html
//          :https://mail.rsgc.on.ca/~cdarcy/Datasheets/nRF24L01.pdf
#include <RF24.h>
#define CHANNEL 100             //any value between 0 and 125 (2.400GHz to 2.525GHz)
uint8_t receivedData;           //for receiver to store the incoming byte
uint8_t clockPin = 14;          //aka A0 (PC0)
uint8_t latchPin = 15;          //aka A1 (PC1)
uint8_t dataPin = 16;           //aka A2 (PC2)
uint8_t groundPin = 17;         //aka A3 (PC3)
uint8_t powerPin = 18;          //aka A4 (PC4)

RF24 radio(9, 10);                            //CE (Chip Enable/Disable), CSN(SS)
uint8_t addresses[][6] = {"1Node", "2Node"};  //pipe names (See Reference 2)

void setup() {
  Serial.begin(9600);           //invoke the local terminal window
  while (!Serial);              //wait for full activation
  configureBargraph();          //set up the Morland bargraph

  radio.begin();                //invoke the radio
  radio.setPALevel(RF24_PA_LOW);//set low power amplification for close proximity
  radio.setChannel(CHANNEL);    //mutually agreeable frequency offset(2.400GHz to 2.525GHz)

  radio.openWritingPipe(addresses[1]);    //select ONE addresses to write to
  //https://tmrh20.github.io/RF24/classRF24.html#a9edc910ccc1ffcff56814b08faca5535
  radio.openReadingPipe(1, addresses[0]); //receiver and transmit are reversed
  radio.startListening();                 //should be good to go...
}

void loop() {
  if (radio.available()) {                //anything to be read?
    radio.read(&receivedData, 1);         //grab the oldest data byte
    Serial.println(receivedData);         //local echo
    displayData(receivedData);            //display on the bargraph
  }
}

void displayData(uint8_t rec) {
  uint8_t data = (1 << (rec >> 5)) - 1;         //What do you think this does?
  digitalWrite(latchPin, LOW);                  //detach shift regs from storage register
  shiftOut(dataPin, clockPin, LSBFIRST, data);  //next, shift bits in, serially....
  digitalWrite(latchPin, HIGH);                 //connect shift regs to storage register
}

//Our Rx display device is a Morland Bargraph inserted into PC0-PC4
void configureBargraph() {
  //DDRC = B11111000;                 //preferred register alternative to next 5 statements
  pinMode(clockPin, OUTPUT);          //declare all 5 Morland pins for output
  pinMode(latchPin, OUTPUT);          //
  pinMode(dataPin, OUTPUT);           //
  pinMode(groundPin, OUTPUT);         //
  pinMode(powerPin, OUTPUT);          //
  digitalWrite(groundPin, LOW);       //sink
  //PORTC |= 1<<PC4;                  //preferred register alternative to next statement
  digitalWrite(powerPin, HIGH);       //source
}
