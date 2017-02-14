extern void RunIteration();							/*функция управления итерациями*/
extern void ReadDataRxD();	  							/*функция чтения данных*/
extern void WriteDataWxD();	 						/*функция записи данных*/
extern void FormPackWr();
extern int putchar_uart(unsigned char ch); 			
extern int getchar_uart(unsigned char *ch);