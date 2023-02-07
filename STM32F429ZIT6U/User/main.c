
#include "main.h"
#include "stm32f4xx.h"
#include "led.h"

int main(void)
{  
	LED_init();
     
  /* Infinite loop */
  while (1)
  {
		GPIO_SetBits(GPIOG,GPIO_Pin_13);
		GPIO_SetBits(GPIOG,GPIO_Pin_14);
  }
}
