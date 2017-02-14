#include "LPC43xx.h"                    /* LPC43xx Definitions                */
//#include <lpc17xx.h>

int Data = 0;
void InitSSP (void)
{
//------------------------------------------------------------------------------------------------------------------	
// Init SSP0  ________ ADC0 & DDS  _______________________________________________
//  PD_14-> GPIO6[28]-> Func4
	LPC_SCU->SFSPD_14 = 4 | (1<<5) ;  // Func4, EPUN = 0 -> enable pull up, EHS =1 (Fast Speed) GPIO6[28]
	LPC_GPIO_PORT->DIR[6] |= (1<<28) ;  // LPC_GPIO3->FIODIR |= 1 << 25;   							// START_CONV_ADC
	LPC_GPIO_PORT->CLR[6]  = (1<<28) ;  // LPC_GPIO3->FIOCLR  = 1 << 25;   							// START_CONV_ADC


//  PF_9-> GPIO7[23]-> Func4
	LPC_SCU->SFSPF_9 = 4 | (1<<5) ;  // Func4, EPUN = 0 -> enable pull up, EHS =1 (Fast Speed) GPIO7[23]
	LPC_GPIO_PORT->DIR[7] |= (1<<23) ;  // ~EN_ADC0 P7.23
	LPC_GPIO_PORT->SET[7] |= (1<<23) ;  // ~EN_ADC0 P7.23->1
	
//  PF_0-> SSP0_SCK -> Func0
//  PF_2-> SSP0_MISO-> Func2
//  PF_3-> SSP0_MOSI-> Func2
	LPC_SCU->SFSPF_0 = 0 | (1<<5)          ;  // Func0, EHS =1 (Fast Speed) SSP0_SCK
	LPC_SCU->SFSPF_2 = 2 | (1<<5) | (1<<6) ;  // Func2, EHS =1 (Fast Speed) SSP0_MISO, EZI = 1 input buffer enable
	LPC_SCU->SFSPF_3 = 2 | (1<<5)          ;  // Func3, EHS =1 (Fast Speed) SSP0_MOSI

	LPC_CGU->BASE_SSP0_CLK = (0x09 << 24) ; // CLK_SEL = PLL1
	
	LPC_SSP0->CR0   = 0x07;    // 8 bit
//	LPC_SSP0->CR0  |= 0x0F;    // 16 bit
//	LPC_SSP0->CR0  |= 0 << 4;  // SPI frame format
//	LPC_SSP0->CR0  |= 1 << 6;  // CPOL = 1
//	LPC_SSP0->CR0  |= 1 << 7;  // CPHA = 1
	LPC_SSP0->CR0  |= 1 << 8;  // SCR = 2
//	LPC_SSP0->CR0  |= 10 << 8;  // SCR = 2

	LPC_SSP0->CR1  = 0x00   ;  // During normal operation, The SSP controller is disabled,  Master
//	LPC_SSP0->CR1  |= 0 << 0;  // During normal operation
//	LPC_SSP0->CR1  |= 0 << 2;  // Master

//	LPC_SSP0->CPSR  = 5;  //40
	LPC_SSP0->CPSR  = 10;  //40
	LPC_SSP0->CR1  |= 0x02;  // The SSP controller is enabled
//__________________________________________________________________________________


//_____init SSP1 ____ DAC0 & ADC1____________________________________________________
//  PF_5-> GPIO7[19]-> Func4
	LPC_SCU->SFSPF_5 = 4 | (1<<5)    ;  // Func4, EPUN = 0 -> enable pull up, EHS =1 (Fast Speed) GPIO7[19]
	LPC_GPIO_PORT->DIR[7] |= (1<<19) ;  // ~EN_ADC1 P7.19
	LPC_GPIO_PORT->SET[7] |= (1<<19) ;  // ~EN_ADC1 P7.19->1
//  PF_10-> GPIO7[24]-> Func4
	LPC_SCU->SFSPF_10 = 4 | (1<<5)   ;  // Func4, EPUN = 0 -> enable pull up, EHS =1 (Fast Speed) GPIO7[24]
	LPC_GPIO_PORT->DIR[7] |= (1<<24) ;  // ~EN_DAC0 P7.24
	LPC_GPIO_PORT->SET[7] |= (1<<24) ;  // ~EN_DAC0 P7.24->1
//  PD_13-> GPIO6[27]-> Func4
	LPC_SCU->SFSPD_13 = 4 | (1<<5)   ;  // Func4, EPUN = 0 -> enable pull up, EHS =1 (Fast Speed) GPIO6[27]
	LPC_GPIO_PORT->DIR[6] |= (1<<27) ;  // ~LOAD_DAC0 P6.27
	LPC_GPIO_PORT->SET[6] |= (1<<27) ;  // ~LOAD_DAC0 P6.27->1
// init for DAC  8 bit
//  PF_4-> SSP1_SCK -> Func0
//  PF_6-> SSP1_MISO-> Func2
//  PF_7-> SSP1_MOSI-> Func2
	LPC_SCU->SFSPF_4 = 0 | (1<<5)          ;  // Func0, EHS =1 (Fast Speed) SSP1_SCK
	LPC_SCU->SFSPF_6 = 2 | (1<<5) | (1<<6) ;  // Func2, EHS =1 (Fast Speed) SSP1_MISO, EZI = 1 input buffer enable
	LPC_SCU->SFSPF_7 = 2 | (1<<5)          ;  // Func3, EHS =1 (Fast Speed) SSP1_MOSI

	LPC_CGU->BASE_SSP1_CLK = (0x09 << 24) ; // CLK_SEL = PLL1

	LPC_SSP1->CR0   = 0x07;    // 8 bit
//	LPC_SSP1->CR0   = 0x0F;    // 16 bit
//	LPC_SSP1->CR0  |= 0 << 4;  // SPI frame format
//	LPC_SSP1->CR0  |= 1 << 6;  // CPOL = 1  //LPC_SPI->SPCR |= (1 << 4);		// SCK is active high
//	LPC_SSP1->CR0  |= 1 << 7;  // CPHA = 1 	//LPC_SPI->SPCR |= (1 << 3);		// CPHA mode

	LPC_SSP1->CR0  |= 1 << 8;  // SCR = 2

	LPC_SSP1->CR1  = 0x00   ;  // During normal operation, The SSP controller is disabled,  Master, Loop back mode
//	LPC_SSP1->CR1  = 0x01   ;  // During normal operation, The SSP controller is disabled,  Master, Loop back mode
//	LPC_SSP1->CR1  |= 0 << 0;  // During normal operation
//	LPC_SSP1->CR1  |= 0 << 2;  // Master

	LPC_SSP1->CPSR  = 10;  //40
	LPC_SSP1->CR1  |= 1 << 1;  // The SSP controller is enabled
//_________________________________________________________________________________

//------------------------------------------------------------------------------------------------------------------	
/*
// init for ADC
	LPC_SSP0->CR0 = 0x00;      // SPI frame format, CPOL=0
	LPC_SSP0->CR0  |= 0x07;    // 8 bit
//	LPC_SSP0->CR0  |= 0x0F;    // 16 bit
//	LPC_SSP0->CR0  |= 0 << 4;  // SPI frame format
//	LPC_SSP0->CR0  |= 1 << 6;  // CPOL = 1
	LPC_SSP0->CR0  |= 1 << 7;  // CPHA = 1
	LPC_SSP0->CR0  |= 0 << 8;  // SCR = 2

	LPC_SSP0->CR1  = 0x00   ;  // During normal operation, The SSP controller is disabled,  Master
//	LPC_SSP0->CR1  |= 0 << 0;  // During normal operation
//	LPC_SSP0->CR1  |= 0 << 1;  // The SSP controller is disabled
//	LPC_SSP0->CR1  |= 0 << 2;  // Master

	LPC_SSP0->CPSR  = 5;  //40
	LPC_SSP0->CR1  |= 1 << 1;  // The SSP controller is enabled
*/
}
//int OutputSSP_prog(void)
//{
//	int i0, i1, Dt, temp = 0x3FF;

