#define F_CPU 8000000UL
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Config.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

int main(void)
{
	u8 num_arr[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

	DIO_voidSetPortDirection(PORTA_ID, ALL_PORT_OUTPUT);
	DIO_voidSetPortDirection(PORTD_ID, ALL_PORT_INPUT);

	s8 count = 0;

	DIO_voidSetPortValue(PORTA_ID, num_arr[count]);

	while (1)
	{
		if (DIO_voidGetBitValue(PORTD_ID, PIN0) == 1 || DIO_voidGetBitValue(PORTD_ID, PIN1) == 1)
		{
			_delay_ms(30); 

			if (DIO_voidGetBitValue(PORTD_ID, PIN0) == 1)
			{
				count++;
				if (count > 9)
					count = 0;
			}
			else if (DIO_voidGetBitValue(PORTD_ID, PIN1) == 1)
			{
				count--;
				if (count < 0)
					count = 9;
			}

			DIO_voidSetPortValue(PORTA_ID, num_arr[count]);

			while (DIO_voidGetBitValue(PORTD_ID, PIN0) == 1 || DIO_voidGetBitValue(PORTD_ID, PIN1) == 1);
		}
	}
}