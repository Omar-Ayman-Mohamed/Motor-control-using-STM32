/*
 * UART.c
 *
 *  Created on: Sep 11, 2022
 *      Author: wario
 */

#include "stm32f4xx.h"
#include"gpio.h"
#include"UART.h"
unsigned char txBuffer[200];
unsigned char txDataSizeToSend;
unsigned char txDataSizeLeftToSend;
void UART1_INIT(void)
{
	// configure GPIO for alternate function mode
	//Enable clock access to port A
	RCC->AHB1ENR |=(1u<<0);
	//Set pin 9,10 in port A to alternate mode
	GPIOA->MODER |=(0xAu<<18);

	// Set Alternate function to AF07 for pin 9 and 10
	GPIOA->AFR[1] |= (1u<<4);
	GPIOA->AFR[1] |= (1u<<5);
	GPIOA->AFR[1] |= (1u<<6);
	GPIOA->AFR[1] &= ~(1u<<7);

	GPIOA->AFR[1] |= (1u<<8);
	GPIOA->AFR[1] |= (1u<<9);
	GPIOA->AFR[1] |= (1u<<10);
	GPIOA->AFR[1] &= ~(1u<<11);



	// Enable clock access to uart1
	RCC->APB2ENR |= (1u<<4);
	//Set Baud rate ,USARTDIV = Fclck/16*baudrate ,here baud rate is 115200 , Fclck 84Mhz
	USART1->BRR = 0x8B;
	// Enable Transmitter
	USART1->CR1 = (1u<<3);
	// Enable Receiver
	USART1->CR1 |= (1u<<2);
	// Enable USART
	USART1->CR1 |= (1u<<13);
}



void UART1_Write(unsigned char data)
{
	USART1->DR = data;
	//wait for transmition to complete
	while(!(USART1->SR&(1u<<6))){}
}

char UART1_Read(void)
{
	//wait till read data register is ready to be read
	while(!(USART1->SR&(1u<<5))){}
	return USART1->DR;
}
void Send_String(const signed char * const pcString, unsigned short StringLength){

	int i;

	if(txDataSizeLeftToSend == 0 && pcString != 0)
	{
	  txDataSizeToSend = StringLength;
	  txDataSizeLeftToSend = StringLength;

	  for(i = 0;i < StringLength; i++)
	  {
		  txBuffer[i] = pcString[i];
		  UART1_Write(txBuffer[txDataSizeToSend - txDataSizeLeftToSend--]);
	  }
	}

}
void Read_String( signed char *  pcString,unsigned short StringLength){
	for(int i = 0; i < StringLength ; i ++){
		pcString[i] = UART1_Read();
	}
}
