#ifndef _SPI_H_
#define _SPI_H_
#include "stm32f30x.h"


void Spi_Init(void);


void writeData(uint8_t address, uint8_t dataToWrite);
u8 SendByte(u8 data);
u8 Read_Data(u8 address);

u16 CombineSendByte(u8 data);
u8 CombineReadData(u8 address);
#endif
