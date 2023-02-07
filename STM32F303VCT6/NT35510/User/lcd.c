#include "lcd.h"
#include "stm32f30x.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Pin define on stm32f3 discovery and NT35510 module


// CS -> PF10  
// RS -> PF9
// WR -> PF1 !! ->PB9
// RD -> PF0 !! ->PB7
// RST -> PC15

// D0 -> PC14 
// D1 -> PC13  
// D2 -> PE6 
// D3 -> PE4 !! -> PA3
// D4 -> PE5 !! -> PC3

// D5 -> PE14 
// D6 -> PE15
// D7 -> PB10
// D8 -> PB11
// D9 -> PB12
// D10 -> PB13
// D11 -> PB15
// D12 -> PB14
// D13 -> PD8
// D14 -> PD9 !! -> PC2 ->PA1
// D15 -> PC1
// BL -> PC9



void LCD_Init()
{	
	
	GPIO_InitTypeDef GPIO_InitStructure ;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF,ENABLE);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	
	
	// Init Switch Pin
	// Init Cs
	GPIO_InitStructure.GPIO_Pin = LCD_CS_Pin ;
	GPIO_Init(LCD_CS_Port,&GPIO_InitStructure);
	// Init Rs
	GPIO_InitStructure.GPIO_Pin = LCD_RS_Pin ;
	GPIO_Init(LCD_RS_Port,&GPIO_InitStructure);
	// Init WR
	GPIO_InitStructure.GPIO_Pin = LCD_Write_Pin ;
	GPIO_Init(LCD_Write_Port,&GPIO_InitStructure);
	// Init RD
	GPIO_InitStructure.GPIO_Pin = LCD_Read_Pin	;
	GPIO_Init(LCD_Read_Port,&GPIO_InitStructure);
	// Init Reset
	GPIO_InitStructure.GPIO_Pin = LCD_Reset_Pin	;
	GPIO_Init(LCD_Reset_Port,&GPIO_InitStructure);
	
	
	// Init Data Pin
	GPIO_InitStructure.GPIO_Pin = LCD_Data0_Pin ;
	GPIO_Init(LCD_Data0_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data1_Pin ;
	GPIO_Init(LCD_Data1_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data2_Pin ;
	GPIO_Init(LCD_Data2_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data3_Pin ;
	GPIO_Init(LCD_Data3_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data4_Pin ;
	GPIO_Init(LCD_Data4_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data5_Pin ;
	GPIO_Init(LCD_Data5_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data6_Pin ;
	GPIO_Init(LCD_Data6_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data7_Pin ;
	GPIO_Init(LCD_Data7_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data8_Pin ;
	GPIO_Init(LCD_Data8_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data9_Pin ;
	GPIO_Init(LCD_Data9_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data10_Pin ;
	GPIO_Init(LCD_Data10_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data11_Pin ;
	GPIO_Init(LCD_Data11_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data12_Pin ;
	GPIO_Init(LCD_Data12_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data13_Pin ;
	GPIO_Init(LCD_Data13_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data14_Pin ;
	GPIO_Init(LCD_Data14_Port,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = LCD_Data15_Pin ;
	GPIO_Init(LCD_Data15_Port,&GPIO_InitStructure);
	
	// Init BL
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	LCD_Reset_On;
	Delay_ms(10);
	LCD_Reset_Off;
	
	
	
	LCD_WriteReg(0xF000, 0x55);
	LCD_WriteReg(0xF001, 0xAA);
	LCD_WriteReg(0xF002, 0x52);
	LCD_WriteReg(0xF003, 0x08);
	LCD_WriteReg(0xF004, 0x01);
	//AVDD Set AVDD 5.2V
	LCD_WriteReg(0xB000, 0x0D);
	LCD_WriteReg(0xB001, 0x0D);
	LCD_WriteReg(0xB002, 0x0D);
	//AVDD ratio
	LCD_WriteReg(0xB600, 0x34);
	LCD_WriteReg(0xB601, 0x34);
	LCD_WriteReg(0xB602, 0x34);
	//AVEE -5.2V
	LCD_WriteReg(0xB100, 0x0D);
	LCD_WriteReg(0xB101, 0x0D);
	LCD_WriteReg(0xB102, 0x0D);
	//AVEE ratio
	LCD_WriteReg(0xB700, 0x34);
	LCD_WriteReg(0xB701, 0x34);
	LCD_WriteReg(0xB702, 0x34);
	//VCL -2.5V
	LCD_WriteReg(0xB200, 0x00);
	LCD_WriteReg(0xB201, 0x00);
	LCD_WriteReg(0xB202, 0x00);
	//VCL ratio
	LCD_WriteReg(0xB800, 0x24);
	LCD_WriteReg(0xB801, 0x24);
	LCD_WriteReg(0xB802, 0x24);
	//VGH 15V (Free pump)
	LCD_WriteReg(0xBF00, 0x01);
	LCD_WriteReg(0xB300, 0x0F);
	LCD_WriteReg(0xB301, 0x0F);
	LCD_WriteReg(0xB302, 0x0F);
	//VGH ratio
	LCD_WriteReg(0xB900, 0x34);
	LCD_WriteReg(0xB901, 0x34);
	LCD_WriteReg(0xB902, 0x34);
	//VGL_REG -10V
	LCD_WriteReg(0xB500, 0x08);
	LCD_WriteReg(0xB501, 0x08);
	LCD_WriteReg(0xB502, 0x08);
	LCD_WriteReg(0xC200, 0x03);
	//VGLX ratio
	LCD_WriteReg(0xBA00, 0x24);
	LCD_WriteReg(0xBA01, 0x24);
	LCD_WriteReg(0xBA02, 0x24);
	//VGMP/VGSP 4.5V/0V
	LCD_WriteReg(0xBC00, 0x00);
	LCD_WriteReg(0xBC01, 0x78);
	LCD_WriteReg(0xBC02, 0x00);
	//VGMN/VGSN -4.5V/0V
	LCD_WriteReg(0xBD00, 0x00);
	LCD_WriteReg(0xBD01, 0x78);
	LCD_WriteReg(0xBD02, 0x00);
	//VCOM
	LCD_WriteReg(0xBE00, 0x00);
	LCD_WriteReg(0xBE01, 0x64);
	//Gamma Setting
	LCD_WriteReg(0xD100, 0x00);
	LCD_WriteReg(0xD101, 0x33);
	LCD_WriteReg(0xD102, 0x00);
	LCD_WriteReg(0xD103, 0x34);
	LCD_WriteReg(0xD104, 0x00);
	LCD_WriteReg(0xD105, 0x3A);
	LCD_WriteReg(0xD106, 0x00);
	LCD_WriteReg(0xD107, 0x4A);
	LCD_WriteReg(0xD108, 0x00);
	LCD_WriteReg(0xD109, 0x5C);
	LCD_WriteReg(0xD10A, 0x00);
	LCD_WriteReg(0xD10B, 0x81);
	LCD_WriteReg(0xD10C, 0x00);
	LCD_WriteReg(0xD10D, 0xA6);
	LCD_WriteReg(0xD10E, 0x00);
	LCD_WriteReg(0xD10F, 0xE5);
	LCD_WriteReg(0xD110, 0x01);
	LCD_WriteReg(0xD111, 0x13);
	LCD_WriteReg(0xD112, 0x01);
	LCD_WriteReg(0xD113, 0x54);
	LCD_WriteReg(0xD114, 0x01);
	LCD_WriteReg(0xD115, 0x82);
	LCD_WriteReg(0xD116, 0x01);
	LCD_WriteReg(0xD117, 0xCA);
	LCD_WriteReg(0xD118, 0x02);
	LCD_WriteReg(0xD119, 0x00);
	LCD_WriteReg(0xD11A, 0x02);
	LCD_WriteReg(0xD11B, 0x01);
	LCD_WriteReg(0xD11C, 0x02);
	LCD_WriteReg(0xD11D, 0x34);
	LCD_WriteReg(0xD11E, 0x02);
	LCD_WriteReg(0xD11F, 0x67);
	LCD_WriteReg(0xD120, 0x02);
	LCD_WriteReg(0xD121, 0x84);
	LCD_WriteReg(0xD122, 0x02);
	LCD_WriteReg(0xD123, 0xA4);
	LCD_WriteReg(0xD124, 0x02);
	LCD_WriteReg(0xD125, 0xB7);
	LCD_WriteReg(0xD126, 0x02);
	LCD_WriteReg(0xD127, 0xCF);
	LCD_WriteReg(0xD128, 0x02);
	LCD_WriteReg(0xD129, 0xDE);
 	LCD_WriteReg(0xD12A, 0x02);
	LCD_WriteReg(0xD12B, 0xF2);
	LCD_WriteReg(0xD12C, 0x02);
	LCD_WriteReg(0xD12D, 0xFE);
	LCD_WriteReg(0xD12E, 0x03);
	LCD_WriteReg(0xD12F, 0x10);
	LCD_WriteReg(0xD130, 0x03);
	LCD_WriteReg(0xD131, 0x33);
	LCD_WriteReg(0xD132, 0x03);
	LCD_WriteReg(0xD133, 0x6D);
	LCD_WriteReg(0xD200, 0x00);
	LCD_WriteReg(0xD201, 0x33);
	LCD_WriteReg(0xD202, 0x00);
	LCD_WriteReg(0xD203, 0x34);
	LCD_WriteReg(0xD204, 0x00);
	LCD_WriteReg(0xD205, 0x3A);
	LCD_WriteReg(0xD206, 0x00);
	LCD_WriteReg(0xD207, 0x4A);
	LCD_WriteReg(0xD208, 0x00);
	LCD_WriteReg(0xD209, 0x5C);
	LCD_WriteReg(0xD20A, 0x00);

	LCD_WriteReg(0xD20B, 0x81);
	LCD_WriteReg(0xD20C, 0x00);
	LCD_WriteReg(0xD20D, 0xA6);
	LCD_WriteReg(0xD20E, 0x00);
	LCD_WriteReg(0xD20F, 0xE5);
	LCD_WriteReg(0xD210, 0x01);
	LCD_WriteReg(0xD211, 0x13);
	LCD_WriteReg(0xD212, 0x01);
	LCD_WriteReg(0xD213, 0x54);
	LCD_WriteReg(0xD214, 0x01);
	LCD_WriteReg(0xD215, 0x82);
	LCD_WriteReg(0xD216, 0x01);
	LCD_WriteReg(0xD217, 0xCA);
	LCD_WriteReg(0xD218, 0x02);
	LCD_WriteReg(0xD219, 0x00);
	LCD_WriteReg(0xD21A, 0x02);
	LCD_WriteReg(0xD21B, 0x01);
	LCD_WriteReg(0xD21C, 0x02);
	LCD_WriteReg(0xD21D, 0x34);
	LCD_WriteReg(0xD21E, 0x02);
	LCD_WriteReg(0xD21F, 0x67);
	LCD_WriteReg(0xD220, 0x02);
	LCD_WriteReg(0xD221, 0x84);
	LCD_WriteReg(0xD222, 0x02);
	LCD_WriteReg(0xD223, 0xA4);
	LCD_WriteReg(0xD224, 0x02);
	LCD_WriteReg(0xD225, 0xB7);
	LCD_WriteReg(0xD226, 0x02);
	LCD_WriteReg(0xD227, 0xCF);
	LCD_WriteReg(0xD228, 0x02);
	LCD_WriteReg(0xD229, 0xDE);
	LCD_WriteReg(0xD22A, 0x02);
	LCD_WriteReg(0xD22B, 0xF2);
	LCD_WriteReg(0xD22C, 0x02);
	LCD_WriteReg(0xD22D, 0xFE);
	LCD_WriteReg(0xD22E, 0x03);
	LCD_WriteReg(0xD22F, 0x10);
	LCD_WriteReg(0xD230, 0x03);
	LCD_WriteReg(0xD231, 0x33);
	LCD_WriteReg(0xD232, 0x03);
	LCD_WriteReg(0xD233, 0x6D);
	LCD_WriteReg(0xD300, 0x00);
	LCD_WriteReg(0xD301, 0x33);
	LCD_WriteReg(0xD302, 0x00);
	LCD_WriteReg(0xD303, 0x34);
	LCD_WriteReg(0xD304, 0x00);
	LCD_WriteReg(0xD305, 0x3A);
	LCD_WriteReg(0xD306, 0x00);
	LCD_WriteReg(0xD307, 0x4A);
	LCD_WriteReg(0xD308, 0x00);
	LCD_WriteReg(0xD309, 0x5C);
	LCD_WriteReg(0xD30A, 0x00);

	LCD_WriteReg(0xD30B, 0x81);
	LCD_WriteReg(0xD30C, 0x00);
	LCD_WriteReg(0xD30D, 0xA6);
	LCD_WriteReg(0xD30E, 0x00);
	LCD_WriteReg(0xD30F, 0xE5);
	LCD_WriteReg(0xD310, 0x01);
	LCD_WriteReg(0xD311, 0x13);
	LCD_WriteReg(0xD312, 0x01);
	LCD_WriteReg(0xD313, 0x54);
	LCD_WriteReg(0xD314, 0x01);
	LCD_WriteReg(0xD315, 0x82);
	LCD_WriteReg(0xD316, 0x01);
	LCD_WriteReg(0xD317, 0xCA);
	LCD_WriteReg(0xD318, 0x02);
	LCD_WriteReg(0xD319, 0x00);
	LCD_WriteReg(0xD31A, 0x02);
	LCD_WriteReg(0xD31B, 0x01);
	LCD_WriteReg(0xD31C, 0x02);
	LCD_WriteReg(0xD31D, 0x34);
	LCD_WriteReg(0xD31E, 0x02);
	LCD_WriteReg(0xD31F, 0x67);
	LCD_WriteReg(0xD320, 0x02);
	LCD_WriteReg(0xD321, 0x84);
	LCD_WriteReg(0xD322, 0x02);
	LCD_WriteReg(0xD323, 0xA4);
	LCD_WriteReg(0xD324, 0x02);
	LCD_WriteReg(0xD325, 0xB7);
	LCD_WriteReg(0xD326, 0x02);
	LCD_WriteReg(0xD327, 0xCF);
	LCD_WriteReg(0xD328, 0x02);
	LCD_WriteReg(0xD329, 0xDE);
	LCD_WriteReg(0xD32A, 0x02);
	LCD_WriteReg(0xD32B, 0xF2);
	LCD_WriteReg(0xD32C, 0x02);
	LCD_WriteReg(0xD32D, 0xFE);
	LCD_WriteReg(0xD32E, 0x03);
	LCD_WriteReg(0xD32F, 0x10);
	LCD_WriteReg(0xD330, 0x03);
	LCD_WriteReg(0xD331, 0x33);
	LCD_WriteReg(0xD332, 0x03);
	LCD_WriteReg(0xD333, 0x6D);
	LCD_WriteReg(0xD400, 0x00);
	LCD_WriteReg(0xD401, 0x33);
	LCD_WriteReg(0xD402, 0x00);
	LCD_WriteReg(0xD403, 0x34);
	LCD_WriteReg(0xD404, 0x00);
	LCD_WriteReg(0xD405, 0x3A);
	LCD_WriteReg(0xD406, 0x00);
	LCD_WriteReg(0xD407, 0x4A);
	LCD_WriteReg(0xD408, 0x00);
	LCD_WriteReg(0xD409, 0x5C);
	LCD_WriteReg(0xD40A, 0x00);
	LCD_WriteReg(0xD40B, 0x81);

	LCD_WriteReg(0xD40C, 0x00);
	LCD_WriteReg(0xD40D, 0xA6);
	LCD_WriteReg(0xD40E, 0x00);
	LCD_WriteReg(0xD40F, 0xE5);
	LCD_WriteReg(0xD410, 0x01);
	LCD_WriteReg(0xD411, 0x13);
	LCD_WriteReg(0xD412, 0x01);
	LCD_WriteReg(0xD413, 0x54);
	LCD_WriteReg(0xD414, 0x01);
	LCD_WriteReg(0xD415, 0x82);
	LCD_WriteReg(0xD416, 0x01);
	LCD_WriteReg(0xD417, 0xCA);
	LCD_WriteReg(0xD418, 0x02);
	LCD_WriteReg(0xD419, 0x00);
	LCD_WriteReg(0xD41A, 0x02);
	LCD_WriteReg(0xD41B, 0x01);
	LCD_WriteReg(0xD41C, 0x02);
	LCD_WriteReg(0xD41D, 0x34);
	LCD_WriteReg(0xD41E, 0x02);
	LCD_WriteReg(0xD41F, 0x67);
	LCD_WriteReg(0xD420, 0x02);
	LCD_WriteReg(0xD421, 0x84);
	LCD_WriteReg(0xD422, 0x02);
	LCD_WriteReg(0xD423, 0xA4);
	LCD_WriteReg(0xD424, 0x02);
	LCD_WriteReg(0xD425, 0xB7);
	LCD_WriteReg(0xD426, 0x02);
	LCD_WriteReg(0xD427, 0xCF);
	LCD_WriteReg(0xD428, 0x02);
	LCD_WriteReg(0xD429, 0xDE);
	LCD_WriteReg(0xD42A, 0x02);
	LCD_WriteReg(0xD42B, 0xF2);
	LCD_WriteReg(0xD42C, 0x02);
	LCD_WriteReg(0xD42D, 0xFE);
	LCD_WriteReg(0xD42E, 0x03);
	LCD_WriteReg(0xD42F, 0x10);
	LCD_WriteReg(0xD430, 0x03);
	LCD_WriteReg(0xD431, 0x33);
	LCD_WriteReg(0xD432, 0x03);
	LCD_WriteReg(0xD433, 0x6D);
	LCD_WriteReg(0xD500, 0x00);
	LCD_WriteReg(0xD501, 0x33);
	LCD_WriteReg(0xD502, 0x00);
	LCD_WriteReg(0xD503, 0x34);
	LCD_WriteReg(0xD504, 0x00);
	LCD_WriteReg(0xD505, 0x3A);
	LCD_WriteReg(0xD506, 0x00);
	LCD_WriteReg(0xD507, 0x4A);
	LCD_WriteReg(0xD508, 0x00);
	LCD_WriteReg(0xD509, 0x5C);
	LCD_WriteReg(0xD50A, 0x00);
	LCD_WriteReg(0xD50B, 0x81);

	LCD_WriteReg(0xD50C, 0x00);
	LCD_WriteReg(0xD50D, 0xA6);
	LCD_WriteReg(0xD50E, 0x00);
	LCD_WriteReg(0xD50F, 0xE5);
	LCD_WriteReg(0xD510, 0x01);
	LCD_WriteReg(0xD511, 0x13);
	LCD_WriteReg(0xD512, 0x01);
	LCD_WriteReg(0xD513, 0x54);
	LCD_WriteReg(0xD514, 0x01);
	LCD_WriteReg(0xD515, 0x82);
	LCD_WriteReg(0xD516, 0x01);
	LCD_WriteReg(0xD517, 0xCA);
	LCD_WriteReg(0xD518, 0x02);
	LCD_WriteReg(0xD519, 0x00);
	LCD_WriteReg(0xD51A, 0x02);
	LCD_WriteReg(0xD51B, 0x01);
	LCD_WriteReg(0xD51C, 0x02);
	LCD_WriteReg(0xD51D, 0x34);
	LCD_WriteReg(0xD51E, 0x02);
	LCD_WriteReg(0xD51F, 0x67);
	LCD_WriteReg(0xD520, 0x02);
	LCD_WriteReg(0xD521, 0x84);
	LCD_WriteReg(0xD522, 0x02);
	LCD_WriteReg(0xD523, 0xA4);
	LCD_WriteReg(0xD524, 0x02);
	LCD_WriteReg(0xD525, 0xB7);
	LCD_WriteReg(0xD526, 0x02);
	LCD_WriteReg(0xD527, 0xCF);
	LCD_WriteReg(0xD528, 0x02);
	LCD_WriteReg(0xD529, 0xDE);
	LCD_WriteReg(0xD52A, 0x02);
	LCD_WriteReg(0xD52B, 0xF2);
	LCD_WriteReg(0xD52C, 0x02);
	LCD_WriteReg(0xD52D, 0xFE);
	LCD_WriteReg(0xD52E, 0x03);
	LCD_WriteReg(0xD52F, 0x10);
	LCD_WriteReg(0xD530, 0x03);
	LCD_WriteReg(0xD531, 0x33);
	LCD_WriteReg(0xD532, 0x03);
	LCD_WriteReg(0xD533, 0x6D);
	LCD_WriteReg(0xD600, 0x00);
	LCD_WriteReg(0xD601, 0x33);
	LCD_WriteReg(0xD602, 0x00);
	LCD_WriteReg(0xD603, 0x34);
	LCD_WriteReg(0xD604, 0x00);
	LCD_WriteReg(0xD605, 0x3A);
	LCD_WriteReg(0xD606, 0x00);
	LCD_WriteReg(0xD607, 0x4A);
	LCD_WriteReg(0xD608, 0x00);
	LCD_WriteReg(0xD609, 0x5C);
	LCD_WriteReg(0xD60A, 0x00);
	LCD_WriteReg(0xD60B, 0x81);

	LCD_WriteReg(0xD60C, 0x00);
	LCD_WriteReg(0xD60D, 0xA6);
	LCD_WriteReg(0xD60E, 0x00);
	LCD_WriteReg(0xD60F, 0xE5);
	LCD_WriteReg(0xD610, 0x01);
	LCD_WriteReg(0xD611, 0x13);
	LCD_WriteReg(0xD612, 0x01);
	LCD_WriteReg(0xD613, 0x54);
	LCD_WriteReg(0xD614, 0x01);
	LCD_WriteReg(0xD615, 0x82);
	LCD_WriteReg(0xD616, 0x01);
	LCD_WriteReg(0xD617, 0xCA);
	LCD_WriteReg(0xD618, 0x02);
	LCD_WriteReg(0xD619, 0x00);
	LCD_WriteReg(0xD61A, 0x02);
	LCD_WriteReg(0xD61B, 0x01);
	LCD_WriteReg(0xD61C, 0x02);
	LCD_WriteReg(0xD61D, 0x34);
	LCD_WriteReg(0xD61E, 0x02);
	LCD_WriteReg(0xD61F, 0x67);
	LCD_WriteReg(0xD620, 0x02);
	LCD_WriteReg(0xD621, 0x84);
	LCD_WriteReg(0xD622, 0x02);
	LCD_WriteReg(0xD623, 0xA4);
	LCD_WriteReg(0xD624, 0x02);
	LCD_WriteReg(0xD625, 0xB7);
	LCD_WriteReg(0xD626, 0x02);
	LCD_WriteReg(0xD627, 0xCF);
	LCD_WriteReg(0xD628, 0x02);
	LCD_WriteReg(0xD629, 0xDE);
	LCD_WriteReg(0xD62A, 0x02);
	LCD_WriteReg(0xD62B, 0xF2);
	LCD_WriteReg(0xD62C, 0x02);
	LCD_WriteReg(0xD62D, 0xFE);
	LCD_WriteReg(0xD62E, 0x03);
	LCD_WriteReg(0xD62F, 0x10);
	LCD_WriteReg(0xD630, 0x03);
	LCD_WriteReg(0xD631, 0x33);
	LCD_WriteReg(0xD632, 0x03);
	LCD_WriteReg(0xD633, 0x6D);
	//LV2 Page 0 enable
	LCD_WriteReg(0xF000, 0x55);
	LCD_WriteReg(0xF001, 0xAA);
	LCD_WriteReg(0xF002, 0x52);
	LCD_WriteReg(0xF003, 0x08);
	LCD_WriteReg(0xF004, 0x00);
	//Display control
	LCD_WriteReg(0xB100, 0xCC);
	LCD_WriteReg(0xB101, 0x00);
	//Source hold time
	LCD_WriteReg(0xB600, 0x05);
	//Gate EQ control
	LCD_WriteReg(0xB700, 0x70);
	LCD_WriteReg(0xB701, 0x70);
	//Source EQ control (Mode 2)
	LCD_WriteReg(0xB800, 0x01);
	LCD_WriteReg(0xB801, 0x03);
	LCD_WriteReg(0xB802, 0x03);
	LCD_WriteReg(0xB803, 0x03);
	//Inversion mode (2-dot)
	LCD_WriteReg(0xBC00, 0x02);
	LCD_WriteReg(0xBC01, 0x00);
	LCD_WriteReg(0xBC02, 0x00);
	//Timing control 4H w/ 4-delay
	LCD_WriteReg(0xC900, 0xD0);
	LCD_WriteReg(0xC901, 0x02);
	LCD_WriteReg(0xC902, 0x50);
	LCD_WriteReg(0xC903, 0x50);
	LCD_WriteReg(0xC904, 0x50);
	LCD_WriteReg(0x3500, 0x00);
	LCD_WriteReg(0x3A00, 0x55); //16-bit/pixel
	//LCD_WR_REG(0x1100);
	LCD_Write_Command(0x1100);
	Delay_110ns(120);
	//LCD_WR_REG(0x2900);
	LCD_Write_Command(0x2900);
	
	
}



// there are 16 data pin to be transmited 
inline void Parallel_Write(u16 data) 
{
		
		// bit0
		if ((data>>0 & 0x0001)) GPIO_SetBits(LCD_Data0_Port,LCD_Data0_Pin);    
		else GPIO_ResetBits(LCD_Data0_Port,LCD_Data0_Pin);
		// bit1
		if ((data>>1 & 0x0001)) GPIO_SetBits(LCD_Data1_Port,LCD_Data1_Pin); 
		else GPIO_ResetBits(LCD_Data1_Port,LCD_Data1_Pin);
		// bit2
		if ((data>>2 & 0x0001)) GPIO_SetBits(LCD_Data2_Port,LCD_Data2_Pin);
		else GPIO_ResetBits(LCD_Data2_Port,LCD_Data2_Pin);
    // bit3	
		if ((data>>3 & 0x0001)) GPIO_SetBits(LCD_Data3_Port,LCD_Data3_Pin);
		else GPIO_ResetBits(LCD_Data3_Port,LCD_Data3_Pin);
		// bit4	
		if ((data>>4 & 0x0001)) GPIO_SetBits(LCD_Data4_Port,LCD_Data4_Pin); 
		else GPIO_ResetBits(LCD_Data4_Port,LCD_Data4_Pin);
		// bit5	
		if ((data>>5 & 0x0001)) GPIO_SetBits(LCD_Data5_Port,LCD_Data5_Pin); 
		else GPIO_ResetBits(LCD_Data5_Port,LCD_Data5_Pin);
		// bit6	
		if ((data>>6 & 0x0001)) GPIO_SetBits(LCD_Data6_Port,LCD_Data6_Pin); 
		else GPIO_ResetBits(LCD_Data6_Port,LCD_Data6_Pin);
		// bit7	
		if ((data>>7 & 0x0001)) GPIO_SetBits(LCD_Data7_Port,LCD_Data7_Pin); 
		else GPIO_ResetBits(LCD_Data7_Port,LCD_Data7_Pin);
		// bit8	
		if ((data>>8 & 0x0001)) GPIO_SetBits(LCD_Data8_Port,LCD_Data8_Pin); 
		else GPIO_ResetBits(LCD_Data8_Port,LCD_Data8_Pin);
		// bit9	
		if ((data>>9 & 0x0001)) GPIO_SetBits(LCD_Data9_Port,LCD_Data9_Pin); 
		else GPIO_ResetBits(LCD_Data9_Port,LCD_Data9_Pin);
		// bit10	
		if ((data>>10 & 0x0001)) GPIO_SetBits(LCD_Data10_Port,LCD_Data10_Pin); 
		else GPIO_ResetBits(LCD_Data10_Port,LCD_Data10_Pin);
		// bit11	
		if ((data>>11 & 0x0001)) GPIO_SetBits(LCD_Data11_Port,LCD_Data11_Pin); 
		else GPIO_ResetBits(LCD_Data11_Port,LCD_Data11_Pin);
		// bit12	
		if ((data>>12 & 0x0001)) GPIO_SetBits(LCD_Data12_Port,LCD_Data12_Pin); 
		else GPIO_ResetBits(LCD_Data12_Port,LCD_Data12_Pin);
		// bit13	
		if ((data>>13 & 0x0001)) GPIO_SetBits(LCD_Data13_Port,LCD_Data13_Pin); 
		else GPIO_ResetBits(LCD_Data13_Port,LCD_Data13_Pin);
		// bit14	
		if ((data>>14 & 0x0001)) GPIO_SetBits(LCD_Data14_Port,LCD_Data14_Pin); 
		else GPIO_ResetBits(LCD_Data14_Port,LCD_Data14_Pin);
		// bit15	
		if ((data>>15 & 0x0001)) GPIO_SetBits(LCD_Data15_Port,LCD_Data15_Pin); 
		else GPIO_ResetBits(LCD_Data15_Port,LCD_Data15_Pin);
}




void LCD_Write_Command(u16 input)
{
	
	LCD_RS_Command;
	LCD_CS_Enable;
	LCD_Read_Disable;
	LCD_Write_Enable;	
	Parallel_Write(input);
	LCD_Write_Disable;	
	LCD_CS_Disable;
}


void LCD_Write_Data(u16 input)
{
	LCD_RS_Data;
	LCD_CS_Enable;
	LCD_Read_Disable;	
	LCD_Write_Enable;
	Parallel_Write(input);
	LCD_Write_Disable;
	LCD_CS_Disable;
}

void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{
	LCD_Write_Command(LCD_Reg);
	LCD_Write_Data(LCD_RegValue);

}


void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_Write_Command(LCD_SetXCmd);
	LCD_Write_Data(Xpos >> 8);
	LCD_Write_Command(LCD_SetXCmd + 1);
	LCD_Write_Data(Xpos & 0XFF);
	LCD_Write_Command(LCD_SetYCmd);
	LCD_Write_Data(Ypos >> 8);
	LCD_Write_Command(LCD_SetYCmd + 1);
	LCD_Write_Data(Ypos & 0XFF);
}



void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
{
    u16 i, j;
    u16 xlen = 0;

    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++)
    {
        LCD_SetCursor(sx, i);       
        //LCD_WriteRAM_Prepare();     
				LCD_Write_Command(LCD_WriteGramCmd);
			
        for (j = 0; j < xlen; j++)
        {
            //LCD->LCD_RAM=color;     
						LCD_Write_Data(color);
				}
    }
}


void LCD_Clear(u16 color)
{
    u32 index = 0;
    u32 totalpoint = LCD_Width;
    totalpoint *= LCD_Height;    // get number full point

    LCD_SetCursor(0x00, 0x0000);    
    LCD_Write_Command(LCD_WriteGramCmd);      

    for (index = 0; index < totalpoint; index++)
    {
        LCD_Write_Data(color);
    }

}

