/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Description: Source file for the Buzzer AVR driver
 *
 * Author: Habiba Elbehairy
 *
 *******************************************************************************/
#include "buzzer.h"



void Buzzer_init(){
	/*
	 * set up pin direction of the buzzer
	 * set it off initially
	*/
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_INPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);

}
void Buzzer_on(void){
	/*Turn on the Buzzer*/
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}
void Buzzer_off(void){
	/*Turn off the Buzzer*/
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);

}
