// PROJECT: NRF Simple V2
// PURPOSE: A receiver NRF
// DEVICE:  Arduino
// AUTHOR:  Daniel
// DATE:    2019-02-05

#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
uint8_t data;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);  // Give channel to communicate on
  radio.setPALevel(RF24_PA_MIN);      // Set PA level
  radio.startListening();             // Set to be receiver
  DDRD = 0x0F;                        // Set LEDs to output
  
}
void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));  // Read in the data when it is available
    PORTD = data;                     // Output the values onto the LEDs
  }
}

/*
 
  radio.openReadingPipe(uint8_t child, uint64_t address) {
    memcpy(pipe0_reading_address,&address,addr_width);
  }

  radio.startListening(void) {  
    write_register(NRF_CONFIG, read_register(NRF_CONFIG) | _BV(PRIM_RX));
    write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
    digitalWrite(ce_pin, HIGH);
    
    // Restore the pipe0 adddress, if exists
    write_register(RX_ADDR_P0, pipe0_reading_address, addr_width);  

    // Flush buffers
    //flush_rx();
    if(read_register(FEATURE) & _BV(EN_ACK_PAY)){
      flush_tx();
    }
  }

  radio.read(void* buf, uint8_t len) {
    // Fetch the payload
    read_payload( buf, len );

    //Clear the two possible interrupt flags with one command
    write_register(NRF_STATUS,_BV(RX_DR) | _BV(MAX_RT) | _BV(TX_DS) );
  }

  uint8_t read_payload(void* buf, uint8_t data_len) {
    uint8_t status;
    uint8_t* current = reinterpret_cast<uint8_t*>(buf);

    if(data_len > payload_size) data_len = payload_size;
    uint8_t blank_len = dynamic_payloads_enabled ? 0 : payload_size - data_len;

    beginTransaction();
    status = _SPI.transfer( R_RX_PAYLOAD );
    while ( data_len-- ) {
      *current++ = _SPI.transfer(0xFF);
    }
    while ( blank_len-- ) {
      _SPI.transfer(0xff);
    }
    endTransaction();

    return status;
  }
*/
