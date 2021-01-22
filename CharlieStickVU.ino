//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#define PinCon 0
#define PinState 1

#define LED_COUNT 12
#define numPin 4
uint8_t VCC = A1;
uint8_t GND = A0;

const int sampleTime = 50; // Sample window width in mS
uint16_t soundSample;
uint8_t stick[] = {10, 11, 12, 13,};
int configuration[LED_COUNT][2][4] = {
  //           PIN_CONFIG                  PIN_STATE
  //    A       B       C      D         A     B    C    D
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // AB 1
  { { INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, HIGH, LOW } }, // BA 2
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // BC 3
  { { INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // CB 4
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW } }, // AC 5
  { { OUTPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // CA 6
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // AD 7
  { { INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW } }, // DA 8
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW } }, // BD 9
  { { OUTPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW } }, // DB 10
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, HIGH } }, // CD 11
  { { OUTPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW } }  // DC 12
};

void setup() {
  Serial.begin(9600);
  pinMode(GND, OUTPUT);
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
  digitalWrite(GND, LOW);
}

void loop() {
  uint32_t startMillis = millis(); // Start of sample window
  uint16_t soundReading = 0;   //Sets the soundLevel to 0
  uint16_t signalMaximum = 0; // establsihes a signal maximum
  uint16_t signalMinimum = 1024; // establishes a signal minimum

  while (millis() - startMillis < sampleTime)  // collect data for 50 mS
  {
    soundSample = analogRead(A3);//Read volts on analog pin 0, out pin of the mic
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
  voltReading = map(voltReading, 2, 24, 1, LED_COUNT);//Map the volt reading to a value between 1 and 5
  Serial.println(voltReading);
    for (uint8_t l = 0; l < voltReading; l++) {
      for (uint8_t i = 0; i < numPin; i++) {
        pinMode(stick[i], configuration[l][PinCon][i]);
        digitalWrite(stick[i], configuration[l][PinState][i]);
      }
    }
}
