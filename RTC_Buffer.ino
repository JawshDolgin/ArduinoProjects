//Project:
//Author:
//Date: YY/MM/DD
//Status
#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 rtc;
DateTime dt;
#include <LiquidCrystal.h>
uint8_t RS = 7, EN = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
#define LCD_COLUMNS  16
#define LCD_ROWS 2

char buffer[LCD_COLUMNS];

void setup() {
  rtc.begin();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  rtc.adjust(DateTime( (__DATE__), (__TIME__)  ));
  Serial.begin(9600);
}

void loop() {
  dt = rtc.now();
  Serial.println(dt.year());
  Serial.println(dt.month());
  Serial.println(dt.day());
  Serial.print(dt.hour());
  Serial.print(": ");
  Serial.println(dt.minute());
  /*lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time:");
  lcd.print(dt.hour());
  lcd.print(":");
  lcd.print(dt.minute());
  lcd.print(":");
  lcd.print(dt.second());
  lcd.setCursor(0, 1);
  lcd.print("Date:");
  lcd.print(dt.year());
  lcd.print(":");
  lcd.print(dt.day());
  delay(1000);
  */
  lcd.setCursor(0,0);
  sprintf(buffer, "TIME: %02d:%02d:%02d", dt.hour(), dt.minute(), dt.second());
  lcd.print(buffer);
  lcd.setCursor(0,1);
  sprintf(buffer, "Date: %4d/%02d/%02d", dt.year(), dt.month(), dt.day());
  lcd.print(buffer);
  delay(1000);
}
