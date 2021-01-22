// PROJECT  :DigitalPins0and1 
// PURPOSE  :Demonstrates the use of Digital Pins 0 and 1 when Serial Communication not required
// DEVICE   :Arduino UNO
// AUTHOR   :C. D'Arcy
// DATE     :2019 01 10
// uC       :328p
// COURSE   :ICS3U
// STATUS   :Working
// NOTES    :Disconnect any component from digital pins 0 and 1 when uploading this code

#define RX 0          //Normally used for receiving bytes in the serial stream
#define TX 1          //Normally used for transmitting bytes in the serial stream
#define DURATION 500  //Frequency of flashing (default: 1Hz)

void setup() {
  Serial.begin(9600);
  Serial.println("Disconnect any component from digital pins 0 and 1 when uploading this code.");
  Serial.println("Once uploaded, insert a bicolor LED into pins 0 and 1.");
  Serial.end();         //disconnect the UART (serial comm stream) 
  pinMode(RX,OUTPUT);   //digital pin 0 is now free for use
  pinMode(TX,OUTPUT);   //digital pin 1 is now free for use
}

void loop() {
  digitalWrite(RX,HIGH);  //depending on the LED orientation, turn one colour on
  digitalWrite(TX,LOW);
  delay(DURATION);        //admire...
  digitalWrite(RX,LOW);   //turn the other colour on
  digitalWrite(TX,HIGH);
  delay(DURATION);        //admire...
}
