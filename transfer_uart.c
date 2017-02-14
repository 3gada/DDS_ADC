//#include <lpc17xx.h>
#include "LPC43xx.h"                    /* LPC43xx Definitions                */
#include "MainData.h"
#include "PackLib.h"
#include "ReadData.h"
#include "WriteData.h"
#include "CommandResponse.h"

#define period_sensor 480000       //  100 Hz

//int ReadSPI();
//unsigned char write_uart ();
unsigned int number_read;
unsigned int rrr ;
// -------------------------------------------------------------------------------------------------------------------------------------

void Get_moving();
void GetOptionBlock();
void GetCalibrationBlock();

//------????????-----------------------------------------------------------------------------------------------------------------------------
void RunIteration();							/*???????? ?????*/
void ReadDataRxD();	  							/*?????????*/
void WriteDataWxD();	 						/*?????? ??*/
void FormPackWr();
void WriteSPI();

void WriteDataFlash();
void WritePackFlash();
void ReadDataFlash();

//void PutCalibrationBlock();
//void PutDynamicData();

int Put_Read_Data_from_RAM();
int Put_Read_Data_from_RAM_next();
int Put_WHO_AM_I();
int Put_work_mode();
int Put_mode_make_LFM();
int Put_DDS_F_begin();
int Put_DDS_F_end();
int Put_DDS_step_changed_F();
int Put_DDS_time_changed_F();
int Put_DAC_out_value();
int Put_DAC_number_of_point_in_period();
int Put_STATUS_REG2();
int Put_DAC_F_sampling();
int Put_FIFO_SRC_REG();
int Put_INT1_CFG();
int Put_INT1_SOURCE();
int Put_manual_code_antenn();
int Put_time_reconnect_a();
int Put_code_antenn();
int Put_CLICK_SRC();
int Put_CLICK_THS();
int Put_TIME_LIMIT();
int Put_adc_pila();
int Put_number_of_code_antenn();

int Put_OUT_ADC();
int Put_OUT_XYZ();


void Getwork_mode ();
void Getmode_make_LFM    ();
void GetDDS_F_begin    ();
void GetDDS_F_end    ();
void GetDDS_step_changed_F    ();
void GetDDS_time_changed_F    ();
void GetDAC_out_value    ();
void GetDAC_number_of_point_in_period    ();
void GetDAC_F_sampling();
void GetStart_ADC     ();
void Getmanual_code_antenn     ();
void Gettime_reconnect_a();
void Getcode_antenn    ();
void Getcode_antenn_next    ();
void GetCLICK_THS    ();
void Getadc_pila_next   ();
void Getadc_pila ();
void Getnumber_of_code_antenn  ();
void Get_number_of_block_RAM () ;
int PutStateBlock();
int PutOptionBlock();
int PutParametrsData();
void ReadDataRxD();
void WriteDataTxD();

/*--- служебные переменные для интерфейса */
unsigned char BuffGetChar [512] ; //[3300] ; // [512] ; //256];	//  
unsigned char BuffPutChar [512] ; //[3300] ; // [512] ; //[256];	// 
//unsigned char BuffWorkFlash [1024] ; //[256];	// 
int SizeSendPack = 0;
int SizeGetPack = 0;		   		// 
int SizePutPack = 0;		   		// 
unsigned char  VarCRC8 = 0;

int CntGetPack = 0;					// счетчик состояний для приема байта
int CntGetByte = 0;			  		// 
int PosGetByte = 0;			   		// 

int CntPutPack = 0;
int CntPutByte = 0;					// счетчик для передачи байтов
int PosPutByte = 0;				   	// позиция в массиве для отправления на момент формирования

char FlgEndTransmission = 0;
char FlgBeginTransmission = 0;
char FlgGetPack = 0;

unsigned char tmp = 0;
unsigned int number_reciver_packet = 0 ;

unsigned short data_from_RAM ;
/*--------------------------------------*/

int putchar_uart (unsigned char ch); 			
int getchar_uart (unsigned char *ch);
unsigned char  CRC8(unsigned char  data, unsigned char  crc);

	unsigned char GetByte;
unsigned int number_of_data_from_RAM ;
unsigned int Number_of_transmit_block = 0 ;

