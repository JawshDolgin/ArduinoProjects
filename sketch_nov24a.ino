//Project:
//Author: Josh Dolgin
//Date: YY/MM/DD
//Status:

uint16_t score = 0;
uint8_t binarySwitch = 4;
uint8_t signedSwitch = 5;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(PORTD, OUTPUT);
}

void binaryValue() {
  uint8_t binValue = random(0, 255);
  return binValue;
  Serial.println(binValue);
}

void signedValue() {
  int8_t signValue = random(-128, 127);
  return signValue;
  Serial.println(signValue);
}

void hexadecimalValue(){
  uint8_t hexValue = random(0x00, 0xFF);
  return  hexValue; 
  Serial.println(hexValue);
}

void loop() {
  while (binarySwitch) {
    binaryValue();
    if ( digitalRead(PORTD) != binaryValue) {
    }else{
      score = score + 10;
    }
  }
  while (signedSwitch) {
    signedValue();
    if ( digitalRead(PORTD) != signedValue) {
    } else{
      score = score + 10;
    }
  }
  while(binarySwitch && signedSwitch){
    hexadecimalValue();
    if( digitalRead(PORTD) != hexadecimalValue){
    }else{
      score = score + 10;
    }
  }
}
