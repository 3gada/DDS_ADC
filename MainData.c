/*---входной буфер для обработки*/
unsigned char *BuffDataChar;
int *PosDataByte;
unsigned char *CheckSummData;

/*---переменные для обмена с ПК*/
unsigned char TypeRdPack;							
unsigned char TypeWrPack;
//unsigned char EnableRD;
//unsigned char EnableWR;

/*---счетчики*/
unsigned char CntIDPcakWr;			// номер отправляемого пакета
unsigned char CntIDPcakWrRespon; 	// номер приянтого пакета на ПК, используется как ответо правильном принятии
unsigned char CntRun;
unsigned int CntWrPack;

/*---флаги*/
char FlgEnableProcess;
char FlgCorrectReception;

/*---переменные контроля*/
unsigned int AmountWrPack;

/*---переменные протокола*/
unsigned char ReceivedCommand;
unsigned char SentCommand;

//struct StateBlock
//{
//	char BitReady;          //
//	char BitMeasurement;    //
//	char BitStop;           //
//	char BitNotRespon;      //
//	char Temprature_correction_ON  ;    //
//	char Temprature_correction_OFF ;    //
////	char BitWorkOn;         //
//	char BitGenerFreq;      //
//	char BitGenerPWM;       //
//	char Bit4_20mA;         //
//	char BitOmnibus;        //
//	char BitModBus;         //
//} sStateBlock;

/*
struct SetStateBlock
{
	char BitSetGenerFreq;      //
	char BitSetGenerPWM;       //
	char BitSet4_20mA;         //
	char BitSetOmnibus;        //
	char BitSetModBus;         //
	char Set_Temprature_correction_ON  ;    //
	char Set_Temprature_correction_OFF ;    //
//	char BitSetBWorkOn;        //
} sSetStateBlock;
*/

//struct OptionBlock
//{
//    char FCURR_FMIN;            	// 
//    char FCURR_FMAX;            	// 
//    double TSLOPE_T0_k_t;          	// 
//    double TSLOPE_T0_k_t0;         	//
//    double SET_FMIN;               	// 
//    double SET_FMAX;              	// 
//    double SET_PWM_MAX;            	// 
//    char SET_PWM_MOD;           	// 
//    double SET_TRL;                	// 
//    unsigned int SET_FILT_LENG;          // 
//    unsigned int SET_PERIOD;             // 
//    unsigned int FMAX_answer_ultrasonic;          // 

////    double FMIN_answer_ultrasonic;    		// 
//    unsigned int FMIN_answer_ultrasonic;    		// 
//    double TimeDelay15;          		// 
////    double TimeDelay51;          		// 
//    unsigned int AmountResponImp;       // 
//    unsigned int MaxAmountRespon;       // 
//    unsigned int AmountResponAverage;   // 
//    unsigned int AmountResponDesigion;  //
//}  sOptionBlock;

//struct DurationBlock
//{
//     unsigned int AmountDuration;    
//     unsigned int Duration[10];              //
//     unsigned int Delay[10];                 //
//     unsigned int Dist_to_next[10];                 // ????????
//     unsigned int Dist_to_last[10];                 // ????????
////     unsigned int Dist[10];                  //
//} sDurationBlock;

//struct CalibrationBlock
//{
//     unsigned int AmountCalibration;
//     double Volume[10];
//     unsigned int Level[10];
//     double koeff_k[10];
//     double koeff_b[10];
//     double Temprature_calibration	;           		// calibration temprature
//} sCalibrationBlock;

struct DynamicData
{
//     unsigned int Level;
//     double Level;
//     double Temper;
//     double Volume;

      unsigned int time_after_start;
			 short temprature1;
			 short temprature2;
			 short temprature3;
			unsigned char status_sensor;
			unsigned short number_shock;
			unsigned short amplituda_shock;
			unsigned short duration_shock;
//			unsigned char  current_mode;
			unsigned short number_of_write;
			unsigned char reserved_byte;


} sDynamicData;