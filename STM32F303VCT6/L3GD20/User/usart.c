#include "usart.h"
#include "stm32f30x_usart.h"
#include "spi.h"

void Usart_Init(void)	
{
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOC, ENABLE); //enable usart time clock of gpio
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); // enable usart time clock which locate in APB2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_7);
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //key
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;   // key, this has to be set read and recieve, if set only read, it fail at send and receive exp
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // key
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //key
	USART_Init(USART3,&USART_InitStruct);
	USART_Cmd(USART3,ENABLE); // turn on
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE); // second parmeter is set to read for we use read mode of usart1 
	// this meand we turn on read interupt on usart1
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn; //on top header stm32f0x.h with ORQN suffix, means which channel
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;// means enable or not
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;// set PreemptionPriority we have 0-3 because we have group 2, this is arbitrary for now because we have no other  interrupt  
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	

}


void USART3_printf(u16 data)
{
	USART_SendData(USART3,data);
}




void USART3_IRQHandler (void)
{
	
	u8 res;
	u8 res_;
	if (USART_GetITStatus(USART3,USART_IT_RXNE))
	{
		res = USART_ReceiveData(USART3);
		res_ = res;
		USART_SendData(USART3,res_); 
	}
}

