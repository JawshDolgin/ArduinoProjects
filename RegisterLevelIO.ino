// PROJECT  :Register-Level IO
// PURPOSE  :Provides a register-level look at (potentially) more efficient input/output function 
//          :by echoing byte input from buttons 
// DEVICE   :Arduino UNO
// AUTHOR   :C. D'Arcy
// DATE     :2018 10 08
// uC       :328p
// COURSE   :ICS3U (Enriched)
// STATUS   :Working
/*********************************************************************************************
1. The ATmega328P offers 3 General Purpose Input/Output (GPIO) ports.
2. These are port B, C, and D as can be seen by clicking the graphic link on Lesson 10.
3. All 8 bits of Ports B and D are broken out to physical pins, whereas Port C only to 7 pins.
4. To accommodate many other features of the microcontroller, the physical port pins are used
   for other purposes as required. 
5. As amazing as the ATmega328P is, it is somewhat unfortunate that the designers did not leave
   at least one ENTIRE 8-bit port (either Port B or D) unencumbered by these other uses. 
6. PB6-7 are typically tied up with the external crystal and PD0-1 are typically committed to
   supporting serial communications (Rx/Tx)
7. The designers of the Arduino UNO therefore were unable to allow developers easy access to
   a FULL BYTE of IO activity.
8. In this sample sketch I'll restrict GPIO activity to Register-Level manipulation of the low
   6 bit os Port B (PB0-5) that are broken out to the UNO's digital pins 8-13. 
*********************************************************************************************/
#define DURATION 1000
uint8_t buttonStates;

void setup() {
  Serial.begin(9600);
  DDRB = 0;         //declares all Port B pins for input
                    //totally optional as pins are 0 (input) by default
                    //equivalent to the high-level code:
                    //    for(uint8_t pin=8; pin<=13; pin++) pinMode(pin,INPUT);
  PORTB = 0x3F;     //sets pullup resistors on 6 low order bits of Port B,       
                    //equivalent to the high-level code:
                    //    for(uint8_t pin=8; pin<=13; pin++) pinMode(pin,INPUT_PULLUP);
  Serial.println("Press any combination of buttons..."); 
}
void loop() {
  delay(DURATION);      //poll the button input at preferred intervals 
  buttonStates = PINB;  //equivalent of the high-level code:
                        //    buttonStates = 0;
                        //    for(uint8_t pin=0; pin<=5; pin++) 
                        //      buttonStates |= digitalRead(8+pin)<<pin;
  Serial.println(buttonStates,BIN);
                        //a press is viewed as a 0; unpressed a 1 due to pullup
}
