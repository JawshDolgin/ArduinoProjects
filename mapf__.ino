//Project : Our Map Function
//Author : Joshua Dolgin
//Date  : 2018/10/15
//Status : Working

float a = 10.5;
float b = 19.7;
float x = 11.6;
float e = 48.7;
float f = 93.21;


void setup() {
  Serial.begin(9600);
  uint16_t reading = analogRead(A4);
  Serial.println( map (reading, 0, 1023, 0, 5) ); /* map is limited to integers */
  //  Serial.println( mapf(x, a, b, e, f)  );
  float result = mapf (x, a, b, e, f);
  Serial.println( result );

}

float mapf ( float ex, float eh, float bee, float ee, float eff) {

  //  float y = (ex - eh) / (bee - eh) * (eff - ee) + ee;
  //  return y;
  return (ex - eh) / (bee - eh) * (eff - ee) + ee;
}

void loop() {


}
