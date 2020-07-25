#include <Arduino.h>
#include <spiAccess.h>
#include <RFM69.h>

using namespace RFM69Radio;

static RFM69 module;

/***************************Prototypes********************************************/
void printCurrMode() {
  Serial.printf("Current mode is 0x%02X\n", (uint8_t) module.get_mode() );
}


void setup() {

  //Serial Debugging.
  Serial.begin(9600);
  delay(2000);

  // Initialize the spi access functions.
  module.spi_attach(&spiInit, &spiBegin, &spiEnd, &spiRead, &spiWrite);

  spiInit();
  Serial.println("Starting");
  delay(2000);
  do {
    module.set_mode(RFM69::OpMode::RECEIVE);
  } while(module.get_mode() != RFM69::OpMode::RECEIVE );
  
}

void loop() {

  printCurrMode();

  delay(1000);
}
