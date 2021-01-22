//Project : 
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :
float multiplier = 5.0/1023;
uint16_t value;
float voltageLevel;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
value = analogRead(A1);
voltageLevel = value*multiplier;
Serial.println(voltageLevel);
}
