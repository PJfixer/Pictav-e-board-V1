/* 
 * File:   uart.h
 * Author: pierre
 *
 * Created on 8 février 2018, 19:23
 */



void putch( char data);
void usart4_init(void);
uint8_t UART4_Read(void);
void SendUART4(uint8_t txData);
void UART4_SendStr(const char * s);
void UART4_SendDec(unsigned int data);
void UART4_SendHex(unsigned int data);
unsigned char setHEX(unsigned char ch);
void printTable(uint8_t * table,uint8_t size);
void  interpretation(void);


#define RX_BUFFER_SIZE 10 // taille du beffer de reception en octets