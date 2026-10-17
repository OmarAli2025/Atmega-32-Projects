/*
 * Port_reg.h
 *
 *  Created on: Oct 14, 2026
 *      Author: hp
 */

#ifndef PORT_REG_H_
#define PORT_REG_H_

/*Dio Reg Definations */

/*Portx Regs*/
# define PORTA_REG *((volatile uint8t*)0x3B)
# define PORTB_REG *((volatile uint8t*)0x38)
# define PORTC_REG *((volatile uint8t*)0x35)
# define PORTD_REG *((volatile uint8t*)0x32)

/*DDRx Regs*/
# define DDRA_REG *((volatile uint8t*)0x3A)
# define DDRB_REG *((volatile uint8t*)0x37)
# define DDRC_REG *((volatile uint8t*)0x34)
# define DDRD_REG *((volatile uint8t*)0x31)

/*PINx REG*/
# define PINA_REG *((volatile uint8t*)0x39)
# define PINB_REG *((volatile uint8t*)0x36)
# define PINC_REG *((volatile uint8t*)0x33)
# define PIND_REG *((volatile uint8t*)0x30)


#endif /* PORT_REG_H_ */
