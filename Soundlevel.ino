//Project : 
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial);

}

void loop() {
  // put your main code here, to run repeatedly:
uint16_t soundLevel = analogRead(A0);
Serial.println(soundLevel);
delay(200);
}
