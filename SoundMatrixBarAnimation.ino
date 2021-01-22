//Project :
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
uint8_t data = 11;        // DA: SER IN (Serial Input)
uint8_t clk = 10;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 9;       // LA: RCK (Register Clock)
uint8_t colData [] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // with both colData and rowData = 0x01,
uint8_t rowData [] = {0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF}; //...only the top left LED should light up




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  pinMode(data, OUTPUT);      //
  pinMode(clk, OUTPUT);       //
  pinMode(latch, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t startMillis = millis(); // Start of sound sample window
  uint16_t soundLevel = 0;   // soundLevel value (volume)

  uint16_t signalMax = 0;
  uint16_t signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)//
  {
    sample = analogRead(A0);//Read volts on analog pin 0, out pin of the mic
    if (sample < 1024)  //If sound sample is less than the minimum value
    {
      if (sample > signalMax) //If sound sample is greater than the maximum value
      {
        signalMax = sample;  // Save just the max levels
      }
      else if (sample < signalMin) // Or if the sound level is greater than the minimum value
      {
        signalMin = sample;  // Save just the min levels
      }
    }
  }
  soundLevel = signalMax - signalMin; // Max value- min value = soundLevel
  float voltReading = (soundLevel * 5.0) / 1024;  // Convert to volts
  voltReading = voltReading * 10;//Get values from 0.2 volts - 2.4 volts, to values from 2 volts - 24 volts
  voltReading = constrain(voltReading, 2, 24);//Constrain volt values between 2 - 24
  voltReading = map(voltReading, 2, 24, 1, 8);

  for (uint8_t j = 0; j < voltReading; j++) {
    digitalWrite(latch, LOW);
    shiftOut(data, clk, LSBFIRST, colData[j]);
    shiftOut(data, clk, LSBFIRST, rowData[j]);
  }
  digitalWrite(latch, HIGH);
}
