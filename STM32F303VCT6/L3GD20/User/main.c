#include "main.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "spi.h"


int main(void)	
{
	Spi_Init();
	Usart_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // set nvic group 2
	
	
	//writeData(0x20, 0x0F);
	
	while (1)
		{
		
			u8 ID_address = 0x0F|0x80;
			u8 CTRL_REG1_address = 0x20|0x80;
			u8 X_angular_address = 0x28|0x80; // 
			u8 Y_angular_address = 0x2B|0x80; //
			u8 Z_angular_address = 0x2D|0x80; //
			u8 test_address = 0x0F|0x80;
			
			u8 ID = Read_Data(ID_address);
			u8 CTRL_REG1 = Read_Data(CTRL_REG1_address);
			u8 X_angular = Read_Data(X_angular_address);
			u8 Y_angular = Read_Data(Y_angular_address);
			u8 Z_angular = Read_Data(Z_angular_address);
			u8 test = Read_Data(test_address);
			
			
			USART3_printf(test);
			Delay_ms(100);
			
			
			
			//USART3_printf(ID);
			//Delay_ms(100);
			//USART3_printf(CTRL_REG1);
			//Delay_ms(100);
			//USART3_printf(X_angular);
			//Delay_ms(100);
			//USART3_printf(Y_angular);
			//USART3_printf(Z_angular);
			
			
			
			

		}
	return 0;
}
