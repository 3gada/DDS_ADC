extern unsigned char CalcCRCBuff(unsigned char *Buff, int pos, int Size);
extern unsigned char  CRC8(unsigned char  data, unsigned char  crc);

extern double UnPackDouble();	/*---������� ������������ ������ �� ��*/
extern unsigned int UnPackU32(int Amount);

extern void PackDouble(double Data);/*---������� ���������� ������ ��� ��*/
extern void PackU32(unsigned int Data, int Amount);
	
extern double UnPackBuffDouble(unsigned char *Buff, int pos); /*---������� ���������� ������ � ����������*/
extern unsigned int UnPackBuffU32(unsigned char *Buff, int pos, int Amount);
extern int UnPackBuffI32(unsigned char *Buff, int pos);
extern short UnPackBuffI16(unsigned char *Buff, int pos);

extern void PackBuffDouble(unsigned char *Buff, int pos, double Data);	/*---������� �������� ���������� � �����*/
extern void PackBuffU32(unsigned char *Buff, int pos, int Amount, unsigned int Data);
