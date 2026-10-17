#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BITNUM)     REG |=  (1U<<BITNUM)
#define CLR_BIT(REG,BITNUM)     REG &=  ~(1U<<BITNUM)
#define TOGGLE_BIT(REG,BITNUM)  REG ^=  (1U<<BITNUM) 
#define GET_BIT(REG,BITNUM)     (REG>>BITNUM)  &0b1U
# define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0) ( b7<<7)|\
																			(b6<<6)|\
																			(b5<<5)|\
																			(b4<<4)|\
																			(b3<<3)|\
																			(b2<<2)|\
																			(b1<<1)|\
																			(b0<<0)




#endif
