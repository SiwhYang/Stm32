#ifndef __LCD_H__
#define __LCD_H__
#include "stm32f30x.h"
#include "delay.h"

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


// LCD Data Pin
#define LCD_Data0_Port  GPIOC
#define LCD_Data0_Pin   GPIO_Pin_14
#define LCD_Data1_Port  GPIOC
#define LCD_Data1_Pin   GPIO_Pin_13
#define LCD_Data2_Port  GPIOE
#define LCD_Data2_Pin   GPIO_Pin_6
//#define LCD_Data3_Port  GPIOE
//#define LCD_Data3_Pin   GPIO_Pin_4
#define LCD_Data3_Port  GPIOA
#define LCD_Data3_Pin   GPIO_Pin_3
//#define LCD_Data4_Port  GPIOE
//#define LCD_Data4_Pin   GPIO_Pin_5
#define LCD_Data4_Port  GPIOC
#define LCD_Data4_Pin   GPIO_Pin_3
#define LCD_Data5_Port  GPIOE
#define LCD_Data5_Pin   GPIO_Pin_14
#define LCD_Data6_Port  GPIOE
#define LCD_Data6_Pin   GPIO_Pin_15
#define LCD_Data7_Port  GPIOB
#define LCD_Data7_Pin   GPIO_Pin_10
#define LCD_Data8_Port  GPIOB
#define LCD_Data8_Pin   GPIO_Pin_11
#define LCD_Data9_Port  GPIOB
#define LCD_Data9_Pin   GPIO_Pin_12
#define LCD_Data10_Port GPIOB
#define LCD_Data10_Pin  GPIO_Pin_13
#define LCD_Data11_Port GPIOB
#define LCD_Data11_Pin  GPIO_Pin_15
#define LCD_Data12_Port GPIOB
#define LCD_Data12_Pin  GPIO_Pin_14
#define LCD_Data13_Port GPIOD
#define LCD_Data13_Pin  GPIO_Pin_8
//#define LCD_Data14_Port GPIOD
//#define LCD_Data14_Pin  GPIO_Pin_9
#define LCD_Data14_Port GPIOA
#define LCD_Data14_Pin  GPIO_Pin_1
#define LCD_Data15_Port GPIOC
#define LCD_Data15_Pin  GPIO_Pin_1

// LCD BackLight port
#define LCD_BackLight_Port GPIOC
#define LCD_BackLight_Pin GPIO_Pin_9


// LCD Chip select
#define LCD_CS_Port GPIOF
#define LCD_CS_Pin  GPIO_Pin_10
// LCD Command or Data port
#define LCD_RS_Port GPIOF
#define LCD_RS_Pin  GPIO_Pin_9
// LCD Read port
#define LCD_Read_Port GPIOB
#define LCD_Read_Pin  GPIO_Pin_7
// LCD Write port
#define LCD_Write_Port GPIOB
#define LCD_Write_Pin  GPIO_Pin_9
// LCD Rest
#define LCD_Reset_Port GPIOC
#define LCD_Reset_Pin  GPIO_Pin_15


// Define some useful switch function
#define LCD_BackLight_Enable  GPIO_SetBits(LCD_BackLight_Port,LCD_BackLight_Pin)
#define LCD_BackLight_Disable GPIO_ResetBits(LCD_BackLight_Port,LCD_BackLight_Pin)
#define LCD_CS_Enable  GPIO_ResetBits(LCD_CS_Port,LCD_CS_Pin)
#define LCD_CS_Disable GPIO_SetBits(LCD_CS_Port,LCD_CS_Pin)
#define LCD_RS_Data    GPIO_SetBits(LCD_RS_Port,LCD_RS_Pin)
#define LCD_RS_Command GPIO_ResetBits(LCD_RS_Port,LCD_RS_Pin)
#define LCD_Write_Enable  GPIO_ResetBits(LCD_Write_Port,LCD_Write_Pin)
#define LCD_Write_Disable GPIO_SetBits(LCD_Write_Port,LCD_Write_Pin)
#define LCD_Read_Enable   GPIO_ResetBits(LCD_Read_Port,LCD_Read_Pin)
#define LCD_Read_Disable  GPIO_SetBits(LCD_Read_Port,LCD_Read_Pin)

#define LCD_Reset_On GPIO_SetBits(LCD_Reset_Port,LCD_Reset_Pin)
#define LCD_Reset_Off GPIO_SetBits(LCD_Reset_Port,LCD_Reset_Pin)

// Define some useful command 
#define LCD_Read_ID_Cmd   
#define LCD_WriteGramCmd 0x2C00
#define LCD_SetXCmd 0x2A00
#define LCD_SetYCmd 0x2B00
#define LCD_Width 480
#define LCD_Height 800
#define WHITE           0xFFFF
#define BLACK           0x0000
#define BLUE            0x001F
#define BRED            0XF81F
#define GRED            0XFFE0
#define GBLUE           0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN           0x07E0
#define CYAN            0x7FFF
#define YELLOW          0xFFE0
#define BROWN           0XBC40  
#define BRRED           0XFC07  
#define GRAY            0X8430  


void LCD_Init();
void Parallel_Write (u16 data);
void LCD_Write_Command(u16 input);
void LCD_Write_Data(u16 input);
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_FillColor(u16 color);

void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color);
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue);
//u16 Parallel_UsartPrintf (u16 data) ;
void LCD_Clear(u16 color);


#endif
