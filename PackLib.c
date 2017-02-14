#include "MainData.h"
#include "PackLib.h"
#define crc_polynome 0xA001

unsigned char CalcCRCBuff(unsigned char *Buff, int pos, int Size);
unsigned char  CRC8(unsigned char  data, unsigned char  crc);

double UnPackDouble();	/*---функция распаковки пакета от ПК*/
unsigned int UnPackU32(int Amount); 

void PackDouble(double Data);/*--- функция упаковывания пакета для ПК*/
void PackU32(unsigned int Data, int Amount);
	
double UnPackBuffDouble(unsigned char *Buff, int pos); /*--- распаковка буфера в переменные */
unsigned int UnPackBuffU32(unsigned char *Buff, int pos, int Amount);
int UnPackBuffI32(unsigned char *Buff, int pos);
short UnPackBuffI16(unsigned char *Buff, int pos);
void PackBuffDouble(unsigned char *Buff, int pos, double Data);	/*---упаковка аеременных в буфер*/
void PackBuffU32(unsigned char *Buff, int pos, int Amount, unsigned int Data);

/*---вычисление контрольной суммы */
unsigned char CalcCRCBuff(unsigned char *Buff, int pos, int Size)
{	
	unsigned char crc = 0;
	int i0;
//	for (i0 = 0; i0 < Size; i0++)
	for (i0 = pos; i0 < Size; i0++)
		crc = CRC8(Buff[i0], crc);
	return crc; 	
}
/*---вычисление CRC суммы*/
unsigned char  CRC8(unsigned char  data, unsigned char  crc)
{ 
	unsigned char i = data ^ crc;
	crc = 0;
	if(i & 0x01) crc ^= 0x5e;
	if(i & 0x02) crc ^= 0xbc;
	if(i & 0x04) crc ^= 0x61;
	if(i & 0x08) crc ^= 0xc2;
	if(i & 0x10) crc ^= 0x9d;
	if(i & 0x20) crc ^= 0x23;
	if(i & 0x40) crc ^= 0x46;
	if(i & 0x80) crc ^= 0x8c;
	return crc;
}
/*---функции распаковки пакета от ПК */
double UnPackDouble()
{
	double Data = UnPackBuffDouble(BuffDataChar, *PosDataByte);
	*PosDataByte += 8;
	return Data;
} 	
unsigned int UnPackU32(int Amount)
{
	unsigned int Data = UnPackBuffU32(BuffDataChar, *PosDataByte, Amount);
	*PosDataByte += Amount;
	return Data; 	
}
/*---функции упаковки пакета для ПК */
void PackDouble(double Data)
{
	PackBuffDouble(BuffDataChar, *PosDataByte, Data);
	*PosDataByte += 8;			
} 	
void PackU32(unsigned int Data, int Amount)
{
	PackBuffU32(BuffDataChar, *PosDataByte, Amount, Data);
	*PosDataByte += Amount;	 	
} 
/*---распаковка буфера в переменные --*/
double UnPackBuffDouble(unsigned char *Buff, int pos)
{
	double Data = 0;
//	unsigned long Tmp = 0;
	unsigned long long Tmp = 0;
	int i0;
	for (i0 = 0; i0 < 8; i0++)
		Tmp |= ((long long )Buff[i0+pos]) << i0*8;

	Data = *((double *)(&Tmp));	
	return Data;
}
unsigned int UnPackBuffU32(unsigned char *Buff, int pos, int Amount)
{
	unsigned int Data = 0;
	unsigned long Tmp = 0;
	int i0;
	for (i0 = 0; i0 < Amount; i0++)
		Tmp |= Buff[i0+pos] << i0*8;

	Data = Tmp;	
	return Data;
}
int UnPackBuffI32(unsigned char *Buff, int pos)
{
	int Data = 0;
	unsigned long Tmp = 0;
	int i0;
	for (i0 = 0; i0 < 4; i0++)
		Tmp |= Buff[i0+pos] << i0*8;

	Data = Tmp;	
	return Data;
}
short UnPackBuffI16(unsigned char *Buff, int pos)
{
	short Data = 0;
	unsigned long Tmp = 0;
	int i0;
	for (i0 = 0; i0 < 2; i0++)
		Tmp |= Buff[i0+pos] << i0*8;

	Data = Tmp;	
	return Data;
}
/*---упаковка переменных в буфер --*/
void PackBuffDouble(unsigned char *Buff, int pos, double Data)
{
	unsigned long long Tmp = *((unsigned long long *)&Data);
//	unsigned long Tmp = *((unsigned long *)&Data);
	int i0;
	for (i0 = 0; i0 < 8; i0++)
   {
			Buff[i0+pos] = (Tmp >> i0*8) & 0xFF; 
//		Buff[i0+pos] = unsigned long long (Tmp >> i0*8) & 0xFF; 
	 }
}
void PackBuffU32(unsigned char *Buff, int pos, int Amount, unsigned int Data)
{
	unsigned long Tmp = Data;
	int i0;
	for (i0 = 0; i0 < Amount; i0++)
		Buff[i0+pos] = (Tmp >> i0*8) & 0xFF; 
}
//void PackBuffUchar(unsigned char *Buff, int pos, int Amount, unsigned char Data)
//{
////	unsigned long Tmp = Data;
//	int i0;
//	for (i0 = 0; i0 < Amount; i0++)
//		Buff[i0+pos] = Data & 0xFF; 
//}
//void PackUchar(unsigned char Data, int Amount)
//{
//	PackBuffUchar(BuffDataChar, *PosDataByte, Amount, Data);
//	*PosDataByte += Amount;	 	
//} 