//------???-----------------------------------------------------------------------------------------------------------------------------
/* ---функция управления пакета и разрешения след-о значения ----*/
void RunIteration()
{	
	if (FlgCorrectReception == 1)
	{
		FlgCorrectReception = 0;
		EnableRD = 0;
		EnableWR = 1; 
		SentCommand = ReceivedCommand;
		
		FlgBeginTransmission = 1;
		SizeSendPack = 1;
		CntPutPack = 0;
	}   
	if (SizeSendPack > 0)
	{
		if (CntPutPack >= SizeSendPack)	 
		{
			EnableRD = 1;
			EnableWR = 0; 
			SizeSendPack = 0;
			CntPutPack = 0;
      FlgEndTransmission = 0;
		} else { if (FlgEndTransmission == 1){ CntPutPack++; }	}
	}
		if (EnableRD) ReadDataRxD();
		if (EnableWR) WriteDataTxD();
}
/*---функция чтения данных */
void ReadDataRxD()
{
	if (getchar_uart(&GetByte))
	{
	 switch (CntGetPack)
	 {
		case 0:
		{
		  if (GetByte == 0x31) CntGetPack = 1;
			CntGetByte = 0;
			VarCRC8 = 0;
			break;
		}
		case 1:
		{
  		if (GetByte == 0x02) CntGetPack = 2;
			else CntGetPack = 0;			
			break;
		}
		case 2:
		{
		  ReceivedCommand	= GetByte;
			switch(ReceivedCommand)
			{
			case 6: {SizeGetPack = 3  ;      break;}
			case 5:	{SizeGetPack = 3; 	     break;}
			case 20:{SizeGetPack = 60+3+8;   break;}
			case 15:{SizeGetPack = 3 ;       break;	}
			case 0x12:{SizeGetPack = 3 ;       break;	}
			case 0x13:{SizeGetPack = 3 ;       break;	}

      case 0x08:{ SizeGetPack = 3 ;     break; }
      case 0x09:{ SizeGetPack = 3+4 ;     break; }
      case 0x0A:{ SizeGetPack = 3 ;     break; }
      case 0x0B:{ SizeGetPack = 3 ;     break; }
      case 0x0C:{ SizeGetPack = 3 ;     break; }
      case 0x0D:{ SizeGetPack = 3 ;     break; }
      case 0x0E:{ SizeGetPack = 3 ;     break; }
			case 0x10:{SizeGetPack = 3 ;     break;	}
			case 0x11:{SizeGetPack = 3 ;     break;	}
			case 0x20:{SizeGetPack = 3 ;     break;	}
      case 0x21:{ SizeGetPack = 3 ;     break; }
      case 0x22:{ SizeGetPack = 3 ;     break; }
      case 0x23:{ SizeGetPack = 3 ;     break; }
      case 0x24:{ SizeGetPack = 3 ;     break; }
      case 0x25:{ SizeGetPack = 3 ;     break; }
      case 0x26:{ SizeGetPack = 3 ;     break; }
      case 0x27:{ SizeGetPack = 3 ;     break; }
      case 0x28:{ SizeGetPack = 3 ;     break; }
      case 0x29:{ SizeGetPack = 3 ;     break; }
      case 0x2A:{ SizeGetPack = 3 ;     break; }
      case 0x2B:{ SizeGetPack = 3 ;     break; }
      case 0x2C:{ SizeGetPack = 3 ;     break; }
      case 0x2D: { SizeGetPack = 3 ;    break; }
      case 0x2E: { SizeGetPack = 3 ;    break; }
      case 0x2F: { SizeGetPack = 3 ;    break; }
      case 0x30: { SizeGetPack = 3 ;    break; }
      case 0x40: { SizeGetPack = 3 + 4;    break; }
      case 0x41: { SizeGetPack = 3 + 4 ;    break; }
      case 0x42: { SizeGetPack = 3 + 4 ;    break; }
      case 0x43: { SizeGetPack = 3 + 4 ;    break; }
      case 0x44: { SizeGetPack = 3 + 4 ;    break; }
      case 0x45: { SizeGetPack = 3 + 4 ;    break; }
      case 0x46: { SizeGetPack = 3 + 4 ;    break; }
      case 0x47: { SizeGetPack = 3 + 4 + 4 ;    break; }
      case 0x48: { SizeGetPack = 3 + 4 ;    break; }
      case 0x49: { SizeGetPack = 3 + 4 ;    break; }
      case 0x4A: { SizeGetPack = 3 + 4 ;    break; }
      case 0x4B: { SizeGetPack = 3 + 4 ;    break; }
      case 0x4C: { SizeGetPack = 3 + 2 + 250*2 ;    break; }
      case 0x4D: { SizeGetPack = 3 + 4 ;    break; }
      case 0x4E: { SizeGetPack = 3 + 250*2 ;    break; }
      case 0x4F: { SizeGetPack = 3 + 2 + 250*2 ;    break; }
      case 0x50: { SizeGetPack = 3 + 250*2 ;    break; }
			default: {break; }
			}
			CntGetPack = 3;
			break;
		}			
		case 3:
		{
		if (CntGetByte >= SizeGetPack)
			{
				if (GetByte == VarCRC8)
				{
					FlgCorrectReception = 1;
					PosGetByte = 3;
					CntGetPack = 0;
					switch(ReceivedCommand)
					 {
					 case 6: {                                               break;}
					 case 5: {						                                   break;}
					 case 0x12:{						                                   break;}
					 case 0x13:{						                                   break;}
					 case 0x14: {GetOptionBlock(BuffGetChar,    &PosGetByte);   break;}  // ???? 8

           case 0x08: { break; }
           case 0x09: {Get_number_of_block_RAM(BuffGetChar,    &PosGetByte);  break; }
           case 0x0A: { break; }
           case 0x0B: { break; }
           case 0x0C: { break; }
           case 0x0D: { break; }
           case 0x0E: { break; }
					 case 0x10:{                                             break;}
					 case 0x11:{                                             break;}
					 case 0x20:{                                             break;}
           case 0x21:{ break; }
           case 0x22:{ break; }
           case 0x23:{ break; }
           case 0x24:{ break; }
           case 0x25:{ break; }
           case 0x26:{ break; }
           case 0x27:{ break; }
           case 0x28:{ break; }
           case 0x29:{ break; }
           case 0x2A:{ break; }
           case 0x2B:{ break; }
           case 0x2C:{ break; }
           case 0x2D:{ break; }
           case 0x2E:{ break; }
           case 0x2F:{ break; }
           case 0x30:{  break; }
           case 0x40: { Getwork_mode (BuffGetChar, &PosGetByte); break; }
           case 0x41: { Getmode_make_LFM    (BuffGetChar, &PosGetByte); break; }
           case 0x42: { GetDDS_F_begin    (BuffGetChar, &PosGetByte); break; }
           case 0x43: { GetDDS_F_end    (BuffGetChar, &PosGetByte); break; }
           case 0x44: { GetDDS_step_changed_F    (BuffGetChar, &PosGetByte); break; }
           case 0x45: { GetDDS_time_changed_F    (BuffGetChar, &PosGetByte); break; }
           case 0x46: { GetDAC_out_value    (BuffGetChar, &PosGetByte); break; }
           case 0x47: { GetDAC_number_of_point_in_period    (BuffGetChar, &PosGetByte); break; }
           case 0x48: { GetDAC_F_sampling(BuffGetChar, &PosGetByte); break; }
           case 0x49: { GetStart_ADC     (BuffGetChar, &PosGetByte); break; }
           case 0x4A: { Getmanual_code_antenn     (BuffGetChar, &PosGetByte); break; }
           case 0x4B: { Gettime_reconnect_a(BuffGetChar, &PosGetByte); break; }
           case 0x4C: { Getcode_antenn    (BuffGetChar, &PosGetByte); break; }
           case 0x4D: { GetCLICK_THS    (BuffGetChar, &PosGetByte); break; }
           case 0x4E: { Getadc_pila_next(BuffGetChar, &PosGetByte); break; }
           case 0x4F: { Getadc_pila (BuffGetChar, &PosGetByte); break; }
//           case 0x50: { Getnumber_of_code_antenn  (BuffGetChar, &PosGetByte); break; }
           case 0x50: { Getcode_antenn_next  (BuffGetChar, &PosGetByte); break; }
					 default:{						                                    break;}
				   } 
			   }
				 else{CntGetPack = 0; }
	    }
      break;     
		  }
		 default:{                                                     break;}
	}
		BuffGetChar[CntGetByte++] = GetByte;
		VarCRC8 = CRC8(GetByte, VarCRC8);
 }
}
/*--- функция записи данных --*/
void WriteDataTxD()
{
	if (FlgBeginTransmission == 1)
	{
		FlgBeginTransmission = 0;
		FormPackWr();	
	}

	if (FlgEndTransmission == 0)
	{
	if (putchar_uart(BuffPutChar[CntPutByte]))
	{
		CntPutByte++;
		if (CntPutByte >= SizePutPack)
		{
			CntPutByte = 0;
			FlgEndTransmission = 1;
		}
	}
  }
}
/*--- функция формирования пакета ---*/
void FormPackWr()
{
    BuffPutChar[0] = 0x3E;
    BuffPutChar[1] = 0x02;	   
	BuffPutChar[2] = SentCommand;
	PosPutByte = 3;
	BuffDataChar = BuffPutChar;
	PosDataByte = &PosPutByte;
	switch(SentCommand)
	{
	case 6:	{PutStateBlock(BuffPutChar, &PosPutByte);		    break;}
	case 5:	{PutOptionBlock(BuffPutChar, &PosPutByte);		  break;}
	case 20:{	                                              break;}  // ???? 8
	case 15:{		                                            break;}
	case 0x12:{PutDynamicData(BuffPutChar, &PosPutByte);		  break;}
//	case 0x13:{PutParametrsData(BuffPutChar, &PosPutByte);	  break;}
	
  case 0x08:{ Put_Read_Data_from_RAM(BuffPutChar,  &PosPutByte); break; }
  case 0x09:{ Put_Read_Data_from_RAM_next(BuffPutChar, &PosPutByte); break; }
  case 0x0A:{ Put_WHO_AM_I(BuffPutChar,        &PosPutByte); break; }
  case 0x0B:{ Put_STATUS_REG2(BuffPutChar,     &PosPutByte); break; }
  case 0x0C:{ Put_FIFO_SRC_REG(BuffPutChar,    &PosPutByte); break; }
  case 0x0D:{ Put_INT1_SOURCE(BuffPutChar,     &PosPutByte); break; }
  case 0x0E:{ Put_CLICK_SRC(BuffPutChar,       &PosPutByte); break; }
	case 0x10:{ Put_OUT_ADC(BuffPutChar,         &PosPutByte); break; }
	case 0x11:{ Put_OUT_XYZ(BuffPutChar,         &PosPutByte); break; }
	case 0x20:{ Put_work_mode(BuffPutChar,    &PosPutByte); break; }
  case 0x21:{ Put_mode_make_LFM(BuffPutChar,       &PosPutByte); break; }
  case 0x22:{ Put_DDS_F_begin(BuffPutChar,       &PosPutByte); break; }
  case 0x23:{ Put_DDS_F_end(BuffPutChar,       &PosPutByte); break; }
  case 0x24:{ Put_DDS_step_changed_F(BuffPutChar,       &PosPutByte); break; }
  case 0x25:{ Put_DDS_time_changed_F(BuffPutChar,       &PosPutByte); break; }
  case 0x26:{ Put_DAC_out_value(BuffPutChar,       &PosPutByte); break; }
  case 0x27:{ Put_DAC_number_of_point_in_period(BuffPutChar,       &PosPutByte); break; }
  case 0x28:{ Put_DAC_F_sampling(BuffPutChar,   &PosPutByte); break; }
  case 0x29:{ Put_INT1_CFG(BuffPutChar,        &PosPutByte); break; }
  case 0x2A:{ Put_manual_code_antenn(BuffPutChar,        &PosPutByte); break; }
  case 0x2B:{ Put_time_reconnect_a(BuffPutChar,   &PosPutByte); break; }
  case 0x2C:{ Put_code_antenn(BuffPutChar,       &PosPutByte); break; }
  case 0x2D:{ Put_CLICK_THS(BuffPutChar,       &PosPutByte); break; }
  case 0x2E:{ Put_TIME_LIMIT(BuffPutChar,      &PosPutByte); break; }
  case 0x2F:{ Put_adc_pila(BuffPutChar,    &PosPutByte); break; }
  case 0x30:{ Put_number_of_code_antenn(BuffPutChar,     &PosPutByte); break; }
  case 0x40: { break; }
  case 0x41: { break; }
  case 0x42: { break; }
  case 0x43: { break; }
  case 0x44: { break; }
  case 0x45: { break; }
  case 0x46: { break; }
  case 0x47: { break; }
  case 0x48: { break; }
  case 0x49: { break; }
  case 0x4A: { break; }
  case 0x4B: { break; }
  case 0x4C: { break; }
  case 0x4D: { break; }
  case 0x4E: { break; }
  case 0x4F: { break; }
  case 0x50: { break; }
  default:{						                                    break;}
	}
	PackU32(CalcCRCBuff(BuffPutChar, 0, PosPutByte), 1);
	SizePutPack = PosPutByte;
	CntPutByte = 0;
	rrr = 0 ;
}

