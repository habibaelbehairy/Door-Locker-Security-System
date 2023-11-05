 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Habiba Elbehairy
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * Description :
 * enum responsible for Uart data size.
 */
typedef enum {
    UART_5_BIT_DATA,UART_6_BIT_DATA,UART_7_BIT_DATA,UART_8_BIT_DATA,UART_9_BIT_DATA=7
} UART_BitData;

/*
 * Description :
 * enum responsible for parity bit value.
 */
typedef enum {
	DISABLED,RESERVED,EVEN_PARITY,ODD_PARITY
}UART_Parity;

/*
 * Description :
 * enum responsible for stop bit value.
 */
typedef enum {
	ONE_BIT,TWO_BITS
}UART_StopBit;

/*
 * Description :
 * enum responsible for BaudRate value.
 */
typedef enum {
    UART_BAUD_RATE_9600=9600,UART_BAUD_RATE_19200=19200,UART_BAUD_RATE_38400=38400,UART_BAUD_RATE_57600=57600,UART_BAUD_RATE_115200=115200
}UART_BaudRate;

/*
 * Description :
 * enum responsible for Uart speed mode.
 */
typedef enum{
	NORMAL_SPEED,DOUBLE_SPEED
}UART_Speed_Mode;


/*
 * Description :
 * struct responsible for uart Configuration.
 */

typedef struct{
 UART_BitData Bit_data;
 UART_Parity Parity;
 UART_StopBit Stop_Bit;
 UART_BaudRate Baud_Rate;
 UART_Speed_Mode Speed;
}UART_ConfigType;


/*
 * Macro responsible for calculate baudrare for asynchronous normal mode
 */
#define ASYNCHRONOUS_NORMAL_MODE(F_CPU, BAUD_RATE) (((F_CPU) / (BAUD_RATE * 16UL)) - 1)

/*
 * Macro responsible for calculate baudrare for asynchronous double speed mode
 */
#define ASYNCHRONOUS_DOUBLE_SPEED_MODE(F_CPU, BAUD_RATE) (((F_CPU) / (BAUD_RATE * 8UL)) - 1)



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init(UART_ConfigType * config_Ptr);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
