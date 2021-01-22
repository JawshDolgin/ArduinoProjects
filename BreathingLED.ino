//Project : Breathing LED
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :

uint8_t LEDPin = 7;
uint8_t brightness = 0;
uint8_t delta = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LEDPin, brightness);
  delay(10);
  brightness = brightness + delta;
  if (brightness == 255 || brightness == 0)
  {
    delta = -delta;
  }
}
