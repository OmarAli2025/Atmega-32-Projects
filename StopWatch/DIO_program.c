# include "StdLib.h"
#include "BIT_MATH.h"
#include "ErrorStates.h"
#include "DIO_interface.h"
#include "DIO_pvt.h"
#include "DIO_reg.h"
#include "DIO_cfg.h"
# include <util/delay.h>



uint8t DIO_u8SetPinDirection(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t copy_u8Direction)
{
	uint8t local_u8ErrorState=OK;
	if(copy_u8Pin <=DIO_u8PIN7)
	{
		if(copy_u8Direction==DIO_u8INPUT)
		{
			switch(copy_u8Port)
			{
			case DIO_u8PORTA: DDRA_REG&=~(1U<<copy_u8Pin); break;
			case DIO_u8PORTB: DDRB_REG&=~(1U<<copy_u8Pin); break;
			case DIO_u8PORTC: DDRC_REG&=~(1U<<copy_u8Pin); break;
			case DIO_u8PORTD: DDRD_REG&=~(1U<<copy_u8Pin); break;
			default:local_u8ErrorState=NOK;break;/*Invalid Port*/
			}
		}

		else if(copy_u8Direction==DIO_u8OUTPUT)
		{
			switch(copy_u8Port)
			{
			case DIO_u8PORTA: DDRA_REG|=(1U<<copy_u8Pin); break;
			case DIO_u8PORTB: DDRB_REG|=(1U<<copy_u8Pin); break;
			case DIO_u8PORTC: DDRC_REG|=(1U<<copy_u8Pin); break;
			case DIO_u8PORTD: DDRD_REG|=(1U<<copy_u8Pin); break;
			default:local_u8ErrorState=NOK;break;/*Invalid Port*/
			}
		}
		else
		{
			local_u8ErrorState=NOK;/*Invalid  State*/
		}
	}
	else
	{
		local_u8ErrorState=NOK;/*Invalid  Pin Number*/
	}
	return local_u8ErrorState;
}

uint8t DIO_u8SetPinValue(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t copy_u8Value)
{
	uint8t local_u8ErrorState=OK;
	if(copy_u8Pin <=DIO_u8PIN7)
	{
		if(copy_u8Value==DIO_u8LOW)
		{
			switch(copy_u8Port)
			{
			case DIO_u8PORTA: PORTA_REG&=~(1U<<copy_u8Pin); break;
			case DIO_u8PORTB: PORTB_REG&=~(1U<<copy_u8Pin); break;
			case DIO_u8PORTC: PORTC_REG&=~(1U<<copy_u8Pin); break;
			case DIO_u8PORTD: PORTD_REG&=~(1U<<copy_u8Pin); break;
			default:local_u8ErrorState=NOK;break; /*Invalid Port*/
			}
		}

		else if(copy_u8Value==DIO_u8HIGH)
		{
			switch(copy_u8Port)
			{
			case DIO_u8PORTA: PORTA_REG|=(1U<<copy_u8Pin); break;
			case DIO_u8PORTB: PORTB_REG|=(1U<<copy_u8Pin); break;
			case DIO_u8PORTC: PORTC_REG|=(1U<<copy_u8Pin); break;
			case DIO_u8PORTD: PORTD_REG|=(1U<<copy_u8Pin); break;
			default:local_u8ErrorState=NOK;break; /*Invalid Port*/
			}
		}
		else
		{
			local_u8ErrorState=NOK;  /*Invalid State*/
		}
	}
	else
	{
		local_u8ErrorState=NOK; /*Invalid PinNumber*/
	}

	return local_u8ErrorState;
}

uint8t DIO_u8SetPortDirection(uint8t copy_u8Port,uint8t copy_u8Direction)
{
	uint8t local_u8ErrorState=OK;
	switch(copy_u8Port)
	{
	case DIO_u8PORTA:DDRA_REG=copy_u8Direction;break;
	case DIO_u8PORTB:DDRB_REG=copy_u8Direction;break;
	case DIO_u8PORTC:DDRC_REG=copy_u8Direction;break;
	case DIO_u8PORTD:DDRD_REG=copy_u8Direction;break;
	default:local_u8ErrorState=NOK;/*Invalid Port*/

	}
	return local_u8ErrorState;
}