/*--- функция передачи байта --*/ 
int putchar_uart (unsigned char ch) 			
{          
//unsigned char i0 ;
	int i0;
	if (LPC_UART1->LSR & 0x20) 	// проверка готовности UART
	{
		LPC_UART1->THR = ch;
		rrr++ ;
//		for (i0 = 0; i0 < 8000; i0++);
		return 1;
	}return 0;
}
/*---функция приема байта -- */
int getchar_uart (unsigned char *ch) 				
{    
unsigned char i0 ;     
unsigned char i1 ;     
	i0 = 0 ;
	i1 = LPC_UART1->LSR ;
	if(i1 & 0x01) 	// проверяем наличие нового байта в UART
	{
		*ch = LPC_UART1->RBR;
	  if((i1 & 0x0E) == 0) 	{i0 = 1;}// проверяем наличие ошибок приема в UART
	}
	return i0;
}

// -------------------------------------------------------------------------------------------------------------------------
void GetOptionBlock(unsigned char *BuffChar, int *PosByte)
{		
//	unsigned i0;
//	unsigned i1;
	BuffDataChar = BuffChar;
	PosDataByte = PosByte;

	work_mode = UnPackU32(4); 
	mode_make_LFM = UnPackU32(4);  
	DDS_F_begin = UnPackU32(4);  
	DDS_F_end = UnPackU32(4);  
	DDS_step_changed_F = UnPackU32(4);  
	DDS_time_changed_F = UnPackU32(4); 
	DAC_out_value = UnPackU32(4); 
	DAC_number_of_point_in_period = UnPackU32(4); 
	DAC_F_sampling = UnPackU32(4); 
	Start_ADC = UnPackU32(4); 
	manual_code_antenn = UnPackU32(4); 
//	change_param_X = 1 ;
//	change_param_Y = 1 ;

	time_reconnect_a = UnPackU32(4); 
	code_antenn[0] = UnPackU32(2) ;
	CLICK_THS = UnPackU32(4) ;
	TIME_LIMIT = UnPackU32(4) ;
	TIME_LATENCY = UnPackU32(4) ;
	number_of_code_antenn = UnPackU32(2) ;
}

