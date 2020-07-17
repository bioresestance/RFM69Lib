#include <Arduino.h>
#include <spiAccess.h>
#include <RFM69.h>


static RFM69 module;
static RegOpMode reg;

/***************************Prototypes********************************************/


void setup() {

  //Serial Debugging.
  Serial.begin(9600);

  // Initialize the spi access functions.
  module.spi_attach(&spiInit, &spiBegin, &spiEnd, &spiRead, &spiWrite);

  spiInit();
    Serial.println("Starting");
}

void loop() {

  //delay(100);
  //Serial.println();
  // SPI.beginTransaction(SPISettings( RFM69::max_spi_clock /10 , MSBFIRST, SPI_MODE0) );
  // digitalWrite(CHIP_SELECT_PIN, LOW);
  // Serial.println();
  // SPI.transfer(addr & 0x7F);
  // uint8_t regVal = SPI.transfer(0);
  // digitalWrite(CHIP_SELECT_PIN, HIGH);
  // SPI.endTransaction();

  uint8_t byte = 0xAA;
  uint8_t data;
  do {
    module.write_reg(RFM69RegisterAddresses::RegSyncValue1, sizeof(byte), &byte);
    module.read_reg(RFM69RegisterAddresses::RegSyncValue1, sizeof(data), &data);
  }while (data != byte);
  byte = 0x55;
  do {
    module.write_reg(RFM69RegisterAddresses::RegSyncValue1, sizeof(byte), &byte);
    module.read_reg(RFM69RegisterAddresses::RegSyncValue1, sizeof(data), &data);
  }while (data != byte);

  Serial.println("Completed!!!");

}
