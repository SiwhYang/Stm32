#ifndef __I3G4250D_H__
#define __I3G4250D_H__




// CS->PC1, PF7->SCK, PF8->MISO, PF9->MOSI

#define I3G4250D_CS_Port   GPIOC
#define I3G4250D_CS_Pin    GPIO_Pin_1
#define I3G4250D_SCK_Port  GPIOF
#define I3G4250D_SCK_Pin   GPIO_Pin_7
#define I3G4250D_MISO_Port GPIOF
#define I3G4250D_MISO_Pin  GPIO_Pin_8
#define I3G4250D_MOSI_Port GPIOF
#define I3G4250D_MOSI_Pin  GPIO_Pin_9

#define Dummy_Byte 0xFFFF


void I3G4250D_init();



#endif

