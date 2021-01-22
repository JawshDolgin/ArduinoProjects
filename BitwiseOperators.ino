//Project : 
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :
//Reference :



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
while(!Serial);
Serial.println(15<<1);// Multiplying by 2 (Move 2 positions left)
Serial.println(15<<2);//Multiplying by 4 (Move 4 positions left)
Serial.println(15<<3);//Multiplying by 8 (Move 8 positions left)
Serial.println(23>>1);//Dividing by 2 (Move 2 positions right)
Serial.println(23>>2);//Dividing by 4 (Move 4 positions right)
Serial.println(11 & 5);//And gate 
Serial.println(11|5);//Or gate 
Serial.println(11^5);//XOR gate ( Different is true, same is false)
Serial.println(~1);//Not one (invert the bits) runs through 2's compliment 
Serial.println(~5<<2);//Not 5 shift left 2 (Invert the bits then shift left 2)
Serial.println(100<<~1);// 
Serial.println(15 & 7 << 1);//
Serial.println(0xAA & 36);//
Serial.println(254|1);//
Serial.println(~10^1<<2);//

 

}

void loop() {
  // put your main code here, to run repeatedly:

}