void Get_number_of_block_RAM (unsigned char *BuffChar, int *PosByte)	 
			{
				BuffDataChar = BuffChar; PosDataByte = PosByte; 
				Number_of_transmit_block = UnPackU32(4);
				address_ext_RAM_read = (unsigned int *) Base_address_ext_RAM ;
				address_ext_RAM_read = address_ext_RAM_read + Number_of_transmit_block * 250  ;
			}

void Getwork_mode (unsigned char *BuffChar, int *PosByte)	 {BuffDataChar = BuffChar; PosDataByte = PosByte; work_mode  = UnPackU32(4);	 }// WriteSPI(work_mode,  0x1F);}
void Getmode_make_LFM    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; mode_make_LFM     = UnPackU32(4); }// WriteSPI(mode_make_LFM,     0x20);}
void GetDDS_F_begin    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; DDS_F_begin     = UnPackU32(4); }// WriteSPI(DDS_F_begin,     0x21);}
void GetDDS_F_end    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; DDS_F_end     = UnPackU32(4); }// WriteSPI(DDS_F_end,     0x22);}
void GetDDS_step_changed_F    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; DDS_step_changed_F     = UnPackU32(4); }// WriteSPI(DDS_step_changed_F,     0x23);}
void GetDDS_time_changed_F    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; DDS_time_changed_F     = UnPackU32(4); }// WriteSPI(DDS_time_changed_F,     0x24);}
void GetDAC_out_value    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; DAC_out_value     = UnPackU32(4); set_DAC = 1 ;}// WriteSPI(DAC_out_value,     0x25);}
void GetDAC_number_of_point_in_period    (unsigned char *BuffChar, int *PosByte)
	   {
			BuffDataChar = BuffChar; PosDataByte = PosByte; 
		  DAC_number_of_point_in_period     = UnPackU32(4); 
			 if (DAC_number_of_point_in_period > 1500) {DAC_number_of_point_in_period = 1500 ;}
			DAC_F_sampling = UnPackU32(4);
			 
		LPC_TIMER0->TCR       = 0x2;
		LPC_TIMER0->MR0       = DAC_F_sampling ;
		LPC_TIMER0->TCR       = 0x1; 

		 }
