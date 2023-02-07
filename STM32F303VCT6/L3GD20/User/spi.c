#include "spi.h"
#include "stm32f30x.h"
#include "stm32f30x_spi.h"


// for spi1 we use PA_5 PA_6 PA_7 as SCK, MISO, MOSI (GPIO_AF_5), and PE3 as CS 
void Spi_Init()
{	
	//init PA
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6, GPIO_AF_5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7, GPIO_AF_5);
		
	// init PE
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
		
	// init spi1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitTypeDef SPI_InitStruct;
	//SPI_I2S_DeInit(SPI1);
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High; // clock is Hight when idle
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge; // data sampled at first edge
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//|SPI_NSSInternalSoft_Set ; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE); 

	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
  SPI_DataSizeConfig(SPI1, ENABLE);
	
	
	GPIO_SetBits(GPIOE,GPIO_Pin_3); // set cs as open
}



void writeData(uint8_t address, uint8_t dataToWrite)
{
    GPIO_ResetBits(GPIOE, GPIO_Pin_3); 
    SendByte(address);
    SendByte(dataToWrite);
    GPIO_SetBits(GPIOE, GPIO_Pin_3);
}


u8 SendByte(u8 data)
{
	u8 retry = 0 ;
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)== RESET)
		{
			retry++;
			if (retry >200) {return 0;}
		}
	SPI_SendData8(SPI1,data)	;
	
	retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET)
		{
			retry++;
			if (retry >200) {return 0;}
		}
	return SPI_ReceiveData8(SPI1);
}

u8 Read_Data(u8 address)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_3);
	SendByte(address);
	u8 TempByte = SendByte(Dummy_Byte);
	GPIO_SetBits(GPIOE,GPIO_Pin_3);
	return TempByte;
}




