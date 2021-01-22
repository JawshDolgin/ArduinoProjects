


// the setup function runs once when you press reset or power the board
void setup() {
 DDRB = 1<<PB5;
}

// the loop function runs over and over again forever
void loop() {
 PORTB ^= (1<<PB5);
 delay(1000);
}
