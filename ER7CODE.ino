//Project : To generate a random ASCII character and have a participant represent the character in binary.
//Author : Joshua Dolgin
//Date  : 2018/10/9
//Status : Working


uint8_t bin1 = 2;/*Uses an unsigned 8 bit integer to rename pin 2-9 to their binary values*/
uint8_t bin2 = 3;
uint8_t bin4 = 4;
uint8_t bin8 = 5;
uint8_t bin16 = 6;
uint8_t bin32 = 7;
uint8_t bin64 = 8;
uint8_t bin128 = 9;
uint8_t greenLED = 13;
uint8_t randomNumber; /*Creates a unsigned 8 bit integer named randomNumber*/
uint8_t binaryInput = 0;/*Creates an unsigned 8 bit integer equal to 0*/




void setup() {
  Serial.begin(9600);
  pinMode(greenLED, OUTPUT);/*Sets the LED pin to output*/
  while (!Serial); /*waiting for serial monitor to start*/
  randomSeed(analogRead(0));/*Uses the analog read on pin 0 to generate a randomseed*/
  randomNumber = random(33, 127);/*Creates a random integer between 33 and 126*/
  Serial.println("Your Random ASCII character is");
  Serial.println((char) randomNumber);/*Prints the random integer as a character*/
  Serial.println("The integer value is");
  Serial.println(randomNumber); /*Prints it as an integer*/
}

void loop() { 
  binaryInput = binaryInput+((digitalRead(bin1)));
  binaryInput = binaryInput+((digitalRead(bin2)<<1));
  binaryInput = binaryInput+((digitalRead(bin4)<<2));
  binaryInput = binaryInput+((digitalRead(bin8)<<3));
  binaryInput = binaryInput+((digitalRead(bin16)<<4));
  binaryInput = binaryInput+((digitalRead(bin32)<<5));
  binaryInput = binaryInput+((digitalRead(bin64)<<6));
  binaryInput = binaryInput+((digitalRead(bin128)<<7));
  if (binaryInput == randomNumber) { /*If the binaryInbut is equal to randomNumber, then it turns on the greenLED*/
    digitalWrite(greenLED, HIGH);
  } else
  {/*If binaryInput is not equal to randomNumber, the LED is turned off and binaryInput is set back to 0*/
    digitalWrite(greenLED, LOW);
    binaryInput == 0;
  }
}
