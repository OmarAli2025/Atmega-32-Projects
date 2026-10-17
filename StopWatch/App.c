/*
 * App.c
 *
 *  Created on: Oct 17, 2026
 *      Author: hp
 */

#include "StdLib.h"
# include "ErrorStates.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Port_interface.h"
#include "Keypad_interface.h"
#include "CLD_interface.h"
# include "util/delay.h"

# define u8MSBHOURCOLUMN 0
# define u8LSBHOURCOLUMN 1

# define u8MSBMINUTECOLUMN 3
# define u8LSBMINUTECOLUMN  4

# define u8MSBSECONDCOLUMN 6
# define u8LSBSECONDCOLUMN  7

# define u8ROWNUM  0


void  main(void)
{
	PORT_voidInit();
	CLCD_voidInit();

	uint8t local_u8KeyPressed=255;
	uint8t local_u8hourMSB=0,local_u8hourLSB=0;
	uint8t local_u8minuteMSB=0,local_u8minuteLSB=0;
	uint8t local_u8secondMSB=0,local_u8secondLSB=0;
	sint8t local_s8ColPos=0;
	uint8t local_u8flag=0;

	CLCD_voidDisplayNumber(local_u8hourMSB);
	CLCD_voidDisplayNumber(local_u8hourLSB);
	CLCD_voidSendData(':');
	CLCD_voidDisplayNumber(local_u8minuteMSB);
	CLCD_voidDisplayNumber(local_u8minuteLSB);
	CLCD_voidSendData(':');
	CLCD_voidDisplayNumber(local_u8secondMSB);
	CLCD_voidDisplayNumber(local_u8secondLSB);

	/*Hamoksa*/
	uint8t local_u8arrBody[8] =
	{
			0b10101,
			0b01110,
			0b00100,
			0b00100,
			0b00100,
			0b01010,
			0b10001,
			0b00000
	};

	uint8t local_u8arrFace[8]=
	{
			0b11111,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b10001,
			0b11111,
			0b0

	};



	CLCD_u8GoToxyPos(local_s8ColPos,u8ROWNUM);

	while(1)
	{

		do
		{

			KPD_u8GetPressedKey(&local_u8KeyPressed);

		}while(local_u8KeyPressed==255);

		if(local_u8KeyPressed == 'S')
		{

			while(local_u8hourMSB 	    != 0 ||
						local_u8hourLSB   	!= 0 ||
						local_u8minuteMSB != 0 ||
						local_u8minuteLSB 	!= 0 ||
						local_u8secondMSB != 0 ||
						local_u8secondLSB 	!= 0)
			{
				KPD_u8GetPressedKey(&local_u8KeyPressed);

				if(local_u8KeyPressed=='C')
				{
					local_u8flag=0;
					break;
				}
				_delay_ms(1000);

				if(local_u8secondLSB > 0)
				{
					local_u8secondLSB--;
				}
				else
				{
					local_u8secondLSB = 9;

					if(local_u8secondMSB > 0)
					{
						local_u8secondMSB--;
					}
					else
					{
						local_u8secondMSB = 5;

						if(local_u8minuteLSB > 0)
						{
							local_u8minuteLSB--;
						}
						else
						{
							local_u8minuteLSB = 9;

							if(local_u8minuteMSB > 0)
							{
								local_u8minuteMSB--;
							}
							else
							{
								local_u8minuteMSB = 5;

								if(local_u8hourLSB > 0)
								{
									local_u8hourLSB--;
								}
								else
								{
									local_u8hourLSB = 9;

									if(local_u8hourMSB > 0)
									{
										local_u8hourMSB--;
									}
									else
									{
										/* Time has reached 00:00:00 */

										local_u8hourLSB = 0;
										local_u8minuteMSB = 0;
										local_u8minuteLSB = 0;
										local_u8secondMSB = 0;
										local_u8secondLSB = 0;
									}
								}
							}
						}
					}
				}

				/* Update hours */
				CLCD_u8GoToxyPos(u8MSBHOURCOLUMN, 0);
				CLCD_voidDisplayNumber(local_u8hourMSB);

				CLCD_u8GoToxyPos(u8LSBHOURCOLUMN, 0);
				CLCD_voidDisplayNumber(local_u8hourLSB);

				/* Update minutes */
				CLCD_u8GoToxyPos(u8MSBMINUTECOLUMN, 0);
				CLCD_voidDisplayNumber(local_u8minuteMSB);

				CLCD_u8GoToxyPos(u8LSBMINUTECOLUMN, 0);
				CLCD_voidDisplayNumber(local_u8minuteLSB);

				/* Update seconds */
				CLCD_u8GoToxyPos(u8MSBSECONDCOLUMN, 0);
				CLCD_voidDisplayNumber(local_u8secondMSB);

				CLCD_u8GoToxyPos(u8LSBSECONDCOLUMN, 0);
				CLCD_voidDisplayNumber(local_u8secondLSB);
			}

			if(local_u8hourMSB   == 0 &&
					local_u8hourLSB   == 0 &&
					local_u8minuteMSB == 0 &&
					local_u8minuteLSB == 0 &&
					local_u8secondMSB == 0 &&
					local_u8secondLSB == 0)
			{
				local_u8flag = 1;
			}
		}

		if(local_u8flag==1)
		{
			CLCD_u8GoToxyPos(0,0);
			CLCD_u8SendString("Time Finish");
			CLCD_u8SendSpecialCharacter(1,local_u8arrFace,15,0);
			CLCD_u8SendSpecialCharacter(2,local_u8arrBody,15,1);
			while(1)
			{
				DIO_u8TogglePinValue(DIO_u8PORTA,DIO_u8PIN7);
				_delay_ms(900);
				KPD_u8GetPressedKey(&local_u8KeyPressed);

				if((local_u8KeyPressed=='C'))
				{
					CLCD_voidClearDisplay();
					local_u8flag=0;
					DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8LOW);
					break;
				}
			}
		}
		else if(local_u8KeyPressed=='C')
		{
			local_s8ColPos=0;
			CLCD_u8GoToxyPos(local_s8ColPos,u8ROWNUM);
			CLCD_voidDisplayNumber(0);
			CLCD_voidDisplayNumber(0);
			CLCD_voidSendData(':');
			CLCD_voidDisplayNumber(0);
			CLCD_voidDisplayNumber(0);
			CLCD_voidSendData(':');
			CLCD_voidDisplayNumber(0);
			CLCD_voidDisplayNumber(0);
			local_s8ColPos=0;
			local_u8hourMSB=0,local_u8hourLSB=0;
			local_u8minuteMSB=0,local_u8minuteLSB=0;
			local_u8secondMSB=0,local_u8secondLSB=0;
			CLCD_u8GoToxyPos(local_s8ColPos,u8ROWNUM);

		}
		else
		{
			if(local_u8KeyPressed=='R')
			{
				if(local_s8ColPos==7)
				{
					local_s8ColPos=-1;
				}
				else if(local_s8ColPos==1|| local_s8ColPos==4)
				{
					local_s8ColPos++;
				}
				local_s8ColPos++;
			}

			else if(local_u8KeyPressed=='L')
			{
				if(local_s8ColPos==0)
				{
					local_s8ColPos=8;
				}
				else if(local_s8ColPos==6|| local_s8ColPos==3)
				{
					local_s8ColPos--;

				}
				local_s8ColPos--;
			}
			else
			{
				switch(local_s8ColPos)
				{
				case 0:

					if(local_u8KeyPressed>2)
					{
						local_u8KeyPressed=2;
					}
					local_u8hourMSB=local_u8KeyPressed;break;

				case 1:
					if(local_u8KeyPressed>3 &&local_u8hourMSB>=2)
					{
						local_u8KeyPressed=3;
					}
					local_u8hourLSB=local_u8KeyPressed;break;

				case 3:

					if(local_u8KeyPressed>5)
					{
						local_u8KeyPressed=5;
					}
					local_u8minuteMSB=local_u8KeyPressed;break;

				case 4:local_u8minuteLSB=local_u8KeyPressed;break;

				case 6:

					if(local_u8KeyPressed>5)
					{
						local_u8KeyPressed=5;
					}
					local_u8secondMSB=local_u8KeyPressed;break;

				case 7:local_u8secondLSB=local_u8KeyPressed;break;

				default:break;
				}

				CLCD_u8GoToxyPos(local_s8ColPos,u8ROWNUM);
				CLCD_voidDisplayNumber(local_u8KeyPressed);
			}
		}

	}


}
