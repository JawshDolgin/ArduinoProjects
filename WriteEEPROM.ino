// PROJECT  :AT28C16Write
// PURPOSE  :Writes data to the AT28C16 (2Kx8) EEPROM IC
// COURSE   :ICS4U
// AUTHOR   :B. Eater. adapted for ACES CHUMP use by C. D'Arcy
// DATE     :2019 11 13-16
// MCU      :Nano/328
// STATUS   :Working
// REFERENCE:B. Eater Github...
//          :https://github.com/beneater/eeprom-programmer/blob/master/eeprom-
//           programmer/eeprom-programmer.ino
// REFERENCE:B. Eater Videos
//          1. Using an EEPROM to replace combinational logic
//          https://www.youtube.com/watch?v=BA12Z7gQ4P0&feature=emb_logo
//          2. Build an Arduino EEPROM programmer
//          https://www.youtube.com/watch?v=K88pgWhEb1M&feature=emb_logo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CHUMP Basic Program Example
//00000101  LOAD 5  accum = 5; pc++;
//01100001 STORETO 1 mem[1]<-accum; pc++;
//10000010 READ 2  addr<-2; pc++;
//00010000 LOAD IT accum = mem[2]; pc++;
//10000001 READ 1  addr<-1; pc++;
//00110000 ADD IT  accum+mem[1]; pc++;
//01100010 STORETO 2 mem[2]<-accum; pc++;
//10000001 READ 1  addr<-1; pc++;
//00010000 LOAD IT accum = mem[1]; pc++;
//01000001 SUBTRACT 1  accum--; pc++
//11001100 IFZERO 12 accum==0?pc=12; pc++;
//10100001 GOTO 1  pc<-0001
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// populate array below with machine instructions above
byte code [] = {
  0b00000101,
  0b01100001,
  0b10000010,
  0b00010000,
  0b10000001,
  0b00110000,
  0b01100010,
  0b10000001,
  0b00010000,
  0b01000001,
  0b11001100,
  0b10100001
};
#define PROG_SIZE sizeof(code)
#define EEPROM_D0 2
#define EEPROM_D1 3
#define EEPROM_D2 4
#define EEPROM_D3 5
#define EEPROM_D4 6
#define EEPROM_D5 7
#define EEPROM_D6 8
#define EEPROM_D7 9
#define EEPROM_OE 10
#define EEPROM_WE 11
#define EEPROM_A0 14
#define EEPROM_A1 15
#define EEPROM_A2 16
#define EEPROM_A3 17

void setup() {
  pinMode(EEPROM_A0, OUTPUT);
  pinMode(EEPROM_A1, OUTPUT);
  pinMode(EEPROM_A2, OUTPUT);
  pinMode(EEPROM_A3, OUTPUT);
  digitalWrite(EEPROM_WE, HIGH);
  pinMode(EEPROM_WE, OUTPUT);
  digitalWrite(EEPROM_OE, HIGH);
  pinMode(EEPROM_OE, OUTPUT);
  Serial.begin(9600);
  Serial.println("Here's the data to be flashed to EEPROM...");
  for (int address = 0; address < PROG_SIZE; address++) {
    Serial.print(code[address], HEX);
    Serial.print("  ");
  }
  Serial.println();
  // Write the code to EEPROM...
  Serial.println("Writing " + String(PROG_SIZE) + " bytes of code to EEPROM...");
  for (int address = 0; address < PROG_SIZE; address++) {
    writeEEPROM(address, code[address]);
  }
  Serial.println("Done");

  // Confirm the write by reading and echoing the code to the Serial Monitor...
  Serial.println("Reading EEPROM");
  printContents();
}

// Read the contents of the EEPROM and print them to the serial monitor.
void printContents() {
  for (int address = 0; address < PROG_SIZE; address++) {
    Serial.println(readEEPROM(address), HEX);
  }
}

// Output the address bits and outputEnable signal using shift registers.
void setAddress(int address) {
  for (int pin = EEPROM_A3; pin >= EEPROM_A0; pin--) {
    digitalWrite(pin, address & 0x08);
    address <<= 1;    //destructive
  }
}
byte readEEPROM(int address) {
  digitalWrite(EEPROM_WE, HIGH);
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) {
    pinMode(pin, INPUT);
  }
  byte value = 0;
  setAddress(address);
  digitalWrite(EEPROM_OE, LOW);
  delayMicroseconds(1);
  digitalWrite(EEPROM_OE, HIGH);
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) {
    Serial.print(digitalRead(pin));
    value = (value << 1) + digitalRead(pin);
  }
  Serial.print(" ");
  return value;
}
//  Write a byte to the EEPROM at the specified address.
void writeEEPROM(int address, byte data) {
  digitalWrite(EEPROM_OE, LOW);
  digitalWrite(EEPROM_WE, HIGH);
  Serial.println("[" + String(address) + "]" + String(code[address], HEX));
  //Set the address
  setAddress(address);
  digitalWrite(EEPROM_OE, HIGH);
  //prepare to write the data...
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
    pinMode(pin, OUTPUT);
  }
  //write the data...
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) {
    digitalWrite(pin, data & 0x80);
    data <<= 1;   //destructive....
  }
  digitalWrite(EEPROM_WE, LOW);
  delayMicroseconds(1);
  digitalWrite(EEPROM_WE, HIGH);
  delay(10);
}

void loop() {
  // nothing left to do...
}
