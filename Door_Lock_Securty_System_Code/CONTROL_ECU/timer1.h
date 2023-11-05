 /******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: Timer1.h
 *
 * Description: Header file for the Timer1 AVR driver
 *
 * Author: Habiba Elbehairy
 *
 *******************************************************************************/
#include"std_types.h"

#ifndef TIMER1_H_
#define TIMER1_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM                 FALSE
#define CTC_A				0
#define CTC_B				1
#define CTC_MODE			CTC_A


#define OVERFLOWS_PER_MINUTE_NORMAL_MODE 29
#define TICKS_PER_ONE_SECOND 31249

/*
 * Description :
 * enum responsible for Timer1 pre scalar values.
 */
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
} Timer1_Prescaler;

/*
 * Description :
 * enum responsible for Timer1 Mode.
 */
typedef enum{
	NORMAL,CTC=4
}Timer1_Mode;


/*
 * Description :
 * struct responsible for Timer1 Configuration.
 */
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*
 * Description :
 * Functional responsible for Initialize the Timer1 device by:
 * 1. Setup the initial value and the prescalar.
 * 2. Setup the timer mode
 * 3. Enable interrput
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*
 * Description :
 * Functional responsible for Deinitialize the Timer1
 * by setting all registers to zero
 */
void Timer1_deInit(void);
/*
 * Description :
 * Save the address of the Call back function in a global variable
 */

void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
