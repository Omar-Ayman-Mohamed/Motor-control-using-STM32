/*
 * Dc_Timer.c
 *
 *  Created on: Sep 11, 2022
 *      Author: wario
 */


#include "stm32f4xx.h"
#include"gpio.h"
#include"Dc_Timer.h"


void TIMER_Init(void){
	//enable timer 1 clock
	RCC->APB2ENR |=(1<<0);
	RCC->APB1ENR |=(1<<2);

	TIM4->PSC = 65535;
	TIM4->ARR = 10000;

	TIM4->CR1 |=(1<<0);



	//set pin a8 alt function
	GPIOA->MODER&=~(1<<16);
	GPIOA->MODER|=(1<<17);

	//set alt function pina8 Timer1ch1
	GPIOA->AFR[1] |= (1u<<0);
	GPIOA->AFR[1] &=~ (1u<<1);
	GPIOA->AFR[1] &=~ (1u<<2);
	GPIOA->AFR[1] &= ~(1u<<3);
	//enable autoreload  preload
	TIM1->CR1 |=(1<<7);
	//select upcounter mode
	TIM1->CR1 |=(1<<4);




	//set timerprelaod prescaler the clock is 84mhz so by this we get 1mhz freq
	TIM1->PSC = 84;
	//set autoreload register with value we want to count to
	TIM1->ARR = 1000;

	//configure capture/compare channel 1 as output to generate pwm on it
	TIM1->CCMR1 &=~(1<<0);
	TIM1->CCMR1 &=~(1<<1);

	//enable preload for capture/compare channel 1
	TIM1->CCMR1 |=(1<<3);

	//select pwm mode1
	TIM1->CCMR1 &=~(1<<4);
	TIM1->CCMR1 |=(1<<5);
	TIM1->CCMR1 |=(1<<6);

	//configure output polarity to be active high
	TIM1->CCER &=~(1<<1);
	//enable capture compare channel 1 output
	TIM1->CCER |=(1<<0);

	//enable update on generation event
	TIM1->EGR |= (1<<0);

	//enable output
	TIM1->BDTR |=(1<<15);
	//enable counter
	TIM1->CR1 |= (1<<0);
}
void Set_Speed(int speed){
	//put speed value in capture compare register
	TIM1->CCR1 = speed*10;
}
void Set_Dir(char Dir){
	//here we are using pin 6 and 7 to control direction
	GPIOA->MODER |=(1<<12);
	GPIOA->MODER &=~ (1<<13);
	GPIOA->MODER |=(1<<14);
	GPIOA->MODER &=~ (1<<15);


	if(Dir =='F'){
		GPIO_Write(GPIOA,7,0);
		GPIO_Write(GPIOA,6,1);

	}
	else if(Dir =='B'){
		GPIO_Write(GPIOA,7,1);
		GPIO_Write(GPIOA,6,0);
	}
}

