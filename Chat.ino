// PROJECT  :Chat
// PURPOSE  :Utility to enable a conversation between ACES' Arduino users
// DEVICE   :2 Arduinos
// AUTHOR   :Lots of people
// DATE     :2019 01 24
// uC       :328
// COURSE   :ICS3U
// STATUS   :(Possibly) Working
// REFERENCE:https://www.arduino.cc/en/Tutorial/SoftwareSerialExample
//          :https://www.instructables.com/id/Simple-Chat-Program-with-Arduino-Uno/
// NOTES    :Receives from the hardware serial, sends to hardware & software serial.
//          :Receives from software serial, sends to hardware serial.

#include <SoftwareSerial.h>
SoftwareSerial chat(10, 11); // RX, TX
char ch;

void setup() {
  Serial.begin(9600);     //use the hardware UART for the Serial Monitor
  while (!Serial);        //wait for serial port to connect
  Serial.println("Starting Chat Program...");
  // set the data rate for the SoftwareSerial port
  chat.begin(9600);
  delay(1000);
  chat.println("Hello, world?");
  Serial.println("Ready to chat...");
}

void loop() {
  if (chat.available()) {           //anything incoming?
    Serial.write(chat.read());      //if so, display the oldest character in the incoming (queued) buffer
  }
  if (Serial.available())  {        //anything outgoing?
    Serial.print("Self:\t");        //if so, let's get started...
    while (Serial.available()) {    //transmit each of the outgoing characters...
      ch = Serial.read();           //...to the software serial stream
      chat.write(ch);               //...
      Serial.write(ch);             //also, echo each character on my local Serial Monitor
    }
    chat.println();                 //At end, transmit a newline (carriage return) character
    Serial.println();               //At end, also write a newline character to the local Serial Monitor
  }
}
