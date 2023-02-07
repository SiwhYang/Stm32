#include "I3G4250D.h"
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"


void I3G4250D_init()
{

	GPIO_InitTypeDef GPIO_InitStructure;
	// LED
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOG,&GPIO_InitStructure);

	//CS
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = I3G4250D_CS_Pin;
	GPIO_Init(I3G4250D_CS_Port,&GPIO_InitStructure);
	
	// SCK, MISO, MOSI
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = I3G4250D_SCK_Pin | I3G4250D_MISO_Pin | I3G4250D_MOSI_Pin ;
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7, GPIO_AF_SPI5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8, GPIO_AF_SPI5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_SPI5);
	
	
	
	
	// init spi5
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI5, ENABLE);
	SPI_InitTypeDef SPI_InitStruct;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High; // clock is Hight when idle
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge; // data sampled at second edge
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;//|SPI_NSSInternalSoft_Set ; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
	SPI_Init(SPI5, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE); 

  SPI_DataSizeConfig(SPI5, ENABLE);
}



u16 SendByte(u16 data)
{
	u8 retry = 0 ;
	while (SPI_I2S_GetFlagStatus(SPI5,SPI_I2S_FLAG_TXE)== RESET)
		{
			retry++;
			if (retry >200) {return 0;}
		}
	SPI_I2S_SendData(SPI5,data)	;
	
	retry = 0;
	while (SPI_I2S_GetFlagStatus(SPI5,SPI_I2S_FLAG_RXNE) == RESET)
		{
			retry++;
			if (retry >200) {return 0;}
		}
	return SPI_I2S_ReceiveData(SPI5);
}


void writeData(uint8_t address, uint8_t dataToWrite)
{
    GPIO_ResetBits(I3G4250D_CS_Port, I3G4250D_CS_Pin); 
    SendByte(address);
    SendByte(dataToWrite);
    GPIO_SetBits(I3G4250D_CS_Port, I3G4250D_CS_Pin);
}




u8 Read_Data(u8 address)
{
	GPIO_ResetBits(I3G4250D_CS_Port, I3G4250D_CS_Pin); 
	SendByte(address);
	u8 TempByte = SendByte(Dummy_Byte);
	GPIO_SetBits(I3G4250D_CS_Port, I3G4250D_CS_Pin);
	return TempByte;
}