void GetDAC_F_sampling(unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; DAC_F_sampling = UnPackU32(4); }// WriteSPI(DAC_F_sampling, 0x2E);}
void GetStart_ADC     (unsigned char *BuffChar, int *PosByte)
	 {
		BuffDataChar = BuffChar; PosDataByte = PosByte; 	
		num_byte_ADC = 0 ; 
		address_ext_RAM = (unsigned int *) Base_address_ext_RAM ;
		work_ADC = 0 ;
	  Ready_ADC = 0 ;
		Start_ADC      = 1 ; /*UnPackU32(4);*/ 
		On_antenn = 1 ;
		}
void Getmanual_code_antenn     (unsigned char *BuffChar, int *PosByte)
	{BuffDataChar = BuffChar; PosDataByte = PosByte; manual_code_antenn      = UnPackU32(4); 
			LPC_GPIO_PORT->PIN[4] = (manual_code_antenn & 0x0FFFF) ;    // Code Antenn
	}// WriteSPI(manual_code_antenn,      0x32);}
void Gettime_reconnect_a(unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; time_reconnect_a = UnPackU32(4); }// WriteSPI(time_reconnect_a, 0x33);}
void Getcode_antenn    (unsigned char *BuffChar, int *PosByte)
	{ unsigned i ;
		BuffDataChar = BuffChar; PosDataByte = PosByte; 
		number_of_code_antenn   = UnPackU32(2);		
		for (i = 0; i<250; i++){	code_antenn[i]     = UnPackU32(2);}
		number_reciver_packet = 1 ;
		}
