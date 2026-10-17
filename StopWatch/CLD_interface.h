#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

/*Function Set mode*/


#define CLCD_u8N1LINE   	0U
#define CLCD_u8N2LINE   	1U

#define CLCD_u8FONT5X7  	0U
#define CLCD_u8FONT5X10 	1U

/*Display mode*/
# define CLCD_u8DON   		1U
# define CLCD_u8DOFF  		0U

# define CLCD_u8CON			1U
# define CLCD_u8COFF  		0U

# define CLCD_u8BON			1U
# define CLCD_u8BOFF			0U



void CLCD_voidInit(void);
void CLCD_voidSendCommand(uint8t copy_u8Com);
void CLCD_voidSendData(uint8t copy_u8Data);
void CLCD_voidDisplayNumber(sint32t copy_s32Number);
void CLCD_voidClearDisplay(void);

uint8t CLCD_u8SendString(const char * copy_pcharString);
uint8t CLCD_u8GoToxyPos(uint8t copy_u8x,uint8t copy_u8y);
uint8t CLCD_u8SendSpecialCharacter(uint8t copy_u8LocationnNum,uint8t * copy_pu8Symbol,uint8t copy_u8x,uint8t copy_u8y);







#endif
