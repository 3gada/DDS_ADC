#include "LPC43xx.h"                    /* LPC43xx Definitions                */
#include "MainData.h"

//___________________________________________________________________________________________________________________________________

void write_reg_DA7_64 (unsigned char num_reg, unsigned long long data_for_reg)
{
unsigned char in7;
	//	LPC_GPIO1->FIOCLR = (1<<21) ; // cs = 0, da7

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = num_reg & ~(0x80) ; 					// Write data to REG0 - CFR1
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 56) & 0x0ff ; 					// bit 63:56
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 48) & 0x0ff ; 					// bit 55:48 
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 40) & 0x0ff ; 					// bit 47:40
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 32) & 0x0ff ;  					// bit 39:32
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 24) & 0x0ff ; 					// bit 31:24
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 16) & 0x0ff ; 					// bit 23:16 
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg >> 8) & 0x0ff ; 					// bit 15:08
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = (data_for_reg) & 0x0ff ;  					    // bit 07:00
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

//	LPC_GPIO1->FIOSET = (1<<8) ; //set P1.8 update_0
//
//	in5=0;
//	in6=1;
//
//	LPC_GPIO1->FIOCLR = (1<<8) ; //clr P1.8 update_0
//
//	in5=0;
//	in6=1;
//
//	LPC_GPIO1->FIOSET = (1<<21) ; // cs = 1, da7

}


void write_reg_DA7_16 (unsigned char num_reg, unsigned int data_for_reg)
{
}

void read_reg_DA7_32 (unsigned char num_reg, unsigned int data_from_reg)
{
unsigned char in1;
unsigned char in2;
unsigned char in4;
unsigned char in8;
unsigned char in3;
	LPC_GPIO_PORT->CLR[7]  = (1<<25) ;  // cs = 0 da7

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x81 ; // read data from REG0 - CFR1
	LPC_SSP0->DR = num_reg | 0x80 ; // read data from REG
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in8 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 31:24
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in1 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 23:16
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in2 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 15:08
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in3 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 07:00
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in4 = LPC_SSP0->DR;

	LPC_GPIO_PORT->SET[7]  = (1<<25) ;  // cs = 1 da7
//	in7 = 0;

	data_from_reg = in1 << 24 | in2 << 16 | in3 << 8 | in4 ;
}

void read_reg_DA7_64 (unsigned char num_reg, unsigned long long data_from_reg)
{
	unsigned char in1;
	unsigned char in2;
	unsigned char in4;
	unsigned char in8;
	unsigned char in3;
	unsigned char in5;
	unsigned char in6;
	unsigned char in7;
	LPC_GPIO_PORT->CLR[7]  = (1<<25) ;  // cs = 0 da7

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x81 ; // read data from REG0 - CFR1
	LPC_SSP0->DR = num_reg | 0x80 ; // read data from REG
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in8 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 63:56
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in5 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 55:48
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in6 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 47:40
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 39:32
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in8 = LPC_SSP0->DR;


	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 31:24
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in1 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 23:16
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in2 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 15:08
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in3 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
	LPC_SSP0->DR = 0x7F ; // bit 07:00
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in4 = LPC_SSP0->DR;

	LPC_GPIO_PORT->SET[7]  = (1<<25) ;  // cs = 1 da7
//	in7 = 0;

//	data_from_reg = in5 << 56 | in6 << 48 | in7 << 40 | in8 << 32 | in1 << 24 | in2 << 16 | in3 << 8 | in4 ;
}


void write_reg_DA7_32 (unsigned char num_reg, unsigned int data_for_reg)
{
unsigned char in7;
//num_reg

//	LPC_GPIO1->FIOCLR = (1<<21) ; // cs = 0, da7

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x000 ; 					// Write data to REG0 - CFR1
	LPC_SSP0->DR = num_reg & ~(0x80) ; 					// Write data to REG0 - CFR1
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x00 ; 					// bit 31:24
	LPC_SSP0->DR = (data_for_reg >> 24) & 0x0ff ; 					// bit 31:24
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x00 ; 					// bit 23:16 
	LPC_SSP0->DR = (data_for_reg >> 16) & 0x0ff ; 					// bit 23:16 
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x00 ; 					// bit 15:08
	LPC_SSP0->DR = (data_for_reg >> 8) & 0x0ff ; 					// bit 15:08
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

	while ((LPC_SSP0->SR & 0x01) == 0 );
//	LPC_SSP0->DR = 0x02 ; 					// bit 07:00
	LPC_SSP0->DR = (data_for_reg) & 0x0ff ;  					    // bit 07:00
	while ((LPC_SSP0->SR & 0x04) == 0 );
	in7 = LPC_SSP0->DR;

//	LPC_GPIO1->FIOSET = (1<<8) ; //set P1.8 update_0
//
//	in5=0;
//	in6=1;
//
//	LPC_GPIO1->FIOCLR = (1<<8) ; //clr P1.8 update_0
//
//	in5=0;
//	in6=1;
//
//	LPC_GPIO1->FIOSET = (1<<21) ; // cs = 1, da7
}