void Getcode_antenn_next   (unsigned char *BuffChar, int *PosByte)
	{ unsigned i, r ;
		BuffDataChar = BuffChar; PosDataByte = PosByte; 
		for (i = 0; i<250; i++)
     {
		 r = (number_reciver_packet*250) + i ;
 		 if (r >= 1600) {r--;}
		 code_antenn[(number_reciver_packet*250) + i]     = UnPackU32(2);
		 }
		number_reciver_packet ++ ;
		}
void GetCLICK_THS    (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; CLICK_THS     = UnPackU32(4); }// WriteSPI(CLICK_THS,     0x3A);}
void Getadc_pila_next   (unsigned char *BuffChar, int *PosByte)
	{ unsigned i, r ;
		BuffDataChar = BuffChar; PosDataByte = PosByte; 
		for (i = 0; i<250; i++)
		{
		 r = (number_reciver_packet*250) + i ;
 		 if (r >= 1500) {r--;}
		 ArrPila[(number_reciver_packet*250) + i] = UnPackU32(2);
		}
		number_reciver_packet ++ ;
		}
void Getadc_pila (unsigned char *BuffChar, int *PosByte)
	{ unsigned i ;
		BuffDataChar = BuffChar; PosDataByte = PosByte;
		number_of_code_pila   = UnPackU32(2);		
		for (i = 0; i<250; i++){	ArrPila[i]     = UnPackU32(2);}
		number_reciver_packet = 1 ;
//		for (i = 0; i<1500; i++){	ArrPila[i]     = UnPackU32(2);}
	 }
void Getnumber_of_code_antenn  (unsigned char *BuffChar, int *PosByte){BuffDataChar = BuffChar; PosDataByte = PosByte; number_of_code_antenn   = UnPackU32(2); }// WriteSPI(number_of_code_antenn,   0x3D);}

//--------------------------------------------------------------------------------------------------------------------------


int PutStateBlock(unsigned char *BuffChar, int *PosByte)
{		
	BuffDataChar = BuffChar;
	PosDataByte = PosByte;
	
//	status_block ^= 0x040;
	status_block ^= 0x080;

	status_block &= ~(0x01F | (1 << 6)) ;
	status_block |= (work_mode & 0x01F) | ((Ready_ADC & 0x01) << 6) | ((err_ext_RAM & 0x01) << 5);
//	status_block |= (Ready_ADC & 0x01) << 6 ;
	
//	status_block=0x55;
	status_block1=0x0AA;

	PackU32(status_block, 1);
	PackU32(status_block1, 1);
	
	Ready_ADC = 0 ;
//	PackU32((step_to_finished_X>>1), 4);
//	PackU32((step_to_finished_Y>>1), 4);
//	PackU32(value_encoder_0, 4);
//	PackU32(value_encoder_1, 4);

	return *PosByte;
}
int PutOptionBlock(unsigned char *BuffChar, int *PosByte)
{		
	PackU32(work_mode, 4);
	PackU32(mode_make_LFM, 4);
	PackU32(DDS_F_begin, 4);
	PackU32(DDS_F_end, 4);
	PackU32(DDS_step_changed_F, 4);
	PackU32(DDS_time_changed_F, 4);
	PackU32(DAC_out_value, 4);
	PackU32(DAC_number_of_point_in_period, 4);
	PackU32(DAC_F_sampling, 4);
	PackU32(Start_ADC, 4);
	PackU32(manual_code_antenn, 4);

	PackU32(time_reconnect_a, 4);
	PackU32(code_antenn[0], 2);
	PackU32(CLICK_THS, 4);
	PackU32(TIME_LIMIT, 4);
	PackU32(TIME_LATENCY, 4);
	PackU32(number_of_code_antenn, 2);

//	PackU32(Read_Data_from_RAM, 4);
//	PackU32(Read_Data_from_RAM_next, 4);
	PackU32(WHO_AM_I, 4);
	PackU32(STATUS_REG2, 4);
	PackU32(FIFO_SRC_REG, 4);
	PackU32(INT1_SOURCE, 4);
	PackU32(CLICK_SRC, 4);
	
	PackU32(OUT_ADC0, 4);
	PackU32(OUT_ADC1, 4);
	PackU32(OUT_ADC3, 4);

	PackU32(OUT_X, 4);
	PackU32(OUT_Y, 4);
	PackU32(OUT_Z, 4);

return *PosByte;
}
int Put_work_mode   (unsigned char *BuffChar, int *PosByte){ PackU32(work_mode,   4); return *PosByte;}

int Put_Read_Data_from_RAM (unsigned char *BuffChar, int *PosByte)
  {
	unsigned short i ;

//	number_of_data_from_RAM = number_of_code_antenn * number_of_code_pila ; //400 ; // временно!!!!!!!!!!!!!!!!!!!!!!!!
	number_of_data_from_RAM = (unsigned int) number_of_code_antenn * DAC_number_of_point_in_period * 2; 

		address_ext_RAM_read = (unsigned int *) Base_address_ext_RAM ;
	PackU32(number_of_data_from_RAM, 4);
	for (i = 0 ; i < 250 ; i++)
		{
		data_from_RAM = (*address_ext_RAM_read);//  & 0x0FFFF);
		PackU32(data_from_RAM, 2);
		address_ext_RAM_read++;
		}
//    Number_of_transmit_block = 1;

	return *PosByte;}
	
