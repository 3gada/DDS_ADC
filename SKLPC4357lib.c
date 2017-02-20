#include "SKLPC4357lib.h"
#include "Global.h"
#include "LPC43xx.h"

void RTCSetTime(RTCTime Time)
{
    LPC_RTC->SEC = Time.RTC_Sec;
    LPC_RTC->MIN = Time.RTC_Min;
    LPC_RTC->HRS = Time.RTC_Hour;
    LPC_RTC->DOM = Time.RTC_Mday;
    LPC_RTC->DOW = Time.RTC_Wday;
    LPC_RTC->DOY = Time.RTC_Yday;
    LPC_RTC->MONTH = Time.RTC_Mon;
    LPC_RTC->YEAR = Time.RTC_Year;
}

RTCTime RTCGetTime(void)
{
    RTCTime LocalTime;

    LocalTime.RTC_Sec = LPC_RTC->SEC;
    LocalTime.RTC_Min = LPC_RTC->MIN;
    LocalTime.RTC_Hour = LPC_RTC->HRS;
    LocalTime.RTC_Mday = LPC_RTC->DOM;
    LocalTime.RTC_Wday = LPC_RTC->DOW;
    LocalTime.RTC_Yday = LPC_RTC->DOY;
    LocalTime.RTC_Mon = LPC_RTC->MONTH;
    LocalTime.RTC_Year = LPC_RTC->YEAR;
    return (LocalTime);
}

void RTC_IRQHandler(void)
{
    LPC_RTC->ILR |= 0x01;
}

void InitRTC(void)
{
    //g        LPC_SC->PCONP |= (1 << 9);
    //g        if ( LPC_RTC->RTC_AUX & (0x1<<4) )
    {
	//g                LPC_RTC->RTC_AUX |= (0x1<<4);
    }
    LPC_RTC->AMR = 0;
    LPC_RTC->CIIR = 1;
    LPC_RTC->CCR = 0x10;
    LPC_RTC->CCR |= 0x01;
    //g        NVIC_EnableIRQ(RTC_IRQn) ;
}

void DeInitRTC(void)
{
    //g        LPC_SC->PCONP &=~(1 << 9);
}

void RTCStart(void)
{
    LPC_RTC->CCR |= 0x01;
}

void RTCStop(void)
{
    LPC_RTC->CCR &= ~0x01;
}

/*
void Delay (uint32_t counter) 
{  
while (counter--);
}

void Delay_s (uint16_t s) 
{  
const uint32_t i = 12000000;
while (s)
{
Delay (i);
s--;
}
}

void Delay_ms (uint16_t ms) 
{  
const uint16_t i = 12000;
while (ms)
{
Delay (i);
ms--;
}
}

void Delay_mks (uint16_t mks) 
{  
const uint8_t i = 12;
while (mks)
{
Delay (i);
mks--;
}
}
*/
/*
void WriteByte4 (uint32_t b)
{
LPC_GPIO1->FIODIR |= 0x3F00000;
LPC_GPIO1->FIOCLR = 0xF00000; 
LPC_GPIO1->FIOSET = (b & 0xF)<<20;
LPC_GPIO1->FIOSET = 0x2000000;
Delay (1000);
LPC_GPIO1->FIOCLR = 0x2000000;
Delay (1000);
LPC_GPIO1->FIOSET = 0xF;  
}

void WriteByte (uint32_t b)
{
WriteByte4 (b>>4);
WriteByte4 (b);
}

void WriteCommand (uint32_t c)
{
LPC_GPIO1->FIOCLR = 0x1000000;
WriteByte (c);
}

void WriteData (uint32_t d)
{
LPC_GPIO1->FIOSET = 0x1000000;
WriteByte (d);
}

*/

void InitUart1_115200(void)
{

    // Init UART1
    //  P3_5-> U1_RXD -> Func4
    //  P3_4-> U1_TXD -> Func4
    LPC_SCU->SFSP3_5 = 4 | (1 << 5) | (1 << 6); // Func4, EHS =1 (Fast Speed) U1_RXD, EZI = 1 input buffer enable
    LPC_SCU->SFSP3_4 = 4 | (1 << 5);		// Func4, EHS =1 (Fast Speed) U1_TXD

    //    LPC_UART1->FCR    = 7;
    LPC_UART1->FCR = 1;
    //		LPC_UART1->FCR   |= 3 << 6;

    LPC_UART1->LCR = 0x87; /* 8 bits, no Parity, 2 Stop bit  */
    LPC_UART1->DLL = 110;  /* 115200 Baud Rate @ 204.0 MHZ PCLK */
    LPC_UART1->DLM = 0;    /* High divisor latch = 0         */
    LPC_UART1->LCR = 0x07; /* DLAB = 0                       */
			   //		        LPC_UART1->MCR    = (1<<4);
}

