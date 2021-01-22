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
uint8_t Data [2][8] = {{ 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},
                       { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}}; 
uint8_t row = 0;




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
  voltReading = map(voltReading, 2, 24, 0, 1);

  for (uint8_t j = 0; j < voltReading; j++) {
    digitalWrite(latch, LOW);
    shiftOut(data, clk, LSBFIRST, Data[j][row]);
    shiftOut(data, clk, LSBFIRST, 1 << row);
    row = row < 8 ? row + 1 : 0;
  }
  digitalWrite(latch, HIGH);
}
