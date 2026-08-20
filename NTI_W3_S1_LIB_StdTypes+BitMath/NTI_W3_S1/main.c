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
	CLR_BIT(DDRD_REG, 3);
	CLR_BIT(DDRD_REG, 4);
	CLR_BIT(DDRD_REG, 5);


	CLR_BIT(PORTD_REG, 0);
	CLR_BIT(PORTD_REG, 1);
	CLR_BIT(PORTD_REG, 2);
	CLR_BIT(PORTD_REG, 3);
	CLR_BIT(PORTD_REG, 4);
	CLR_BIT(PORTD_REG, 5);
	
	u8 led_state = 0;

	while (1)
	{
		if (GET_BIT(PIND_REG, 0) == 1)
		{
			_delay_ms(30);

			if (GET_BIT(PIND_REG, 0) == 1)
			{
				if (led_state == 0)
				{
					led_state = 1;
					SET_BIT(PORTA_REG, 0);
				}
				else
				{
					led_state = 0;
					CLR_BIT(PORTA_REG, 0);
				}

				while (GET_BIT(PIND_REG, 0) == 1);
			}
		}
		
		u8 S1 = GET_BIT(PIND_REG, 1);
		u8 S2 = GET_BIT(PIND_REG, 2);
		
		if (S1 && S2)
		{
			SET_BIT(PORTA_REG, 2);
		}
		else
		{
			CLR_BIT(PORTA_REG, 2);
		}
		
		
		u8 S3 = GET_BIT(PIND_REG, 3);
		u8 S4 = GET_BIT(PIND_REG, 4);
		
		if (S3 || S4)
		{
			SET_BIT(PORTA_REG, 4);
		}
		else
		{
			CLR_BIT(PORTA_REG, 4);
		}
		
		u8 S5 = GET_BIT(PIND_REG, 5);
		if (S5)
		{
			CLR_BIT(PORTA_REG, 6);
		}
		else
		{
			SET_BIT(PORTA_REG, 6);
		}
	}

	return 0;
}