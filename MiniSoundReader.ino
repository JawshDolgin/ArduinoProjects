//Project :
//Author : 
//Date : YYY/MM/DD
//Status :
//Reference :
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

//Pin connected to ST_CP (latch) of 74HC595
uint8_t latchPin = 9;
//Pin connected to SH_CP (clock) of 74HC595
uint8_t clockPin = 10;
//Pin connected to DS (data) of 74HC595
uint8_t dataPin = 8;


uint8_t barGraph[] = {0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111};//bar graph
//uint8_t numElements = sizeof(barGraph);

#define DURATION 500      //define the speed of the animation 
void setup()
{
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}


void loop()
{
  unsigned long startMillis = millis(); // Start of sound sample window
  unsigned int soundLevel = 0;   // soundLevel value (volume)

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

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
  double volts = (soundLevel * 5.0) / 1024;  // Convert to volts
  volts = volts * 10;//Get values from 0.2 volts - 2.4 volts, to values from 2 volts - 24 volts
  volts = constrain(volts, 2, 24);//Constrain volt values between 2 - 24
  volts = map(volts, 2, 24, 1, 8); // Get the volt value to be compatible with the 8 leds on the bar graph

  for (uint8_t j = 0; j < volts; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, barGraph[j]);
    //return the latch pin high to signal chip that it

  }
  digitalWrite(latchPin, HIGH);
  //no longer needs to listen for information
}
