uint8_t analogPin = 7; // read from multiplexer using analog input 0
uint8_t strobePin = 8; // strobe is attached to digital pin 2
uint8_t resetPin = 0; // reset is attached to digital pin 3
int spectrumValue[7]; // to hold a2d values
uint8_t data = 1;        // DA: SER IN (Serial Input)
uint8_t clk = 2;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 3;       // LA: RCK (Register Clock)
uint8_t rowData = 0x01;
uint8_t colData [] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void setup()
{
  //  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  analogReference(DEFAULT);
  pinMode(data, OUTPUT);      
  pinMode(clk, OUTPUT);       
  pinMode(latch, OUTPUT);     
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop()
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  for (uint8_t i = 0; i < 7; i++)
  {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); // to allow the output to settle
    spectrumValue[i] = analogRead(analogPin);
    digitalWrite(latch, LOW);
    shiftOut(data, clk, LSBFIRST, rowData<<i);
    shiftOut(data, clk, LSBFIRST, colData[spectrumValue[i] >> 7]);
    digitalWrite(latch, HIGH);
    digitalWrite(strobePin, HIGH);
  }
}
