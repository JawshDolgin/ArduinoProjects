//Project :
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :
const int sampleWindow = 50; 
uint16_t sample;
uint8_t data = 11;        // DA: SER IN (Serial Input)
uint8_t clk = 10;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 9;       // LA: RCK (Register Clock)
uint8_t cornerData [] = {0x00, 0x81, 0xC3, 0xE7, 0xFF};
uint8_t boxData [] = {0x00, 0x18, 0x3C, 0x7E, 0xFF};

void setup() {
  // put your setup code here, to run once:
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  uint32_t startMillis = millis(); // Start of sound sample window
  uint16_t soundLevel = 0;   // soundLevel value (volume)
  uint16_t signalMaximum = 0;
  uint16_t signalMinimum = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(A0);
    if (sample < 1024)
    {
      if (sample > signalMaximum)
      {
        signalMaximum = sample;
      }
      else if (sample < signalMinimum)
      {
        signalMinimum = sample;
      }
    }
  }
  soundLevel = signalMaximum - signalMinimum;
  float voltReading = (soundLevel * 5.0) / 1024;
  voltReading = voltReading * 10;
  voltReading = constrain(voltReading, 2, 24);
  voltReading = map(voltReading, 2, 24, 1, 5);

  if (!analogRead(A5)) {
    for (uint8_t j = 0; j < voltReading; j++) {
      digitalWrite(latch, LOW);
      shiftOut(data, clk, LSBFIRST, cornerData[j]);
      shiftOut(data, clk, LSBFIRST, cornerData[j]);
    }
    digitalWrite(latch, HIGH);
  } else
    for (uint8_t j = 0; j < voltReading; j++) {
      digitalWrite(latch, LOW);
      shiftOut(data, clk, LSBFIRST, boxData[j]);
      shiftOut(data, clk, LSBFIRST, boxData[j]);
    }
  digitalWrite(latch, HIGH);
}
