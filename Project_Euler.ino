//Project : Project Euler. Problem 1 (find the sum of the multiples 3 or 5 less than 1000);
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :

uint32_t total = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  for (uint16_t i = 3; i < 1000; i++) {
    if( i%3 == 0|| i%5 == 0)
    total = total += i;
    
  }

Serial.println("the total is "+String(total));
}

void loop() {

}
