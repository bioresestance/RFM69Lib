#include <Arduino.h>
#include <spiAccess.h>
#include <stdio.h>
#include <RFM69.h>
#include <esp_freertos_hooks.h>
#include <FreeRTOS.h>
#include <freertos/task.h>


static RFM69 module;

/***************************Prototypes********************************************/


void setup() {


  // Initialize the spi access functions.
  module.spi_attach(&spiInit, &spiBegin, &spiEnd, &spiRead, &spiWrite);
}

void loop() {
  // put your main code here, to run repeatedly:

}
