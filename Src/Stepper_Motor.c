/*
 * Stepper_Motor.c
 *
 *  Created on: Sep 10, 2022
 *      Author: wario
 */

#include"Stepper_Motor.h"
#include "stm32f4xx.h"
#include"gpio.h"

//the function takes array of struct to configure selected pins to control stepper motor
void Stepper_Init( Stepper_Motor_Pins_Config Stepper_Motor_Pins_arr[4]){
	for(int i = 0 ; i< 4 ; i++){
		int local_Pin = Stepper_Motor_Pins_arr[i].pin ;
		GPIO_TypeDef * Local_Port = Stepper_Motor_Pins_arr[i].GPIO_PORT;
		//wehave only port a and b so we enable clock
		if(Local_Port == GPIOA){
			RCC->AHB1ENR |= (1u<<0);
		}else if(Local_Port == GPIOB){
			RCC->AHB1ENR |= (1u<<1);
		}
		//set selected pins as output
		Local_Port->MODER |= (1<<(2*local_Pin));
		Local_Port->MODER &=~(1<<(2*local_Pin+1));
		Local_Port->PUPDR |=(1<<(2*local_Pin+1));
		Local_Port->PUPDR &=~(1<<(2*local_Pin+1));
	}



};
void Rotate_Right(int angle,Stepper_Motor_Pins_Config Stepper_Motor_Pins_arr[4]){
	//here we are utiltzing full drive to control stepper motor
	int step = 0;
	for(int i = 0 ; i<= (angle-1 )/4 ; i ++){
	//delay
	for(int i =0;i<=500000;i++);
	//first step
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,0);
	step ++;
	if(step == angle){
		break;
	}
	for(int i =0;i<=500000;i++);
	//second step
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,0);
	step ++;
	if(step == angle){
		break;
	}
	for(int i =0;i<=500000;i++);
	//third step
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,1);
	step ++;
	if(step == angle){
		break;
	}
	for(int i =0;i<=5000000;i++);
	//fourth step
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,1);
	step ++;
	if(step == angle){
		break;
	}
	}
};
void Rotate_LEFT(int angle,Stepper_Motor_Pins_Config Stepper_Motor_Pins_arr[4]){
	int step = 0;
	for(int i = 0 ; i<= (angle-1 )/4 ; i ++){
	for(int i =0;i<=500000;i++);
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,1);
	step ++;
	if(step == angle){
		break;
	}
	for(int i =0;i<=500000;i++);
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,0);
	step ++;
	if(step == angle){
		break;
	}
	for(int i =0;i<=500000;i++);
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,0);
	step ++;
	if(step == angle){
		break;
	}
	for(int i =0;i<=5000000;i++);
	GPIO_Write(Stepper_Motor_Pins_arr[0].GPIO_PORT,Stepper_Motor_Pins_arr[0].pin,1);
	GPIO_Write(Stepper_Motor_Pins_arr[1].GPIO_PORT,Stepper_Motor_Pins_arr[1].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[2].GPIO_PORT,Stepper_Motor_Pins_arr[2].pin,0);
	GPIO_Write(Stepper_Motor_Pins_arr[3].GPIO_PORT,Stepper_Motor_Pins_arr[3].pin,1);
	step ++;
	if(step == angle){
		break;
	}
	}

};
