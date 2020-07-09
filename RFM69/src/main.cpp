#include <Arduino.h>
#include <spiAccess.h>
#include <stdio.h>
#include <RFM69.h>
#include <esp_freertos_hooks.h>
#include <FreeRTOS.h>
#include <freertos/task.h>


static RFM69 module;
static RegOpMode reg;

/***************************Prototypes********************************************/


void setup() {

  //Serial Debugging.
  Serial.begin(9600);

  // Initialize the spi access functions.
  module.spi_attach(&spiInit, &spiBegin, &spiEnd, &spiRead, &spiWrite);
  //reg.set_byte(0x00);
}

void loop() {
  Serial.println("Testing");
  delay(1000);

  module.read_reg(reg);

  Serial.println(reg.get_byte());
}
