#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define DDRA_REG  *((volatile u8*)0x3A)
#define PORTA_REG *((volatile u8*)0x3B)

#define DDRD_REG  *((volatile u8*)0x31)
#define PORTD_REG *((volatile u8*)0x32)
#define PIND_REG  *((volatile u8*)0x30)

int main(void)
{
	SET_BIT(DDRA_REG, 0);
	SET_BIT(DDRA_REG, 6);

	CLR_BIT(DDRD_REG, 0);
	CLR_BIT(DDRD_REG, 1);
	CLR_BIT(DDRD_REG, 2);


	CLR_BIT(PORTD_REG, 0);
	CLR_BIT(PORTD_REG, 1);
	CLR_BIT(PORTD_REG, 2);
	
	u8 led_state = 0;

	while (1)
	{
		u8 S1 = GET_BIT(PIND_REG, 1);
		u8 S2 = GET_BIT(PIND_REG, 2);
		
		if (S1 && S2)
		{
			SET_BIT(PORTA_REG, 6);
		}
		else
		{
			CLR_BIT(PORTA_REG, 6);
		}
	}

	return 0;
}