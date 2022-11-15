/*
 * UART.h
 *
 *  Created on: Sep 11, 2022
 *      Author: wario
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void UART1_INIT(void);
void UART1_Write(unsigned char data);
char UART1_Read(void);
void Send_String(const signed char * const pcString, unsigned short StringLength);
void Read_String( signed char *  pcString,unsigned short StringLength);

#endif /* INC_UART_H_ */
