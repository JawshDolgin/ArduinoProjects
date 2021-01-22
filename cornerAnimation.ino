//Project : To create seperate animations on an LED matrix based off of the
//readings from an electret condensor mic.
//Author : Joshua Dolgin
//Date  : 2018/11/17
//Status :Working
const int sampleTime = 50; // Sample window width in mS
uint16_t soundSample;
uint8_t data = 11;        // DA: SER IN (Serial Input)
uint8_t clk = 10;         // CK: SRCK (Shift Register cloCK)
uint8_t latch = 9;       // LA: RCK (Register Clock)
uint8_t cornerData [] = {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};

void setup() {
  pinMode(data, OUTPUT);  //declares the data pin for OUTPUT
  pinMode(clk, OUTPUT);  //declares the clock pin for OUTPUT
  pinMode(latch, OUTPUT);//declares the latch pin for OUTPUT
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t startMillis = millis(); // Start of sample window
  uint16_t soundReading = 0;   //Sets the soundLevel to 0
  uint16_t signalMaximum = 0; // establsihes a signal maximum
  uint16_t signalMinimum = 1024; // establishes a signal minimum

  while (millis() - startMillis < sampleTime)  // collect data for 50 mS
  {
    soundSample = analogRead(A0);//Read volts on analog pin 0, out pin of the mic
    if (soundSample < 1024)  //If sound sample is less than the minimum value
    {
      if (soundSample > signalMaximum) //If sound sample is greater than the maximum value
      {
        signalMaximum = soundSample;  // Set the signal maximum to equal sample
      }
      else if (soundSample < signalMinimum) //if the sound level is greater than the minimum value
      {
        signalMinimum = soundSample;  // set the signal minimum to equal sample
      }
    }
  }
  soundReading = signalMaximum - signalMinimum; // Max value- min value = soundLevel
  float voltReading = (soundReading * 5.0) / 1024;  // Convert to volts
  voltReading = voltReading * 10; //Multiplies the volt reading by 10 in order to use integer values.
  voltReading = constrain(voltReading, 2, 24);//Constrain volt values between 2 - 24
  voltReading = map(voltReading, 2, 24, 1, 9);//Map the volt reading to a value between 1 and 5
  for (uint8_t j = 0; j < voltReading; j++) {
    digitalWrite(latch, LOW);
    shiftOut(data, clk, LSBFIRST, cornerData[j]); // Shifts out the box animation
    shiftOut(data, clk, LSBFIRST, cornerData[j]);
  }
  digitalWrite(latch, HIGH);// Writes the latch pin to high
}
