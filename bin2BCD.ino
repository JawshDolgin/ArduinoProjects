//Project:
//Author:
//Date: YY/MM/DD
//Status
#include <Wire.h>
#define RTC_ADDRESS B1101000 //0x68

struct dateTime {
  uint8_t Seconds;
  uint8_t Minutes;
  uint8_t Hours;
  uint8_t Day;
  uint8_t Date;
  uint8_t Month;
  uint8_t Year;
} dt;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //  Serial.println(bin2BCD(89));
  //  Serial.println(BCD2bin(59));
  setDateTime(10, 38, 8, 2, 30, 4, 19);
}

dateTime readDateTime() {
  dateTime info;
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0);
  Wire.endTransmission(RTC_ADDRESS);
  Wire.requestFrom(RTC_ADDRESS, 7);
  info.Seconds = BCD2bin(Wire.read() & 0x7F);
  info.Minutes = BCD2bin(Wire.read());
  info.Hours = BCD2bin(Wire.read());
  info.Day = BCD2bin(Wire.read());
  info.Date = BCD2bin(Wire.read());
  info.Month = BCD2bin(Wire.read());
  info.Year = BCD2bin(Wire.read()) + 2000;
  return info;
}
void displayDateTime(dateTime luc) {
  Serial.print(String(2000+luc.Year) + " ");
  Serial.print(String(luc.Month) + " ");
  Serial.print(String(luc.Date) + " ");
  Serial.print(String(luc.Day) + " ");
  Serial.print(String(luc.Hours) + " ");
  Serial.print(String(luc.Minutes) + " ");
  Serial.println(String(luc.Seconds) + " ");


}

void setDateTime(uint8_t Sec, uint8_t Min, uint8_t Hour, uint8_t Day, uint8_t Date, uint8_t Month, uint8_t Year) {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0);
  Wire.write(bin2BCD(Sec));
  Wire.write(bin2BCD(Min));
  Wire.write(bin2BCD(Hour));
  Wire.write(bin2BCD(Day));
  Wire.write(bin2BCD(Date));
  Wire.write(bin2BCD(Month));
  Wire.write(bin2BCD(Year));
  Wire.endTransmission();
}

uint8_t bin2BCD(uint8_t value) {
  uint8_t temp = (value >> 4) * 10 + value % 10;
  return temp;
}

uint8_t BCD2bin(uint8_t value) {
  return value / 16 * 10 + (value & 0x0F); //bitwise masking to remove top nibble
}

void loop() {
  dt = readDateTime();
  displayDateTime(dt);
  delay(3000);
}
