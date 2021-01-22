uint8_t analogPin = 7; // read multiplexer using analog input 0
uint8_t strobePin = 8; // strobe 
uint8_t resetPin = 0; // reset 
int spectrumValue[7]; // to hold values
uint8_t data = 1;        // DA: SER IN (Serial Input)
uint8_t clk = 2;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 3;       // LA: RCK (Register Clock)
uint8_t colData = 0x01;  //which column is lit
uint8_t rowData [] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF}; // How many LEDs are lit

void setup()
{
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  analogReference(DEFAULT); //Analog reference to 5V
  pinMode(data, OUTPUT);      
  pinMode(clk, OUTPUT);       
  pinMode(latch, OUTPUT);     
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop()
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW); //Reset the MSGEQ7
  for (uint8_t i = 0; i < 7; i++)
  {
    digitalWrite(strobePin, LOW);
    delayMicroseconds(30); // to allow the output to settle
    spectrumValue[i] = analogRead(analogPin); //Reading the analog value
    digitalWrite(latch, LOW); 
    shiftOut(data, clk, LSBFIRST, colData<<i); //Move over i columns
    shiftOut(data, clk, LSBFIRST, rowData[spectrumValue[i] >> 7]); // Determines amount of LEDs
    digitalWrite(latch, HIGH);
    digitalWrite(strobePin, HIGH);
  }
}
