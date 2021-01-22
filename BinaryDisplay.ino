// PROJECT  :Binary Display
// PURPOSE  :(Skeleton) Demonstration of Mathematics' Challenge on p. 19
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 10 23
// uC       :328
// COURSE   :ICS3U
// STATUS   :Not (Quite) Working - You complete it :)

#define MAXIMUM 1023    // the upper bound of our display

// an array of pin numbers to which LEDs are attached
uint8_t ledPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
uint8_t ledCount = sizeof(ledPins); // the number of LEDs in the bar graph

void setup() {
  // loop over the pin array and set them all to output...
  for (uint8_t thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}
void loop() {
  for (uint16_t value = 0; value < MAXIMUM; value++) {
    // display values in succession by testing each bit...
    for (uint8_t bit = 0; bit < 10; bit++) {
      digitalWrite(ledPins[bit], value & 1<<bit);
      //turn the bar on (HIGH) if the bit is SET; or off if the bit is CLEAR
//      if (value & 1<<bit)    // test if a specific bit is set.... 
//          digitalWrite(ledPins[bit], HIGH); // if so, light the corresponding bar
//        else
//          digitalWrite(ledPins[bit], LOW);  // if not, leave the bar off
//      // once the if statement works above, replace it with this single statement that does both
//      // digitalWrite(ledPins[bit],???);
    }
    delay(100);  // admire your brilliance
  }
}
