################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../CONTROL_Main.c \
../DC_Motor.c \
../PWM.c \
../external_eeprom.c \
../gpio.c \
../timer1.c \
../twi.c \
../uart.c 

OBJS += \
./Buzzer.o \
./CONTROL_Main.o \
./DC_Motor.o \
./PWM.o \
./external_eeprom.o \
./gpio.o \
./timer1.o \
./twi.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./CONTROL_Main.d \
./DC_Motor.d \
./PWM.d \
./external_eeprom.d \
./gpio.d \
./timer1.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


