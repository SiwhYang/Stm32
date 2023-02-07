#include "main.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"


int main(void)	
{
	LCD_Init();
	Usart_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	LCD_BackLight_Enable;
	while (1)
		{
			LCD_Clear(RED);
			Delay_ms(1000);
			LCD_Clear(GREEN);
			Delay_ms(1000);
			LCD_Clear(BLUE);
			Delay_ms(1000);
		}
	return 0;
}

