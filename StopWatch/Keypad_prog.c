/*
 * Keypad_prog.c
 *
 *  Created on: Oct 17, 2026
 *      Author: hp
 */

#include "StdLib.h"
# include "ErrorStates.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Keypad_interface.h"
#include "Keypad_cfg.h"
# include "Keypad_pvt.h"


uint8t KPD_u8GetPressedKey(uint8t * copu_pu8PressedKey)
{
	uint8t local_u8errorstate=OK;
	if(copu_pu8PressedKey==NULL)
	{
		local_u8errorstate=NULLPTR;

	}

	else
	{
		const uint8t local_au8Array[u8ROWNUM][u8COLUMNNUM]=KPD_au8Arr;
		uint8t local_u8counter,local_u8counter2;
		uint8t local_au8Columns[u8COLUMNNUM]={KPD_u8C0PIN,KPD_u8C1PIN,KPD_u8C2PIN,KPD_u8C3PIN};
		uint8t local_au8Rows[u8ROWNUM]={KPD_u8R0PIN,KPD_u8R1PIN,KPD_u8R2PIN,KPD_u8R3PIN};
		uint8t local_u8rowsreading;
		uint8t local_u8foundflag=0;



		for(local_u8counter=0;local_u8counter<u8COLUMNNUM;local_u8counter++)
		{
			local_u8errorstate=DIO_u8SetPinValue(KPD_u8COLUMNPORT,local_au8Columns[local_u8counter],DIO_u8LOW);

			if(local_u8errorstate==OK)
			{
				for(local_u8counter2=0;local_u8counter2<u8ROWNUM;local_u8counter2++)
				{
					local_u8errorstate=DIO_u8ReadPinValue(KPD_u8ROWPORT,local_au8Rows[local_u8counter2],&local_u8rowsreading);
					if(local_u8rowsreading==DIO_u8LOW)
					{
						*copu_pu8PressedKey=local_au8Array[local_u8counter2][local_u8counter];
						while(local_u8rowsreading==DIO_u8LOW)
						{
							local_u8errorstate=DIO_u8ReadPinValue(KPD_u8ROWPORT,local_au8Rows[local_u8counter2],&local_u8rowsreading);

						}

						local_u8foundflag=1;

						break;
					}
				}

			}

			local_u8errorstate=DIO_u8SetPinValue(KPD_u8COLUMNPORT,local_au8Columns[local_u8counter],DIO_u8HIGH);

			if(local_u8foundflag==1)
			{

				break;
			}
			else
			{

				*copu_pu8PressedKey=KPD_u8NOPRESSEDKEY;
			}
		}


	}

	return local_u8errorstate;
}
