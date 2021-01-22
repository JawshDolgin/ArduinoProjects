// PROJECT  :Binary Decomposition 
// PURPOSE  :Demonstrates both iterative and recursive algorithms
//          : for converting decimal to binary (binary decomposition) 
// DEVICE   :n/a
// AUTHOR   :C. D'Arcy
// DATE     :2018 10 10
// COURSE   :ICS3U
// STATUS   :Working

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  uint8_t value = random(256);
  Serial.println("The binary equivalent of "+String(value)+" is..."); 
  binaryDecompositionIterative(value,1<<7);
//  binaryDecompositionRecursive(value,1<<7);
}

void binaryDecompositionIterative(uint8_t value, uint8_t power){
  while (power>0){
      Serial.print(value/power);
      value %= power;
      power>>=1;
  }    
}

void binaryDecompositionRecursive(uint8_t value, uint8_t power){
  if (power>0){
      Serial.print(value/power);
      binaryDecompositionRecursive(value%power,power>>1);
  }    
}

void loop() {
}
