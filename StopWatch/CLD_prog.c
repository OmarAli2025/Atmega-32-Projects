#include "StdLib.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLD_interface.h"
#include "CLDCD_pvt.h"
#include "CLD_cfg.h"
# include "ErrorStates.h"
#include "util/delay.h"

#if CLCD_u8BITMODE==u8_FOUR_BITMODE
static void voidSendHalfDataPort(uint8t copy_u8halfdata)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4,GET_BIT(copy_u8halfdata,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5,GET_BIT(copy_u8halfdata,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6,GET_BIT(copy_u8halfdata,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7,GET_BIT(copy_u8halfdata,3));
}
#endif
static void void_SetEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CNTRL_PORT,CLCD_u8E_PIN,DIO_u8HIGH);
	DIO_u8SetPinValue(CLCD_u8CNTRL_PORT,CLCD_u8E_PIN,DIO_u8LOW);
	_delay_ms(2);
}

void CLCD_voidSendCommand(uint8t copy_u8Com)
{
	/*Set RS_PIN to low  */
	DIO_u8SetPinValue(CLCD_u8CNTRL_PORT,CLCD_u8RS_PIN,DIO_u8LOW);

	/*Set RW_PIN to low  */
	DIO_u8SetPinValue(CLCD_u8CNTRL_PORT,CLCD_u8RW_PIN,DIO_u8LOW);

#if CLCD_u8BITMODE==u8EIGHT_BITMODE

	/*Send Command*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Com);

	/*Set Enable To High and Reset Low */
	void_SetEnablePulse();

#elif CLCD_u8BITMODE==u8_FOUR_BITMODE

	voidSendHalfDataPort(copy_u8Com>>4);

	/*Set Enable To High and Reset Low */
	void_SetEnablePulse();

	voidSendHalfDataPort(copy_u8Com);

	/*Set Enable To High and Reset Low */
	void_SetEnablePulse();

#else
#error CLCD_BITMODE Wrong Config

#endif

}

void CLCD_voidSendData(uint8t copy_u8Data)
{
	/*Set RS_PIN to high  */
	DIO_u8SetPinValue(CLCD_u8CNTRL_PORT,CLCD_u8RS_PIN,DIO_u8HIGH);

	/*Set RW_PIN to low  */
	DIO_u8SetPinValue(CLCD_u8CNTRL_PORT,CLCD_u8RW_PIN,DIO_u8LOW);

#if CLCD_u8BITMODE==u8EIGHT_BITMODE
	/*Send Data*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,copy_u8Data);

	/*Set Enable To High and Reset Low */
	void_SetEnablePulse();

#elif CLCD_u8BITMODE==u8_FOUR_BITMODE
	voidSendHalfDataPort(copy_u8Data>>4);
	void_SetEnablePulse();
	voidSendHalfDataPort(copy_u8Data);
	void_SetEnablePulse();

#else
#error CLCD_BITMODE Wrong Config

#endif

}



void CLCD_voidInit(void)
{
	/*Wait for more than 30ms after Power on*/
	_delay_ms(40);

#if CLCD_u8BITMODE==u8EIGHT_BITMODE

	/*Send Command Function Set*/
	CLCD_voidSendCommand(u8_FUNCTIONSET_COMM);	/*Wait for more than 39 us Inside Func Handled*/

	CLCD_voidSendCommand(u8_DISPLAYMODE_COMM);
	CLCD_voidSendCommand(u8_CLEARDISP_COMM);
	CLCD_voidSendCommand(u8_CLEARDISP_COMM);

#elif CLCD_u8BITMODE == u8_FOUR_BITMODE


	voidSendHalfDataPort(u8_FUCTIONSET4BIT_COMM); void_SetEnablePulse();
	voidSendHalfDataPort(u8_FUCTIONSET4BIT_COMM); void_SetEnablePulse();

	voidSendHalfDataPort(u8_FUCTIONSET2_4BIT_COMM);void_SetEnablePulse();

	CLCD_voidSendCommand(u8_DISPLAYMODE_COMM);
	CLCD_voidSendCommand(u8_CLEARDISP_COMM);
	CLCD_voidSendCommand(u8_CLEARDISP_COMM);

#endif


}

uint8t CLCD_u8SendString(const char * copy_pcharString)
{
	uint8t local_u8ErroState=OK;
	uint8t local_u8counter=0;


	if(copy_pcharString==NULL)
	{
		local_u8ErroState=NULLPTR;
	}
	else
	{
		while(copy_pcharString[local_u8counter] != '\0')
		{
			CLCD_voidSendData(copy_pcharString[local_u8counter]);
			local_u8counter++;
		}
	}
	return local_u8ErroState;
}



void CLCD_voidDisplayNumber(sint32t copy_s32Number)
{
	sint8t local_u8counter=0;

	if(copy_s32Number==0)
	{
		CLCD_voidSendData('0');
		return ;
	}

	else

	{
		if(copy_s32Number<0)
		{
			CLCD_voidSendData('-');
			copy_s32Number*=-1;
		}

		char local_charArr[10];
		while(copy_s32Number!=0)
		{
			local_charArr[local_u8counter]=copy_s32Number %10;
			copy_s32Number/=10;
			local_u8counter++;
		}

		for(sint8t local_u8iterator=local_u8counter-1;local_u8iterator>=0;local_u8iterator--)
		{
			CLCD_voidSendData(local_charArr[local_u8iterator]+'0');

		}
	}

}

uint8t CLCD_u8GoToxyPos(uint8t copy_u8x,uint8t copy_u8y) /*X is The Column Y is The Row*/
{
	uint8t local_u8ErrorState=OK;

	if((copy_u8x>=16U)  || (copy_u8y>1U) )
	{
		local_u8ErrorState=NOK;
	}
	else
	{
		if(copy_u8y==0)
		{
			/*Set bit 7 and send Address*/
			CLCD_voidSendCommand((1<<7U)|copy_u8x);

		}
		else if(copy_u8y==1)
		{
			/*Set bit 7 and send Address*/
			CLCD_voidSendCommand((1<<7U)|(copy_u8x+u8_DDRAMLINE2));
		}
	}
	return local_u8ErrorState;
}


uint8t CLCD_u8SendSpecialCharacter(uint8t copy_u8LocationnNum,uint8t * copy_pu8Symbol,uint8t copy_u8x,uint8t copy_u8y)
{
	uint8t local_u8ErrorState=OK;

	if(copy_pu8Symbol==NULL)
	{
		local_u8ErrorState=NULLPTR;
	}
	else if(copy_u8LocationnNum>7U)
	{
		local_u8ErrorState=NOK;

	}
	else
	{
		uint8t local_u8CGRAMAddress=(copy_u8LocationnNum*8)|(0b1<<6U);

		CLCD_voidSendCommand(local_u8CGRAMAddress);
		for(uint8t local_u8iterator=0;local_u8iterator<8;local_u8iterator++)
		{
			CLCD_voidSendData(copy_pu8Symbol[local_u8iterator]);
		}

		/*Go Back To DDRAM*/

		local_u8ErrorState=CLCD_u8GoToxyPos(copy_u8x,copy_u8y);

		if (local_u8ErrorState != OK)
		{
			local_u8ErrorState = NOK;
		}
		else
		{
			CLCD_voidSendData(copy_u8LocationnNum);
		}
	}

	return local_u8ErrorState;
}

void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCommand(1);

}
