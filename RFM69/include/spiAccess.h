#pragma once
#include <SPI.h>

#define CHIP_SELECT_PIN   (3)

uint8_t spiInit(void);
bool spiBegin(uint8_t id);
bool spiEnd(uint8_t id);
bool spiRead(uint8_t id, uint16_t length, uint8_t* buff);
bool spiWrite(uint8_t id, uint16_t length, uint8_t* buff);