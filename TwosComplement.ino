// PROJECT  :2s Complement, Casting, and syntax of binary, hex and octal constants 
// PURPOSE  :In class code developed in support for important fundamentals
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 09 26
// uC       :328p
// COURSE   :ICS3U
// STATUS   :Working

uint8_t value = 151; //binary:0b10010111  hex:0x97 octal:0227

void setup() {
  Serial.begin(9600);       // open the Serial Monitor
  while (!Serial);          // wait for it to become available
  Serial.println(value);    // display the number as the defined type (unsigned integer)
  Serial.println( (int8_t) value);  // cast the unsigned number as an 8-bit signed integer
  Serial.println( (int16_t) value); // cast the unsigned number as a 16-bit signed integer
  Serial.println( (char) value);    // cast the 8-bit integer as an ASCII character
}
void loop() {
}
