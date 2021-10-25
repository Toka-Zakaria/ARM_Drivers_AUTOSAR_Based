 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Dio Driver Registers
 *
 * Author: Toka Zakaria
 ******************************************************************************/

#ifndef DIO_REGS_H
#define DIO_REGS_H

#include "Std_Types.h"

#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))

#endif /* DIO_REGS_H */
