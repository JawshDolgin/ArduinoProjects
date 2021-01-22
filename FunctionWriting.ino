//Project :
//Author  : Josh Dolgin
//Device  :
//Date    : YY/MM/DD
//Status  :
//MCU     :
//Notes   :

uint8_t findLargest(uint8_t a, uint8_t b, uint8_t c) {
  uint8_t larger;
  larger = a >= b ? a : b;
  larger = larger >= c ? larger : c;
  return larger;
}

uint8_t BCD2dec(uint8_t BCD){
  uint8_t dec = 10*(BCD>>4) + (BCD & 0x0F);
  return dec;
}

uint8_t dec2BCD(uint8_t dec){
  uint8_t BCD = (dec/10)<<4 + dec%10;
  return BCD;
}

void setup() {
  Serial.begin(9600);
  Serial.println("The largest number is:  " + String(findLargest(1, 2, 3)));
  Serial.println(BCD2dec(0x29));
  Serial.println(dec2BCD(29));
}

void loop() {


}
