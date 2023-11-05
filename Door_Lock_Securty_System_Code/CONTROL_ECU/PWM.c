 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name:PWM.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Habiba Elbehairy
 *
 *******************************************************************************/
#include"PWM.h"

#include<avr/io.h>
/* Function Name : PWM_Timer0_Start
 * Description : The function responsible for trigger the Timer0 with the PWM Mode.
 * 				 Setup the PWM mode with Non-Inverting.
 * Parameters : duty_cycle: OCR duty cycle Percentage.
 * Return : void.
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	/*
	 * Set Timer Initial value
	 */
	TCNT0 = 0;
	/*
	 * Set Compare Value
	 */

	OCR0 = (int)((float32)duty_cycle / 100.0 * 255 + 0.5);
//	LCD_intgerToString(((float32)duty_cycle/100)*255);
	/*
	 * set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
	 */
	GPIO_setupPinDirection(TIMER0_PORT_ID,OC0_PIN_ID,PIN_OUTPUT);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Non Inverted Mode COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