void InitUart1_921600(void)
{

    // Init UART1
    //  P3_5-> U1_RXD -> Func4
    //  P3_4-> U1_TXD -> Func4
    LPC_SCU->SFSP3_5 = 4 | (1 << 5) | (1 << 6); // Func4, EHS =1 (Fast Speed) U1_RXD, EZI = 1 input buffer enable
    LPC_SCU->SFSP3_4 = 4 | (1 << 5);		// Func4, EHS =1 (Fast Speed) U1_TXD

    //    LPC_UART1->FCR    = 7;
    LPC_UART1->FCR = 1;
    //		LPC_UART1->FCR   |= 3 << 6;

    LPC_UART1->LCR = 0x87; /* 8 bits, no Parity, 2 Stop bit  */
    LPC_UART1->DLL = 14;   //39;                           /* 921600 Baud Rate @ 204.0 MHZ PCLK */
    //LPC_UART1->FDR    = 0x21;                          /* FR 1,51, DIVADDVAL = 1, MULVAL = 2 */
    LPC_UART1->DLM = 0;    /* High divisor latch = 0         */
    LPC_UART1->LCR = 0x07; /* DLAB = 0                       */
			   //		        LPC_UART1->MCR    = (1<<4);
}

void InitUart1_1843200(void)
{

    // Init UART1
    //  P3_5-> U1_RXD -> Func4
    //  P3_4-> U1_TXD -> Func4
    LPC_SCU->SFSP3_5 = 4 | (1 << 5) | (1 << 6); // Func4, EHS =1 (Fast Speed) U1_RXD, EZI = 1 input buffer enable
    LPC_SCU->SFSP3_4 = 4 | (1 << 5);		// Func4, EHS =1 (Fast Speed) U1_TXD

    //    LPC_UART1->FCR    = 7;
    LPC_UART1->FCR = 1;
    //		LPC_UART1->FCR   |= 3 << 6;

    LPC_UART1->LCR = 0x87; /* 8 bits, no Parity, 2 Stop bit  */
    LPC_UART1->DLL = 7;    //39;                           /* 1843200 Baud Rate @ 204.0 MHZ PCLK */
    //LPC_UART1->FDR    = 0x21;                          /* FR 1,51, DIVADDVAL = 1, MULVAL = 2 */
    LPC_UART1->DLM = 0;    /* High divisor latch = 0         */
    LPC_UART1->LCR = 0x07; /* DLAB = 0                       */
			   //		        LPC_UART1->MCR    = (1<<4);
}
void InitUart1_3686400(void)
{

    // Init UART1
    //  P3_5-> U1_RXD -> Func4
    //  P3_4-> U1_TXD -> Func4
    LPC_SCU->SFSP3_5 = 4 | (1 << 5) | (1 << 6); // Func4, EHS =1 (Fast Speed) U1_RXD, EZI = 1 input buffer enable
    LPC_SCU->SFSP3_4 = 4 | (1 << 5);		// Func4, EHS =1 (Fast Speed) U1_TXD

    //    LPC_UART1->FCR    = 7;
    LPC_UART1->FCR = 1;
    //		LPC_UART1->FCR   |= 3 << 6;

    LPC_UART1->LCR = 0x87; /* 8 bits, no Parity, 2 Stop bit  */
    LPC_UART1->DLL = 3;    //39;                           /* 3686400 Baud Rate @ 204.0 MHZ PCLK */
    //LPC_UART1->FDR    = 0x21;                          /* FR 1,51, DIVADDVAL = 1, MULVAL = 2 */
    LPC_UART1->DLM = 0;    /* High divisor latch = 0         */
    LPC_UART1->LCR = 0x07; /* DLAB = 0                       */
			   //		        LPC_UART1->MCR    = (1<<4);
}

int UART1_putChar(uint8_t c)
{
    while (!(LPC_UART1->LSR & 0x20))
	;
    return (LPC_UART1->THR = c);
}

int UART1_getChar(void)
{
    while (!(LPC_UART1->LSR & 0x01))
	;
    return (LPC_UART1->RBR);
}

int UART1_getChar_nb(void)
{
    if (LPC_UART1->LSR & 0x01)
	return (LPC_UART1->RBR);
    else
	return 0;
}

void UART1_putString(uint8_t *s)
{
    while (*s != 0)
    {
	UART1_putChar(*s++);
    }
}