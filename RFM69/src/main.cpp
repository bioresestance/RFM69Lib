#include <Arduino.h>
#include <spiAccess.h>
#include <stdio.h>
#include <RFM69.h>
#include <esp_freertos_hooks.h>
#include <FreeRTOS.h>
#include <freertos/task.h>


static RFM69 module;

static RegTemp1 reg;

/***************************Prototypes********************************************/


void setup() {


  // Initialize the spi access functions.
  module.spi_attach(&spiInit, &spiBegin, &spiEnd, &spiRead, &spiWrite);


uint8_t byte = reg.get_byte();

}

void loop() {
  // put your main code here, to run repeatedly:

}