int Put_Read_Data_from_RAM_next(unsigned char *BuffChar, int *PosByte)
  { 
	unsigned short i ;
		
		PackU32(Number_of_transmit_block, 4);
	for (i = 0 ; i < 250 ; i++)
		{
		data_from_RAM = (*address_ext_RAM_read);//  & 0x0FFFF);
		PackU32(data_from_RAM, 2);
		address_ext_RAM_read++;
		}
//    Number_of_transmit_block++;
	return *PosByte;}
	
int Put_WHO_AM_I       (unsigned char *BuffChar, int *PosByte){/*WHO_AM_I        = ReadSPI(0x0F);*/ PackU32(WHO_AM_I,       4); return *PosByte;}
int Put_mode_make_LFM      (unsigned char *BuffChar, int *PosByte){/*mode_make_LFM       = ReadSPI(0x20);*/ PackU32(mode_make_LFM,      4); return *PosByte;}
int Put_DDS_F_begin      (unsigned char *BuffChar, int *PosByte){/*DDS_F_begin       = ReadSPI(0x21);*/ PackU32(DDS_F_begin,      4); return *PosByte;}
int Put_DDS_F_end      (unsigned char *BuffChar, int *PosByte){/*DDS_F_end       = ReadSPI(0x22);*/ PackU32(DDS_F_end,      4); return *PosByte;}
int Put_DDS_step_changed_F      (unsigned char *BuffChar, int *PosByte){/*DDS_step_changed_F       = ReadSPI(0x23);*/ PackU32(DDS_step_changed_F,      4); return *PosByte;}
int Put_DDS_time_changed_F      (unsigned char *BuffChar, int *PosByte){/*DDS_time_changed_F       = ReadSPI(0x24);*/ PackU32(DDS_time_changed_F,      4); return *PosByte;}
int Put_DAC_out_value      (unsigned char *BuffChar, int *PosByte){/*DAC_out_value       = ReadSPI(0x25);*/ PackU32(DAC_out_value,      4); return *PosByte;}
int Put_DAC_number_of_point_in_period      (unsigned char *BuffChar, int *PosByte)
  {
	  PackU32(DAC_number_of_point_in_period,      4); 
		PackU32(DAC_F_sampling,  4);
	return *PosByte;}
int Put_STATUS_REG2    (unsigned char *BuffChar, int *PosByte){/*STATUS_REG2     = ReadSPI(0x27);*/ PackU32(STATUS_REG2,    4); return *PosByte;}
int Put_DAC_F_sampling  (unsigned char *BuffChar, int *PosByte){/*DAC_F_sampling   = ReadSPI(0x2E);*/ PackU32(DAC_F_sampling,  4); return *PosByte;}
int Put_FIFO_SRC_REG   (unsigned char *BuffChar, int *PosByte){/*FIFO_SRC_REG    = ReadSPI(0x2F);*/ PackU32(FIFO_SRC_REG,   4); return *PosByte;}
int Put_INT1_CFG       (unsigned char *BuffChar, int *PosByte){/*INT1_CFG        = ReadSPI(0x30);*/ PackU32(Start_ADC,       4); return *PosByte;}
int Put_INT1_SOURCE    (unsigned char *BuffChar, int *PosByte){/*INT1_SOURCE     = ReadSPI(0x31);*/ PackU32(INT1_SOURCE,    4); return *PosByte;}
int Put_manual_code_antenn       (unsigned char *BuffChar, int *PosByte){/*manual_code_antenn        = ReadSPI(0x32);*/ PackU32(manual_code_antenn,       4); return *PosByte;}
int Put_time_reconnect_a  (unsigned char *BuffChar, int *PosByte){/*time_reconnect_a   = ReadSPI(0x33);*/ PackU32(time_reconnect_a,  4); return *PosByte;}
int Put_code_antenn      (unsigned char *BuffChar, int *PosByte){/*code_antenn       = ReadSPI(0x38);*/ PackU32(code_antenn[0],      2); return *PosByte;}
int Put_CLICK_SRC      (unsigned char *BuffChar, int *PosByte){/*CLICK_SRC       = ReadSPI(0x39);*/ PackU32(CLICK_SRC,      4); return *PosByte;}
int Put_CLICK_THS      (unsigned char *BuffChar, int *PosByte){/*CLICK_THS       = ReadSPI(0x3A);*/ PackU32(CLICK_THS,      4); return *PosByte;}
int Put_TIME_LIMIT     (unsigned char *BuffChar, int *PosByte){/*TIME_LIMIT      = ReadSPI(0x3B);*/ PackU32(TIME_LIMIT,     4); return *PosByte;}
int Put_adc_pila   (unsigned char *BuffChar, int *PosByte){/*TIME_LATENCY    = ReadSPI(0x3C);*/ PackU32(TIME_LATENCY,   4); return *PosByte;}
int Put_number_of_code_antenn    (unsigned char *BuffChar, int *PosByte){/*number_of_code_antenn     = ReadSPI(0x3C);*/ PackU32(number_of_code_antenn,    2); return *PosByte;}

