/*/*******************************************************************************
 *
 *  module: CONTROL ECU
 *
 *  file name: CONTROL_Main.c
 *
 *  Description: source file for the CONTROL ECU micro-controller
 *
 *  Author: Habiba Elbehairy
 *
 *******************************************************************************/

#include"timer1.h"
#include"uart.h"
#include"twi.h"
#include"DC_Motor.h"
#include"Buzzer.h"
#include"common_macros.h"
#include"external_eeprom.h"
#include<avr/io.h>
#include<util/delay.h>

/*******************************************************************************
 *                                  Definitions                                *
 *******************************************************************************/

#define MC1_READY 			0x10
#define MC2_READY 			0x20
#define CHANGE_PASSWORD 	0xA0
#define SAVE 				0xA1
#define END_SAVING 			0xA2
#define CHECK_PASSWORD 		0xA3
#define UNLOCK_DOOR 		0xA4
#define OPEN_BUZZER			0XA5
#define PASSWORD 			0xA6
#define PASSWORD_MATCH		0xA7
#define PASSWORD_DOESNT_MATCH 0xA8
#define PASSWORD_ADDRESS	0x70

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/*
 * variable to cout the seconds in
 * the call back function of timer 1
 */
volatile uint8 g_countSeconds = 0;
/*
 * variable to store status of password match or not
 */
uint8 g_recieveByte = 0;
/* Description:
 * TIMER1 configurations:
 *		initial_value = 0,
 *		compare_value = 31250 ticks per 1 second,
 *		pre-scaler = 256
 *		CTC mode of operation
 */
Timer1_ConfigType Timer1_Configuration = {0,TICKS_PER_ONE_SECOND,F_CPU_256,CTC};
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void Motorwork(void);
void openBuzzer(void);
void Recieve_password(void);
void Check_PasswordCLU(void);
void Timer1_CallBackFun(void);

/*******************************************************************************
 *                              Functions Implementation                        *
 *******************************************************************************/
/*
 * Description:
 * Call back Fun for timer 1
 */
void Timer1_CallBackFun(void){
	g_countSeconds++;
}


/*
 * Description:
 * Function receive password from HMI and write it in EEPROM
 * then send confirmation to HMI
 */

void Recieve_password(void)
{	
	/*
	 * password to store the password
	 * pass_Counter to count the number of digits entered
	*/
	uint8 password,pass_Counter;
	/*
	 * wait for the HMI to send save command
	*/
	while(UART_recieveByte()!= SAVE);
	/*
	 * for loop to receive the password and write it in EEPROM
	*/
	for(pass_Counter=0; pass_Counter<5; pass_Counter++)
	{
		/*
		 * send ready to HMI to send the password
		*/
		UART_sendByte(MC2_READY);
		/*
		 * receive the password
		 */
		password = UART_recieveByte();
		/*
		 * write the password in EEPROM
		 */
		EEPROM_writeByte((PASSWORD_ADDRESS+pass_Counter), password);
		_delay_ms(70);
	}
	/*
	 * send end of saving to HMI
	*/
	UART_sendByte(END_SAVING);
}

/*
 * Description:
 * Function to check the password from HMI with the saved password in EEPROM
 * if the password is correct send confirmation to HMI
 * else send error to HMI
 */

