#include "led.h"
#include "stm32f4xx.h"

void LED_init()
{

GPIO_InitTypeDef GPIO_InitStructure;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOG,&GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
GPIO_Init(GPIOG,&GPIO_InitStructure);

	
}






