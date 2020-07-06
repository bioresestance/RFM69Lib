#include <Arduino.h>
#include <SPI.h>
#include <stdio.h>
#include <..\lib\RFM69Lib\RFM69.h>
#include <esp_freertos_hooks.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


//#define trace_test(fmt,...)		printf((fmt), ##__VA_ARGS__)

#define CHIP_SELECT_PIN   (3)

static RFM69 module;

//! SPI settings used to communicate with the RFM69 module. Set to half max speed.
static SPISettings spiSettings = SPISettings( RFM69::max_spi_clock / 2 , MSBFIRST, SPI_MODE0);

/***************************Prototypes********************************************/
uint8_t spiInit(void);
bool spiBegin(uint8_t id);
bool spiEnd(uint8_t id);
bool spiRead(uint8_t id, uint16_t length, uint8_t* buff);
bool spiWrite(uint8_t id, uint16_t length, uint8_t* buff);

void setup() {

  //uint8_t test1 = 0, test2 = 1;
  //trace_test( "This is a test %d %d" , test1, test2);


  // Initialize the spi access functions.
  module.spi_attach(&spiInit, &spiBegin, &spiEnd, &spiRead, &spiWrite);
}

void loop() {
  // put your main code here, to run repeatedly:

}


uint8_t spiInit(void) {

  // Stores the current ID to be returned. 
  static uint8_t curr_ID = 0;

  // Set up pin modes
  //TODO

  // Initialize SPI.
  SPI.begin();

  // Return the current ID.
  return curr_ID++;
}


bool spiBegin(uint8_t id) {
  //TODO, If multiple spi device, use ID to select proper chip. For now, we are ignoring it.
  // Start the transaction.
  SPI.beginTransaction(spiSettings);
  //Select the Chip select line.
  digitalWrite(CHIP_SELECT_PIN, LOW);
  return true;
}


bool spiEnd(uint8_t id) {
  //Select the Chip select line.
  digitalWrite(CHIP_SELECT_PIN, HIGH);
  SPI.endTransaction();
  return true;
}


bool spiRead(uint8_t id, uint16_t length, uint8_t* buff) {

  // Input Validation.
  if( length == 0 || buff == nullptr) {
    return false;
  }

  //Read in the given number of bytes from the device.
  for(uint16_t i = 0; i < length; i++ ) {
    buff[i] = SPI.transfer(0);
  }
  return true;
}


bool spiWrite(uint8_t id, uint16_t length, uint8_t* buff) {

  // Input Validation.
  if( length == 0 || buff == nullptr) {
    return false;
  }

  //Read in the given number of bytes from the device.
  for(uint16_t i = 0; i < length; i++ ) {
    buff[i] = SPI.transfer(0);
  }
  return true;
}