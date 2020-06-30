#include <Arduino.h>
#include <..\lib\RFM69Lib\RFM69.h>
#include <esp_freertos_hooks.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static RFM69 module();
static RegOpMode test();


uint8_t spiInit(void);
bool spiRead(uint8_t id, uint16_t length, uint8_t* buff);
bool spiWrite(uint8_t id, uint16_t length, uint8_t* buff);

void setup() {
  

  
}

void loop() {
  // put your main code here, to run repeatedly:

}


uint8_t spiInit(void) {

}

bool spiRead(uint8_t id, uint16_t length, uint8_t* buff) {


}

bool spiWrite(uint8_t id, uint16_t length, uint8_t* buff) {


}