# Door-Locker-Security-System 
Final Project for the embedded system diploma by Mohamed tarek <br />
Developing a door locker security system using:<br />
1- AVR ATmega32 Microcontroller with frequency 8MHZ <br />
2- Drivers: GPIO, Keypad, LCD, Timer, UART, TWI->"I2C", EEPROM, Buzzer and DC-Motor.<br />
The project designed and implemented based on the layered architecture model as follow:<br />
MC1 -> HMI_ECU (Human Machine Interface) with 2x16 LCD and 4x4 keypad..<br />
MC2 -> Control_ECU with EEPROM, Buzzer, and Dc-Motor..<br />
HMI_ECU is just responsible interaction with the user just take inputs through keypad and display messages on the LCD..<br />
CONTROL_ECU is responsible for all the processing and decisions in the system like password checking, open the door and activate the system alarm..<br />
