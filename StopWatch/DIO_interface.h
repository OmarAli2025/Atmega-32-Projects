#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/*Port Defenitation*/

# define  DIO_u8PORTA 0u
# define  DIO_u8PORTB 1u
# define DIO_u8PORTC   2u
# define DIO_u8PORTD   3u

/*Pin Definations*/

# define DIO_u8PIN0 0u
# define DIO_u8PIN1 1u
# define DIO_u8PIN2 2u
# define DIO_u8PIN3 3u
# define DIO_u8PIN4 4u
# define DIO_u8PIN5 5u
# define DIO_u8PIN6 6u
# define DIO_u8PIN7 7u

/*PIN Direction Defenations*/

# define DIO_u8INPUT    0u
# define DIO_u8OUTPUT 1u

/*PIN Value Defenations*/

# define DIO_u8LOW   0u
# define DIO_u8HIGH 1u

uint8t DIO_u8SetPinDirection(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t copy_u8Direction);
uint8t DIO_u8SetPinValue(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t copy_u8Value);
uint8t DIO_u8SetPortDirection(uint8t copy_u8Port,uint8t copy_u8Direction);
uint8t DIO_u8SetPortValue(uint8t copy_u8Port,uint8t copy_u8Value);
uint8t DIO_u8ReadPinValue(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t* copy_pu8Value);
uint8t DIO_u8TogglePinValue(uint8t copy_u8Port,uint8t copy_u8Pin);

#endif
