/*
 * Keypad_cfg.h
 *
 *  Created on: Oct 17, 2026
 *      Author: hp
 */

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

# define  KPD_u8COLUMNPORT DIO_u8PORTC

# define  KPD_u8C0PIN DIO_u8PIN0
# define  KPD_u8C1PIN DIO_u8PIN1
# define  KPD_u8C2PIN DIO_u8PIN2
# define  KPD_u8C3PIN DIO_u8PIN3

# define  KPD_u8ROWPORT DIO_u8PORTC

# define  KPD_u8R0PIN DIO_u8PIN4
# define  KPD_u8R1PIN DIO_u8PIN5
# define  KPD_u8R2PIN DIO_u8PIN6
# define  KPD_u8R3PIN DIO_u8PIN7

# define KPD_au8Arr {{1,2,3,4},	{5,6,7,8},{9,'S','R','L'},{'C',0,255,255}}



# define KPD_u8NOPRESSEDKEY 255





#endif /* KEYPAD_CFG_H_ */
