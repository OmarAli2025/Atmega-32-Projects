/*
 * Port_prog.c
 *
 *  Created on: Oct 14, 2026
 *      Author: hp
 */
#include "StdLib.h"
#include "ErrorStates.h"
#include "BIT_MATH.h"

#include "Port_interface.h"
# include "Port_reg.h"
#include "Port_pvt.h"
#include "Port_cfg.h"

void PORT_voidInit()
{
	DDRA_REG=PORTADIR;
	DDRB_REG=PORTBDIR;
	DDRC_REG=PORTCDIR;
	DDRD_REG=PORTDDIR;

	PORTA_REG=PORTAVAL;
	PORTB_REG=PORTBVAL;
	PORTC_REG=PORTCVAL;
	PORTD_REG=PORTDVAL;



}

