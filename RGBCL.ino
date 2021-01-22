// PROJECT  :RGBCL: RGB LED Command Language
// PURPOSE  :Serial input interpreter for an RGBLED Command Language
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 10 30
// uC       :328
// COURSE   :ICS3U
// STATUS   :Working
// NOTE     :The RGBLED in your kit is the Common Anode (CA) variety
#define RED 3           //
#define COM 4           //Common Anode
#define GREEN 5         //
#define BLUE 6          //
#define DURATION 1000   //time between changes
String command;         //user-entered command line to be interpreted
uint8_t which;          //utility variable to facilitate switch..case decisions

void setup() {
  DDRD = 0b01111000;    //sets PD3-6 for output
  PORTD = 0b01111000;   //turns off LEDs by setting all leads to the same (high) potential
  Serial.begin(9600);   //prepare the serial monitor for user input
  while (!Serial);      //wait until Serial object is ready for action
}

void loop() {
  while (!Serial.available());    //wait here for user input
  command = Serial.readString();  //grab the input up to and including the CR
  //process each character in the String object
  //NOTE: upper bound is reduced by 1 because String object includes the CR (Enter)
  for (uint8_t i = 0; i < command.length() - 1; i++) {
    //determine which LED is to be lit...
    switch (command.charAt(i)) {
      case 'R': which = RED; break;
      case 'G': which = GREEN; break;
      case 'B': which = BLUE;
    }
    PORTD &= ~(1 << which);     //ground the correct pin to turn on the LED
    delay(DURATION);            //admire the glow...
    PORTD |= 1 << which;        //set the ground the correct pin to turn on the LED
  }
}
