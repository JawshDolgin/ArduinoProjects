// PROJECT  :SerialPrintModifiers 
// PURPOSE  :Demonstration of the Serial print functions numeric modifiers 
// DEVICE   :*
// AUTHOR   :?
// DATE     :2019 01 09
// uC       :*
// COURSE   :ICS3U/ICS4U
// STATUS   :Working
// REFERENCE:https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
// NOTES    :Uses a for loop to print numbers in various formats.
void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
}

void loop() {
  // print labels
  Serial.print("NO FORMAT");  // prints a label
  Serial.print("\t");      // prints a tab

  Serial.print("DEC");
  Serial.print("\t");

  Serial.print("HEX");
  Serial.print("\t");

  Serial.print("OCT");
  Serial.print("\t");

  Serial.print("BIN");
  Serial.println();        // carriage return after the last label

  for (int x = 0; x < 64; x++) { // only part of the ASCII chart, change to suit
    // print it out in many formats:
    Serial.print(x);       // print as an ASCII-encoded decimal - same as "DEC"
    Serial.print("\t\t");  // prints two tabs to accomodate the label lenght

    Serial.print(x, DEC);  // print as an ASCII-encoded decimal
    Serial.print("\t");    // prints a tab

    Serial.print(x, HEX);  // print as an ASCII-encoded hexadecimal
    Serial.print("\t");    // prints a tab

    Serial.print(x, OCT);  // print as an ASCII-encoded octal
    Serial.print("\t");    // prints a tab

    //Serial.println(x, BIN); // print as an ASCII-encoded binary
    displayBinary(x);       //activate for full 8-bit binary display
    // then adds the carriage return with "println"
    delay(200);            // delay 200 milliseconds
  }
  Serial.println("--End of sequence--");        // prints another carriage return
  while(true);
}

// This alternative function can be used to display full 8-bit binary numbers
void displayBinary(uint8_t data) {
  for (int8_t i = 7; i >= 0; i--)
    Serial.print(data & (1 << i) ? 1 : 0);
  Serial.println();
}
