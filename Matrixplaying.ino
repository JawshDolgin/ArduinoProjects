//Project :
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :

uint8_t data = 10;        // DA: SER IN (Serial Input)
uint8_t clk = 9;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 8;       // LA: RCK (Register Clock)
uint8_t colData [] = {0x18, 0x3C, 0x7E, 0xFF}; // with both colData and rowData = 0x01,
uint8_t rowData [] = {0x18, 0x3C, 0x7E, 0xFF}; //...only the top left LED should light up


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);     //
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint8_t j = 0; j < sizeof(colData); j++) {
    digitalWrite(latch, LOW);
    shiftOut(data, clk, LSBFIRST, colData[j]);
    shiftOut(data, clk, LSBFIRST, rowData[j]);
    digitalWrite(latch, HIGH);
    delay(250);
  }
  for (uint8_t i = sizeof(colData); i > 0; i--) {
    digitalWrite(latch, LOW);
    shiftOut(data, clk, LSBFIRST, colData[i]);
    shiftOut(data, clk, LSBFIRST, rowData[i]);
    digitalWrite(latch, HIGH);
    delay(250);
  }
}