int Put_OUT_ADC        (unsigned char *BuffChar, int *PosByte)
  {
	work_ADC = 0 ;
	Ready_ADC = 0 ;
	Start_ADC = 1 ;

	while (Ready_ADC == 0){;}
	OUT_ADC3++ ;
	PackU32(OUT_ADC0,    4);
	PackU32(OUT_ADC1,    4);
	PackU32(OUT_ADC3,    4);
  return *PosByte;	
	}
int Put_OUT_XYZ        (unsigned char *BuffChar, int *PosByte)
  {
	OUT_X = 0;//ReadSPI(0x28) | ReadSPI(0x29) << 8;
	OUT_Y = 1;//ReadSPI(0x2A) | ReadSPI(0x2B) << 8;
	OUT_Z = 2;//ReadSPI(0x2C) | ReadSPI(0x2D) << 8;
	PackU32(OUT_X,    4);
	PackU32(OUT_Y,    4);
	PackU32(OUT_Z,    4);
  return *PosByte;	
	}


//int PutCalibrationBlock(unsigned char *BuffChar, int *PosByte)
//{	
//	int i0;
//	BuffDataChar = BuffChar;
//	PosDataByte = PosByte;

//	PackU32(sCalibrationBlock.AmountCalibration, 1);
//	for (i0 = 0; i0 < 10; i0++)
//	{
//		PackDouble(sCalibrationBlock.koeff_k[i0]);
//		PackDouble(sCalibrationBlock.koeff_b[i0]);
//		PackDouble(sCalibrationBlock.Volume[i0]) ;
//		PackU32(sCalibrationBlock.Level[i0],4)     ;
//	}
//	PackDouble(sCalibrationBlock.Temprature_calibration);
//	PackDouble(sOptionBlock.TSLOPE_T0_k_t);
//	PackDouble(sOptionBlock.TSLOPE_T0_k_t0);

//	return *PosByte;	
//}

int PutDynamicData(unsigned char *BuffChar, int *PosByte)
{		
////	double i0 ;
	unsigned int read;
	unsigned int it;
	BuffDataChar = BuffChar;
	PosDataByte = PosByte;
//	read=1;
//	read=write_uart (number_read);
//	number_read++;
//	if (read==0){number_read=0;}
	for (it = 0; it < 512; it++)
	{
	PackU32(ArrADC[it], 1);
	}
	num_byte_ADC = 0 ;

//	PackU32(sDynamicData.time_after_start, 4);
//	PackU32(sDynamicData.temprature1, 2);
//	PackU32(sDynamicData.temprature2, 2);
//	PackU32(sDynamicData.temprature3, 2);
//	PackU32(sDynamicData.status_sensor, 1);
//	PackU32(sDynamicData.number_shock, 2);
//	PackU32(sDynamicData.amplituda_shock, 2);
//	PackU32(sDynamicData.duration_shock, 2);
//	PackU32(sDynamicData.number_of_write, 2);
//	PackU32(sDynamicData.reserved_byte, 1);
	
//		if (number_of_write != 10)
//			{
//			PackU32(sDynamicData.time_after_start++, 4);
//			PackU32(sDynamicData.temprature1, 2);
//			PackU32(sDynamicData.temprature2, 2);
//			PackU32(sDynamicData.temprature3, 2);
//			PackU32(sDynamicData.status_sensor, 1);
//			PackU32(sDynamicData.number_shock, 2);
//			PackU32(sDynamicData.amplituda_shock, 2);
//			PackU32(sDynamicData.duration_shock, 2);
//			PackU32(sDynamicData.number_of_write, 2);
//			PackU32(sDynamicData.reserved_byte, 1);

//			number_of_write++;
////		}
//			else 
//		{
//			PackU32(0x0ffffffff, 4);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ff, 1);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ffff, 2);
//			PackU32(0x0ff, 1);
//			number_of_write=0;
//		}

return *PosByte;	
}
int PutParametrsData(unsigned char *BuffChar, int *PosByte)
{		
//		write_uart_1 ();
		PackU32(current_mode, 1);
		PackU32(value_level, 1);
		number_read=0;
		return *PosByte;	
}
