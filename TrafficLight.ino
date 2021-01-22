//Project : Traffic Light
//Author : Joshua Dolgin
//Date  : 2018/09/18
//Status : Working
//Reference :http://darcy.rsgc.on.ca/ACES/TEI3M/1819/Tasks.html 

uint8_t green = 1; 
uint8_t amber = 2;
uint8_t red = 0;
/*uses an unsigned 8 bit integer to rename 
each pin to the corresponding color*/

uint16_t duration = 3000; 
/* uses an unsigned 16 bit integer to create  
a variable called "duration that lasts 3000 
milliseconds*/

void setup() {
  // put your setup code here, to run once:
  
pinMode(green, OUTPUT);
pinMode(amber, OUTPUT);
pinMode(red, OUTPUT);
/*sets the 3 pins to output*/

}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(green, HIGH);
 /*sets the pins output to high, 
 effectively turning on the LED*/
 delay(duration);
 /*delays for the variable "duration"
 which was previously defined as 3000 milliseconds*/
 digitalWrite(green, LOW);
 /*sets the pins output to low, 
effectively turning off the LED*/
 digitalWrite(amber, HIGH);
 delay(duration/3);
 digitalWrite(amber, LOW);
 digitalWrite(red, HIGH);
 delay(duration);
 digitalWrite(red, LOW);

}
