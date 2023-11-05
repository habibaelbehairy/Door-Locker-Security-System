 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Description: Header file for the Buzzer AVR driver
 *
 * Author: Habiba Elbehairy
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"
#include "gpio.h"

#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN PIN4_ID
/*
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *  Turn off the buzzer through the GPIO
 */
void Buzzer_init();
/*
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void);
/*
 *Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
