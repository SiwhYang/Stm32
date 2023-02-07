#include "main.h"
#include "led.h"
#include "delay.h"
#include "usart.h"



void PE_7()
{
GPIO_InitTypeDef GPIO_InitStructure;
//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOE,&GPIO_InitStructure);
	


}

int main(void)
	
{
	LED_init();
	Usart_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // set nvic group 2
	PE_7();
	
	while(1)
	{	
	
		
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);	
		LED_All_TurnOn();
		Delay_us(10);
		GPIO_SetBits(GPIOE,GPIO_Pin_7);	
		LED_All_TurnOff();
		
		Delay_us(10);
		//USART_SendData(USART3,0X11);
		//for(int i = 8 ; i <= 23 ; i++)
		

	}
		
	
	return 0;
}
