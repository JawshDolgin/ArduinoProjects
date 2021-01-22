//Project:
//Author:
//Date: YY/MM/DD
//Status
#include <Wire.h> //include for I2C devices
#include <RTClib.h>
RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);
  //rtc.adjust(DateTime(2019, 4, 12, 14, 38));
  //rtc.adjust(1555093860L);
  rtc.adjust(DateTime( (__DATE__), (__TIME__)  ));
}


void loop()
{
  DateTime dt = rtc.now();
  Serial.println(dt.year());
  Serial.println(dt.month());
  Serial.println(dt.day());
  Serial.print(dt.hour());
  Serial.print(": ");
  Serial.print(dt.minute());
  Serial.print(": ");
  Serial.println(dt.second());
  delay(500);
}
