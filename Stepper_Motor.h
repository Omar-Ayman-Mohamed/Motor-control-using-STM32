/*
 * Stepper_Motor.h
 *
 *  Created on: Sep 10, 2022
 *      Author: wario
 */

#ifndef INC_STEPPER_MOTOR_H_
#define INC_STEPPER_MOTOR_H_
#include "stm32f4xx.h"
typedef struct Stepper_Motor_Pins_Config{
	unsigned char pin;
	GPIO_TypeDef * GPIO_PORT;
}Stepper_Motor_Pins_Config;

void Stepper_Init(Stepper_Motor_Pins_Config Stepper_Motor_Pins_arr[4]);
void Rotate_Right(int angle,Stepper_Motor_Pins_Config Stepper_Motor_Pins_arr[4]);
void Rotate_LEFT(int angle,Stepper_Motor_Pins_Config Stepper_Motor_Pins_arr[4]);

#endif /* INC_STEPPER_MOTOR_H_ */
