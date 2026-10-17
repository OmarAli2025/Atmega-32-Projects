#ifndef CLCD_CFG_H
#define CLCD_CFG_H


/*CLCD Configure BIT Mode:
 * 											  1-u8_FOUR_BITMODE
 * 											  2-u8EIGHT_BITMODE			*/

# define CLCD_u8BITMODE 					u8_FOUR_BITMODE

/*Control PINS*/
#define  CLCD_u8CNTRL_PORT	 			DIO_u8PORTA
#define  CLCD_u8RS_PIN							DIO_u8PIN0
#define  CLCD_u8RW_PIN						DIO_u8PIN1
#define  CLCD_u8E_PIN							DIO_u8PIN2

/*Data Pins*/
# define CLCD_u8DATA_PORT    			DIO_u8PORTB

#if CLCD_u8BITMODE == u8_FOUR_BITMODE

	#define CLCD_u8D4  DIO_u8PIN4
	#define CLCD_u8D5  DIO_u8PIN5
	#define CLCD_u8D6  DIO_u8PIN6
	#define CLCD_u8D7  DIO_u8PIN7

#endif



/*Function Set Config*/

#define  CLCD_u8NLINESNUM				CLCD_u8N2LINE
#define   CLCD_u8FONTSIZE					CLCD_u8FONT5X7

/*Display  Config*/

#define 	CLCD_u8DISPLAYMODE				CLCD_u8DON
#define 	CLCD_u8CURSORNMODE			CLCD_u8COFF
#define 	CLCD_u8BLINKNMODE				CLCD_u8BOFF


#endif
