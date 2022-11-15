#include "stm32f4xx.h"
#include"adc.h"
#include"LCD.h"
#include"gpio.h"
#include"UART.h"
#include"Dc_Timer.h"
#include"Stepper_Motor.h"


/*unsigned short int data  ;*/
/*void single_mode(void);*/


unsigned char rxBuffer2[200];
int main(void);

int main(void)
{

unsigned int angle;
	/*stepper motor pins confguration*/
	Stepper_Motor_Pins_Config pins_arr[4];
	pins_arr[0].GPIO_PORT =GPIOA;
	pins_arr[0].pin = (unsigned char)1;

	pins_arr[1].GPIO_PORT =GPIOA;
	pins_arr[1].pin = (unsigned char)2;

	pins_arr[2].GPIO_PORT =GPIOA;
	pins_arr[2].pin =(unsigned char) 3;

	pins_arr[3].GPIO_PORT =GPIOA;
	pins_arr[3].pin = (unsigned char)4;
/*all intialitzations for our perpherials*/
	Stepper_Init(pins_arr);
	LCD_Init();
	TIMER_Init();
	UART1_INIT();
/*read frame*/
	Read_String(rxBuffer2,(unsigned char)8);
	int i = 0 ;
	for( ; i<50000 ; i++){
	}
/*check end of frame*/
	unsigned char e = 'E';
		if(rxBuffer2[(unsigned char)7] == e){
			Send_String(rxBuffer2,(unsigned char)8);
		}
		else{
			LCD_DisplayString("error");
		}

/*check speed bits*/
		/*check if first bit is not zero or one*/
		if((rxBuffer2[0] != (unsigned char)48)&& (rxBuffer2[0] != (unsigned char)49)){
			LCD_DisplayString("error");
		}
		/*checking so that it doesn't exceed 100*/
		else if((rxBuffer2[0] == (unsigned char)49) &&((rxBuffer2[1] !=(unsigned char)48)||(rxBuffer2[2] !=(unsigned char)48))){
			LCD_DisplayString("error");
		}
		else{
		    int s = ((rxBuffer2[0] - 48u)*100u) + ((rxBuffer2[1] -48u)*10u) + ((rxBuffer2[2] - 48u)) ;
			/*LCD_DisplayString("speed:");LCD_IntToStr((unsigned int)speed);*/
			Set_Speed(s);

	}
		return 0 ;
}

/*check direction bit
		if((rxBuffer2[3] == (unsigned char)70)){
			Set_Dir('F');
		}
		else if(rxBuffer2[3] == (unsigned char)66){
			Set_Dir('B');
		}
		else{
			LCD_DisplayString("error");
		}*/
/*check angle bits*/
/*		if((rxBuffer2[4] > (unsigned char)52)){
			LCD_DisplayString("error");
		}else if((rxBuffer2[4]==(unsigned char)52)&&(rxBuffer2[5]>(unsigned char)53)){
			LCD_DisplayString("error");
		}else{
			angle = ((rxBuffer2[4]-48)*10) + (rxBuffer2[5]-48);
		}*/
/*check stepper direction pins*/
/*		if(rxBuffer2[6] == 76){
			LCD_DisplayString("angle:");
			LCD_IntToStr(angle);
			Rotate_LEFT(angle,pins_arr);
		}
		else if(rxBuffer2[6] == 82){
			LCD_DisplayString("angle:-");
			LCD_IntToStr(angle);
			Rotate_LEFT(angle,pins_arr);

		}
		else{
			LCD_DisplayString("error");
		}*/
	/*	LCD_IntToStr(TIM4->CNT/100);*/
	/*	LCD_DisplayString("am");*/













/*	while(1)
	{
	//	Set_Dir('l');
		//LCD_DisplayString("temp: ");
	//	ADC_ReadData(&data);
		//LCD_IntToStr(TIM4->CNT);
	//	for(int i =0 ;i<300000;i++){}
	//	char data = UART1_Read();
	//	UART1_Write(data);
	//	for(int i =0 ;i<200000;i++){}

		//LCD_ClearScreen();

	//	LCD_ClearScreen();



	}

} */

