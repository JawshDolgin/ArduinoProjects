//Project : Arrays
//Author : Joshua Dolgin
//Date  : YYYY/MM//DD
//Status :

uint8_t mon[31];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  uint8_t sixes = 0;
  
  for (uint8_t i = 0; i < 31; i++) {
    mon[i] = random(6)+1;
    if (mon[1] == 6)
    sixes++;
  }
  for (uint8_t i = 0; i < 31; i++) {
    Serial.print( mon[i]);
  }
  Serial.println("\nThere are"+String(sixes));
}

void loop() {
  // put your main code here, to run repeatedly:

}
