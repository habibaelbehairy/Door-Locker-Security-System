 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name:DC_Motor.c
 *
 * Description: Source file for the Dc Motor driver
 *
 * Author: Habiba Elbehairy
 *
 *******************************************************************************/
#include"DC_Motor.h"

/*
 * Function Name : DcMotor_Init
 * Description : Function responsible for setup the direction for the two motor pins through the GPIO driver
 * Parameters : void.
 * Return : void.
 */
void DcMotor_Init(void){
	/*
	 * Configure pin IN1_PIN_ID and IN2_PIN_ID as output pins
	 */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,IN2_PIN_ID,PIN_OUTPUT);

	/*
	 * Motor is stop at the beginning
	 */

	GPIO_writePin(DC_MOTOR_PORT_ID,IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID,IN2_PIN_ID, LOGIC_LOW);

}

/*
 * Function Name : DcMotor_Rotate
 * Description : The function responsible for rotate the DC Motor CW/ or A-CW or
 *  			 stop the motor based on the state input state value.
 * Parameters : DcMotor_State: state of the Motor (STOP,CW,A-CW), Speed : speed of the motor.
 * Return : void.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if (state==STOP){
		// Stop the motor
		GPIO_writePin(DC_MOTOR_PORT_ID,IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,IN2_PIN_ID, LOGIC_LOW);
	}
	else if(state==CLOCKWISE){
		// Rotate the motor --> clock wise
		GPIO_writePin(DC_MOTOR_PORT_ID,IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,IN2_PIN_ID, LOGIC_HIGH);

	}else{
		// Rotate the motor --> anti-clock wise
		GPIO_writePin(DC_MOTOR_PORT_ID,IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID,IN2_PIN_ID, LOGIC_LOW);
	}

	PWM_Timer0_Start(speed);
}
