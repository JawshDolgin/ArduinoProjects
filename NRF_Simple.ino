// PROJECT: Simple NRF
// PURPOSE: The most basic NRF Sketch: Sending an integer between two Arduinos
// DEVICE:  Arduino
// AUTHOR:  Daniel Raymond
// DATE:    2019-02-05

#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";   // Address String
uint8_t data = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);         // Give channel to communicate on
  radio.setPALevel(RF24_PA_MIN);          // Set Power Amplifier Level
  radio.stopListening();                  // Set to be the transmitter
}

void loop() {
  radio.write(&data, sizeof(data));       // Write the data to the channel
  delay(1000);
  data = (data + 1) % 0x0F;               // Cycle from 0 - 1111
  Serial.println(data, BIN);
}

/*
  radio.begin() {
    pinMode(csn_pin,OUTPUT);
    pinMode(ce_pin,OUTPUT);
    _SPI.begin();
    digitalWrite(ce_pin,LOW);
    digitalWrite(csn_pin,HIGH);
  }
 
  radio.openWritingPipe(const uint8_t *address) {
    // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
    // expects it LSB first too, so we're good.
    write_register(RX_ADDR_P0,address, addr_width);
    write_register(TX_ADDR, address, addr_width);
    write_register(RX_PW_P0,payload_size);
  }

  uint8_t write_register(uint8_t reg, const uint8_t* buf, uint8_t len) {
    uint8_t status;
  
    beginTransaction();
    status = _SPI.transfer( W_REGISTER | ( REGISTER_MASK & reg ) );
    while ( len-- )
    _SPI.transfer(*buf++);
    endTransaction();

    return status;
  }

  

  radio.stopListening(void) {  
    digitalWrite(ce_pin,LOW);

    delayMicroseconds(txDelay); // 200
  
    if(read_register(FEATURE) & _BV(EN_ACK_PAY)){
      delayMicroseconds(txDelay); //200
      flush_tx();
    }
    //flush_rx();
    write_register(NRF_CONFIG, ( read_register(NRF_CONFIG) ) & ~_BV(PRIM_RX) );
    write_register(EN_RXADDR,read_register(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[0]))); // Enable RX on pipe0
  }

  radio.write(const void* buf, uint8_t len) {
    startFastWrite(buf,len);
    digitalWrite(ce_pin, LOW);
    uint8_t status = write_register(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
  }

  radio.startFastWrite(const void* buf, uint8_t len, bool startTx = 1) {
    write_payload( buf, len, W_TX_PAYLOAD ) ;
    if(startTx)   // I think it will always be 1
      ce(HIGH);
  }

  uint8_t write_payload() {
    uint8_t status;
    const uint8_t* current = reinterpret_cast<const uint8_t*>(buf);
  
    data_len = data_len < payload_size : data_len : payload_size
    // data_len = rf24_min(data_len, payload_size);
    uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;

    beginTransaction();
    status = _SPI.transfer( writeType );
    while ( data_len-- ) {
      _SPI.transfer(*current++);
    }
    while ( blank_len-- ) {
      _SPI.transfer(0);
    }  
    endTransaction();

    return status;
  }

  uint8_t flush_rx() {
    uint8_t status;
  
    beginTransaction();
    status = _SPI.transfer( FLUSH_RX );
    endTransaction(); 
    
    return status;
  }

  uint8_t flush_tx() {
    uint8_t status;
  
    beginTransaction();
    status = _SPI.transfer( FLUSH_TX );
    endTransaction();
    
    return status;
  }
*/
