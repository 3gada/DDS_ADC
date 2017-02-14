#ifndef _SKLPC4357LIB_H
#define _SKLPC4357LIB_H

typedef struct {
    uint32_t RTC_Sec;
    uint32_t RTC_Min; 
    uint32_t RTC_Hour; 
    uint32_t RTC_Mday; 
    uint32_t RTC_Mon; 
    uint32_t RTC_Year; 
    uint32_t RTC_Wday; 
    uint32_t RTC_Yday; 
} RTCTime; 

/*----------------------------------------------------------------------------
  RTC functions
 *----------------------------------------------------------------------------*/

extern void InitRTC (void);
extern void DeInitRTC (void);
extern void RTCStart (void);
extern void RTCStop (void);
extern void RTC_IRQHandler (void);
extern void RTCSetTime (RTCTime Time);
extern RTCTime RTCGetTime( void );

/*----------------------------------------------------------------------------
  Delay functions
 *----------------------------------------------------------------------------*/

//extern void Delay (uint32_t counter);
//extern void Delay_s (uint16_t s);
//extern void Delay_ms (uint16_t ms);
//extern void Delay_mks (uint16_t mks);

/*----------------------------------------------------------------------------
  Text LCD functions
 *----------------------------------------------------------------------------*/

//extern void WriteByte4 (uint32_t b);
//extern void WriteByte (uint32_t b);
//extern void WriteCommand (uint32_t c);
//extern void WriteData (uint32_t d);
//extern void ClrLCD (void);
//extern void InitLCD (void);
//extern void LCDputc (uint8_t c);
//extern void LCDputs (uint8_t *s);
//extern LCDgotoxy (uint32_t x, uint32_t y);

/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate, Power On
 *----------------------------------------------------------------------------*/

//extern void InitUart (uint16_t uart, uint16_t baund);
//extern void InitUart0_115200 (void);
extern void InitUart1_115200 (void);
//extern void InitUart2_115200 (void);
//extern void InitUart3_115200 (void);
//extern void InitUart0_9600 (void);
//extern void InitUart1_9600 (void);
//extern void InitUart2_9600 (void);
//extern void InitUart3_9600 (void);

/*----------------------------------------------------------------------------
  UART Power Off
 *----------------------------------------------------------------------------*/

//extern void DeInitUart0 (void);
//extern void DeInitUart1 (void);
//extern void DeInitUart2 (void);
//extern void DeInitUart3 (void);
//extern void DeInitUartAll (void);

/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/

extern int UART1_putChar (uint8_t c);

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/

extern int UART1_getChar (void); 

/*----------------------------------------------------------------------------
  Read character from Serial Port   (non blocking read)
 *----------------------------------------------------------------------------*/

extern int UART1_getChar_nb (void); 

/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/

extern void UART1_putString (uint8_t *s);

#endif