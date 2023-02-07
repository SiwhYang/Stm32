#ifndef __USART_H__
#define __USART_H__
#include "stm32f30x.h"

void Usart_Init(void);
void USART3_IRQHandler(void);
void Usart_SendDate(u8 data);

void USART3_printf(u16 data);
void SPI_ReadByte();


#endif


