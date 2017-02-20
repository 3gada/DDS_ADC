unsigned char *BuffDataChar;
int *PosDataByte;
unsigned char *CheckSummData;
unsigned char TypeRdPack;
unsigned char TypeWrPack;
unsigned char CntIDPcakWr;
unsigned char CntIDPcakWrRespon;
unsigned char CntRun;
unsigned int CntWrPack;
char FlgEnableProcess;
char FlgCorrectReception;
unsigned int AmountWrPack;
unsigned char ReceivedCommand;
unsigned char SentCommand;

struct DynamicData
{
    unsigned int time_after_start;
    short temprature1;
    short temprature2;
    short temprature3;
    unsigned char status_sensor;
    unsigned short number_shock;
    unsigned short amplituda_shock;
    unsigned short duration_shock;
    unsigned short number_of_write;
    unsigned char reserved_byte;
} sDynamicData;