//	LPC_GPIO_PORT->SET[6] = (1<<28) ;  // LPC_GPIO3->FIOSET = 1 << 25;   							// START_CONV_ADC
//	//for (i0 = 0; i0 < 10; i0++);
//	LPC_GPIO_PORT->CLR[6] = (1<<28) ;  // LPC_GPIO3->FIOCLR = 1 << 25;   							// START_CONV_ADC
//	//for (i0 = 0; i0 < 5000; i0++);	
//	while ((LPC_GPIO_PORT->CLR[6] & (1 << 28)) != 0);
//	Data = 0;

////g	LPC_GPIO1->FIOSET = 1 << 20;
//	//for (i1 = 0; i1 < 100; i1++);
////g	LPC_GPIO1->FIOCLR = 1 << 20; 

//	i0 = 17;
//	while(i0 >= 0)
//	{
////g		LPC_GPIO1->FIOSET = 1 << 20;
//		for (i1 = 0; i1 < 10; i1++);

//		//Data |= ((((temp << 6+(17-i0)) & (1 << 23)) >> 23) & 0x1) << i0;
////g		Data |= (((LPC_GPIO1->FIOPIN & (1 << 23)) >> 23) & 0x1) << i0;
//		
////g		LPC_GPIO1->FIOCLR = 1 << 20;
//		for (i1 = 0; i1 < 10; i1++);

//		i0--;
//	}

//	i0 = 40;
//	while(i0 >= 0)
//	{
////g		LPC_GPIO1->FIOSET = 1 << 20;
//		for (i1 = 0; i1 < 100; i1++);

//		//Data |= (((LPC_GPIO1->FIOPIN & (1 << 23)) >> 23) & 0x1) << i0;
//		
////g		LPC_GPIO1->FIOCLR = 1 << 20;
//		for (i1 = 0; i1 < 10; i1++);
//		i0--;
//	}
//	
//	return Data;
//}