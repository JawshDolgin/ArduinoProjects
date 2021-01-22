// PROJECT  :MatrixMadeEZ
// PURPOSE  :Demo program of the MatrixMadeEZ Device (original design by H. Reed)
// RESULT   :First four rows of the main diagonal should light up as bright as possible
// AUTHOR   :C. D'Arcy
// DATE     :2019 12 03
// uC       :328P
// STATUS   :Working
// REFERENCE:https://cdn-shop.adafruit.com/datasheets/1079datasheet.pdf
#define DMLEVEL 0           //since /G on TPIC:  bright:0, dim:250ish
#define LIMIT 0xFF          //adjust for length of diagonal 
uint8_t dimmer = 3;         //PWM (or external voltage divider, eg pot, LDR)
uint8_t data = A4;          //avoid pins 9 and 10 for later use
uint8_t latch = A2;         //of the TimerOne library to control
uint8_t clk = A3; //frame speed
uint8_t score1 = 0;
uint8_t score2 = 0;
uint8_t VCC = A5;
uint8_t GND = A0;


uint8_t board[8];
uint8_t rowData[][3] = { {0b11111000, 0b10001000, 0b11111000}, {0b00000000, 0b000000000, 0b11111000}, {0b10111000, 0b10101000, 0b11101000},
  {0b10101000, 0b10101000, 0b11111000}, {0b11100000, 0b00100000, 0b11111000}
};   //let's light the main diagonal
uint8_t colData = 0x80;  //equate the row and column coordinates
//uint8_t colData2 = 0x04;

void setup() {
  Serial.begin(9600);
  pinMode(dimmer, OUTPUT);        //
  pinMode(data, OUTPUT);          //
  pinMode(clk, OUTPUT);           //
  pinMode(latch, OUTPUT);
  pinMode(VCC, OUTPUT);
  pinMode(GND, OUTPUT);  //
  analogWrite(dimmer, DMLEVEL);   //brightness control on the /G pin of the TPIC
  randomSeed(analogRead(A0));
  digitalWrite(VCC, HIGH);
  digitalWrite(GND, LOW);
}



void loop() {
  uint8_t binNumber = random(0, 15);
  Serial.println(binNumber, BIN);
  for (uint8_t j = 0; j < 3; j++) {
    board[j] = rowData[score1][j];
    board[j + 5] = rowData[score2][j];
  }

  //While input 1 or 2 are not equal to bin value keep doing POV

  //  while (binNumber != (binInput1 + binInput2 << 1 + binInput3 << 2 + binInput4 << 3) || (binInput5 + binInput6 << 1 + binInput7 << 2 + binInput8 << 3)) {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(latch, LOW);
    shiftOut(data, clk, MSBFIRST, colData >> i); //note the shift order
    shiftOut(data, clk, MSBFIRST, board[i] ); //and the column data first
    digitalWrite(latch, HIGH);
    digitalWrite(latch, LOW);
    for (uint8_t i = 0; i < 3; i++) {
      digitalWrite(latch, LOW);
      shiftOut(data, clk, MSBFIRST, binNumber << 2); //and the column data first
      shiftOut(data, clk, MSBFIRST, colData >> i + 5); //note the shift order
    }
    digitalWrite(latch, HIGH);
  }
}
//  } else if (biNumber == (binInput1 + binInput2 << 1 + binInput3 << 2 + binInput4 << 3)) {
//    score1++;
//  } else
//    score2++;
//}
