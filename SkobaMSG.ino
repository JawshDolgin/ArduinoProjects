//Project: Skoba MSGEQ7
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:
#include <LiquidCrystal.h>
int analogPin = A4; // read from multiplexer using analog input 0
int strobePin = 11; // strobe is attached to digital pin 2
int resetPin = 10; // reset is attached to digital pin 3
int spectrumValue[7]; // to hold a2d values
uint8_t LCD_COLUMNS = 16;
uint8_t LCD_ROWS = 2;
uint8_t RS=7, EN=6, D4=5, D5=4, D6=3, D7=2;

LiquidCrystal lcd (RS,EN,D4,D5,D6,D7);

uint8_t eqLevels [8][8] = {
  {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111},
  {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111},
  {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111},
  {0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111},
  {0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},
  {0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},
  {0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111},
  {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111}  
};

void setup()
{
 Serial.begin(9600);
 pinMode(analogPin, INPUT); //Not needed
 pinMode(strobePin, OUTPUT);
 pinMode(resetPin, OUTPUT);
 analogReference(DEFAULT);

 digitalWrite(resetPin, LOW);
 digitalWrite(strobePin, HIGH);
 lcd.begin(LCD_COLUMNS, LCD_ROWS);
 for(uint8_t j = 0; j<7; j++){
  lcd.createChar(j, eqLevels[j]);
 }

 Serial.println("MSGEQ7 test by J Skoba");
}

void readFrequencies(){
   digitalWrite(resetPin, HIGH);
 digitalWrite(resetPin, LOW);

 for (int i = 0; i < 7; i++)
 {
 digitalWrite(strobePin, LOW);
 delayMicroseconds(30); // to allow the output to settle
 spectrumValue[i] = analogRead(analogPin);
 Serial.print(" ");
 Serial.print(spectrumValue[i]);
 digitalWrite(strobePin, HIGH);
 }
 Serial.println();
}

void displayEqualizer(){
  lcd.setCursor(0,0);
  for(uint8_t i = 0; i<7; i++){
    lcd.write(spectrumValue[i] >> 7);
  }
}

void loop()
{
  readFrequencies();
  displayEqualizer();
}
