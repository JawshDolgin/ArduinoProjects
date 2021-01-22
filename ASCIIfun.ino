//Project : 
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
randomSeed(analogRead(0));
char ascii = random(65, 91);
Serial.println("Here is a random uppercase letter...");
Serial.println(ascii);
Serial.println("The lowercase equivalent is");
Serial.println((char) (ascii|32));


}

void loop() {
  // put your main code here, to run repeatedly:

}
