void SerialInit(unsigned long int fosc, unsigned int baud, short int bits, short int stopBits, short int parity);
void SerialPrintChar(unsigned char data);
void SerialPrintRaw(short int bits);
void SerialPrint(unsigned char *s);
unsigned char SerialRead(void);
