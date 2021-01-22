// PROJECT  :ShiftBar Echo
// PURPOSE  :Echoes ASCII characters entered in the Serial Monitor of the ShiftBar device
// DEVICE   :Arduino
// AUTHOR   :C. D'Arcy
// DATE     :2018 10 29
// uC       :328/84/85
// COURSE   :ICS3U
// STATUS   :Working
// You'll likely need to edit the three pin assignments below...
uint8_t clk = 10;        //SRCLK
uint8_t data = 8;      //SER
uint8_t latch = 9;     //RCLK
#define DURATION 500   //pause between displays.... 

void setup() {
  Serial.begin(9600);
  pinMode(clk, OUTPUT);   //declare the 3 '595 control lines for output  
  pinMode(data, OUTPUT);  //
  pinMode(latch, OUTPUT); //
  while (!Serial);        //wait for the Serial monitor to initialize itself
}

void loop() {
  while (!Serial.available());  //wait until characters are in the stream buffer
  char ch = Serial.read();      //grab them, one at a time...
  digitalWrite(latch, LOW);           //prepare to load shift register flipflops...
  shiftOut(data, clk, LSBFIRST, ch);  //clock 'em in....
  digitalWrite(latch, HIGH);          //present f/f on the output pins
  Serial.println(ch);                 //write to Serial Monitor for confirmation
  delay(DURATION);              //admire their beauty...
}
