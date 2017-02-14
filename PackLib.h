extern unsigned char CalcCRCBuff(unsigned char *Buff, int pos, int Size);
extern unsigned char  CRC8(unsigned char  data, unsigned char  crc);

extern double UnPackDouble();	/*---функции распакования пакета от ПК*/
extern unsigned int UnPackU32(int Amount);

extern void PackDouble(double Data);/*---функции упакования пакета для ПК*/
extern void PackU32(unsigned int Data, int Amount);
	
extern double UnPackBuffDouble(unsigned char *Buff, int pos); /*---Функции распаковки буфера в переменные*/
extern unsigned int UnPackBuffU32(unsigned char *Buff, int pos, int Amount);
extern int UnPackBuffI32(unsigned char *Buff, int pos);
extern short UnPackBuffI16(unsigned char *Buff, int pos);

extern void PackBuffDouble(unsigned char *Buff, int pos, double Data);	/*---Функции упаковки переменных в буфер*/
extern void PackBuffU32(unsigned char *Buff, int pos, int Amount, unsigned int Data);