uint8t DIO_u8SetPortValue(uint8t copy_u8Port,uint8t copy_u8Value)
{
	uint8t local_u8ErrorState=OK;
	switch(copy_u8Port)
	{
	case DIO_u8PORTA:PORTA_REG=copy_u8Value;break;
	case DIO_u8PORTB:PORTB_REG=copy_u8Value;break;
	case DIO_u8PORTC:PORTC_REG=copy_u8Value;break;
	case DIO_u8PORTD:PORTD_REG=copy_u8Value;break;
	default:local_u8ErrorState=NOK;/*Invalid Port*/

	}
	return local_u8ErrorState;
}


uint8t DIO_ReadPinValue(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t* copy_pu8Value)
{
	uint8t local_u8ErrorState=OK;
	if(copy_pu8Value ==NULL)
	{
		local_u8ErrorState=NULLPTR;
	}

	else
	{
		 if(copy_u8Pin>DIO_u8PIN7)
			{
				local_u8ErrorState=NOK;/*Invalid PinNumber*/
			}
		 else
		 {
				switch(copy_u8Port)
				{
				case DIO_u8PORTA:*copy_pu8Value=(PINA_REG>>copy_u8Pin)&1u;break;
				case DIO_u8PORTB:*copy_pu8Value=(PINB_REG>>copy_u8Pin)&1u;break;
				case DIO_u8PORTC:*copy_pu8Value=(PINC_REG>>copy_u8Pin)&1u;break;
				case DIO_u8PORTD:*copy_pu8Value=(PIND_REG>>copy_u8Pin)&1u;break;
				default:local_u8ErrorState=NOK;/*Invalid Port*/

				}
		 }
	}
		return local_u8ErrorState;
}


uint8t DIO_u8ReadPinValue(uint8t copy_u8Port,uint8t copy_u8Pin,uint8t* copy_pu8Value)
{
	uint8t local_u8ErrorState=OK;
	if(copy_pu8Value==NULL)
	{
		local_u8ErrorState=NULLPTR;
	}

	else
	{
		if(copy_u8Pin <=DIO_u8PIN7)
		{

			switch (copy_u8Port)
			{
			    case DIO_u8PORTA:
			        *copy_pu8Value = (PINA_REG >> copy_u8Pin) & 1U;
			        break;

			    case DIO_u8PORTB:
			        *copy_pu8Value = (PINB_REG >> copy_u8Pin) & 1U;
			        break;

			    case DIO_u8PORTC:
			        *copy_pu8Value = (PINC_REG >> copy_u8Pin) & 1U;
			        break;

			    case DIO_u8PORTD:
			        *copy_pu8Value = (PIND_REG >> copy_u8Pin) & 1U;
			        break;

			    default:
			        local_u8ErrorState = NOK;
			        break;
			}

		}

		else
		{
			local_u8ErrorState=NOK; /*Invalid PinNumber*/
		}
	}




	return local_u8ErrorState;
}


uint8t DIO_u8TogglePinValue(uint8t copy_u8Port,uint8t copy_u8Pin)
{
	uint8t local_u8ErrorState=OK;
	if(copy_u8Pin <=DIO_u8PIN7)
	{

			switch(copy_u8Port)
			{
			case DIO_u8PORTA: PORTA_REG^=(1U<<copy_u8Pin); break;
			case DIO_u8PORTB: PORTB_REG^=(1U<<copy_u8Pin); break;
			case DIO_u8PORTC: PORTC_REG^=(1U<<copy_u8Pin); break;
			case DIO_u8PORTD: PORTD_REG^=(1U<<copy_u8Pin); break;
			default:local_u8ErrorState=NOK;break; /*Invalid Port*/
			}
	}

	else
	{
		local_u8ErrorState=NOK; /*Invalid PinNumber*/
	}

	return local_u8ErrorState;
}









