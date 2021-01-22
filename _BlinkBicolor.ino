// PROJECT  :BlinkBicolor
// PURPOSE  :To reinforce concepts involving register-level manipulation of //       : GPIO Ports and bitwise logic
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 09 22
// uC       :328P
// COURSE   :ICS3U
// STATUS   :Working
void setup() {
  DDRB = 0x3F;      // ?
  PORTB = 1;        // ?
}
void loop() {
  PORTB = ~PORTB;   // ?
  delay(1000);      // ?
}
