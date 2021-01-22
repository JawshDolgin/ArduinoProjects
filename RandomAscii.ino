//Project : To generate a random ASCII character and have a participant represent the character in binary.
//Author : Joshua Dolgin
//Date  : 2018/10/9
//Status : Working

uint8_t bin1 = 9;/*Uses an unsigned 8 bit integer to rename the pins to their corresponding binary values*/
uint8_t bin2 = 8;
uint8_t bin4 = 7;
uint8_t bin8 = 6;
uint8_t bin16 = 5;
uint8_t bin32 = 4;
uint8_t bin64 = 3;
uint8_t bin128 = 2;
uint8_t greenLED = 13;/*Uses an unsigned 8 bit integer to rename pin 13 to greenLED*/
char randomNumber;/*Creates a character value named randomNumber*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);/*Turns on the Serial Monitor and sets it to 9600 baud*/
  while (!Serial);/*Waits for the Serial Monitor to be ready*/
  pinMode(greenLED, OUTPUT);/*Sets the pin attached to the anode of the greenLED to output*/
  randomSeed(analogRead(0));/*Creates a randomSeed based of the analogRead of pin 0*/
  randomNumber = random(33, 41);/*Creates a random character between 33 and 40*/
  Serial.println("Your random ASCII character is");
  Serial.println(randomNumber); /*Prints the random character on the next line*/
  Serial.println("The integer value is");
  Serial.println((uint8_t) randomNumber);/*Prints the random character as an integer on the next line*/
}

void loop() {
  while (randomNumber == 33)  { /*While the random character is equal to 33*/
    if ( digitalRead(bin1) == HIGH && digitalRead(bin2) == LOW && digitalRead(bin4) == LOW &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
      /*If all of these values are true to the if statement, power will be applied to the anode of
         the green LED, turning it on*/
    {
      digitalWrite(greenLED, HIGH);
    } else
      /*If any of the values are not true to the if statement, no power will be applied to the anode
        of the green LED, turning it off*/
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 34)  {
    if ( digitalRead(bin1) == LOW && digitalRead(bin2) == HIGH && digitalRead(bin4) == LOW &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 35)  {
    if ( digitalRead(bin1) == HIGH && digitalRead(bin2) == HIGH && digitalRead(bin4) == LOW &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 36)  {
    if ( digitalRead(bin1) == LOW && digitalRead(bin2) == LOW && digitalRead(bin4) == HIGH &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 37)  {
    if ( digitalRead(bin1) == HIGH && digitalRead(bin2) == LOW && digitalRead(bin4) == HIGH &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 38)  {
    if ( digitalRead(bin1) == LOW && digitalRead(bin2) == HIGH && digitalRead(bin4) == HIGH &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 39)  {
    if ( digitalRead(bin1) == HIGH && digitalRead(bin2) == HIGH && digitalRead(bin4) == HIGH &&
         digitalRead(bin8) == LOW && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
  while (randomNumber == 40)  {
    if ( digitalRead(bin1) == LOW && digitalRead(bin2) == LOW && digitalRead(bin4) == LOW &&
         digitalRead(bin8) == HIGH && digitalRead(bin16) == LOW && digitalRead(bin32) == HIGH &&
         digitalRead(bin64) == LOW && digitalRead(bin128) == LOW)
    {
      digitalWrite(greenLED, HIGH);
    } else
    {
      digitalWrite(greenLED, LOW);
    }
  }
}