void Check_PasswordCLU(void) {
	/*
	 * password to store the password entered
	 * password_saved to store the password read from eeerom
	 * pass_Counter to count the number of digits entered
	 * Error_Counter to count num of pass entered wrong
	 */
    uint8 password[5];
    uint8 password_saved[5];
    uint8 pass_Counter;
    uint8 Error_Counter = 0;

    /*
     * Wait for the HMI to send the check command
     */
    while (UART_recieveByte() != CHECK_PASSWORD) {
    }

    /*
	 * for loop to receive the password and compare it with
	 * the password it in EEPROM
	 */

    for (pass_Counter = 0; pass_Counter < 5; pass_Counter++) {
        UART_sendByte(MC2_READY);
        password[pass_Counter] = UART_recieveByte();
        EEPROM_readByte((PASSWORD_ADDRESS + pass_Counter), &password_saved[pass_Counter]);

        if (password[pass_Counter] != password_saved[pass_Counter]) {
            Error_Counter++;
        }
        /*
         * if counter greater than one then password entered wrong
         * send PASSWORD_DOESNT_MATCH to HMI
         */
        if (Error_Counter!=0){
        	UART_sendByte(PASSWORD_DOESNT_MATCH);
        }
        /*
         * if counter is equal zero then ppassword is corret
         * send PASSWORD_MATCH to HMI
         */
        else {
               UART_sendByte(PASSWORD_MATCH);
          }
    }
}
/*
 * Description:
 * Function to open the door
 * 1- rotate the motor in clockwise direction for 15 seconds as the door is unlocking
 * 2- stop the motor for 3 seconds as the door is on hold
 * 3- rotate the motor in anti-clockwise direction for 15 seconds as the door is locking
 * 4- stop the motor as the door is locked
*/
void Motorwork(void){

	/*
	 * init timer 1
	 */
	Timer1_init(&Timer1_Configuration);
	Timer1_setCallBack(Timer1_CallBackFun);
	
	/*
	 * Dc Motor
	 */

	g_countSeconds = 0;
	DcMotor_Rotate(CLOCKWISE,100);
	/*
	 * rotate Motor for 15 seconds in clockwise direction
	 * (Unlocking the door)
	 */
	/*
	 * wait for 15 seconds
	 */
	while (g_countSeconds != 15) {
	}

	g_countSeconds = 0;
	/*
	 * Stop Motor for 3 seconds in
	 * (Door on Hold)
	 */
	DcMotor_Rotate(STOP,0);
	/*
	 * wait for 3 seconds
	 */
	while (g_countSeconds != 3) {
	}

	g_countSeconds = 0;
	/*
	 * rotate Motor for 15 seconds in anti-clockwise direction
	 * (locking the door)
	 */
	DcMotor_Rotate(ANTI_CLOCKWISE,100);
	/*
	 * wait for 15 seconds
	 */
	while (g_countSeconds != 15) {
	}

	/*
	 * Stop Motor
	 * (Door locked)
	 */
	DcMotor_Rotate(STOP,0);

	g_countSeconds = 0;
	/*
	 * turn off the timer
	 */
	Timer1_deInit();
}

/*
 * Description:
 * Function to turn on the buzzer for 60 seconds as 
 * the password is wrong for 3 times
*/
void openBuzzer(void){
	/*
	 * init timer 1
	 */
	Timer1_init(&Timer1_Configuration);
	Timer1_setCallBack(Timer1_CallBackFun);
	/*
	 * Turn on buzzer
	 */
	g_countSeconds = 0;
	/*
	 * wait for 60 seconds
	 */
	while (g_countSeconds != 60) {
		Buzzer_on();
	}
	Buzzer_off();
	g_countSeconds = 0;

	/*
	 * turn off the timer
	 */
	Timer1_deInit();

}


int main(){

	/*
	 * Enable interrupts register
	 */
	SREG |= (1 << 7);
	/*
	 * UART configurations:
	 * 		8-bit data mode
	 * 		disable parity checking
	 *		one bit for stop bit
	 *		baud rate = 9600,
	 *		peed double speed
	 */
	UART_ConfigType UART_Configuration= {UART_8_BIT_DATA,DISABLED,ONE_BIT,UART_BAUD_RATE_9600,DOUBLE_SPEED};
	/*
	 * I2C configurations:
	 * 		I2C ADDRESS_1
	 * 		Baud rate =400k
	 */
	TWI_ConfigType TWI_Configuration={ADDRESS_1,TWI_BAUDRATE_400K};

	/*
	 * init Uart
	 */
	UART_init(&UART_Configuration);
	/*
	 * init I2C
	 */
	TWI_init(&TWI_Configuration);
	/*
	 * init Timer1
	 */
	Timer1_init(&Timer1_Configuration);
	/*
	 * set call back for timer 1
	 */
	Timer1_setCallBack(Timer1_CallBackFun);
	/*
	 * init BUZZER
	 */
	Buzzer_init();
	/*
	 * init DcMotor
	*/
	DcMotor_Init();
	 /*
	  * Wait for the MC1 to send the check command
	 */
    while (UART_recieveByte() != MC1_READY);
    /*
     * take the pass and write it in EEROM
     */
    Recieve_password();

    while (1) {
    	/*
    	 * store byte from mc1 in g_recieveByte
    	*/
    	g_recieveByte  = UART_recieveByte();
    	/*
    	 * g_recieveByte == password
    	 * check if pass entered same as pass
    	 * saved in EEROM
    	 */
    	if (g_recieveByte == PASSWORD) {
    		Check_PasswordCLU();
    	}
    	/*
         * g_recieveByte == UNLOCK_DOOR
         * open door
         *
        */
    	else if (g_recieveByte == UNLOCK_DOOR) {
    		Motorwork();
    	}
    	/*
         * g_recieveByte == OPEN_BUZZER
         * Pass entered 3 times wrong
         * open buzzer
         */
    	else if (g_recieveByte == OPEN_BUZZER) {
    		openBuzzer();
    	}
    	/*
    	  * g_recieveByte == CHANGE_PASSWORD
    	  * write new pass in EEROM
    	  *
    	  */
    	else if (g_recieveByte == CHANGE_PASSWORD) {
    	    Recieve_password();
        }
    }
}

