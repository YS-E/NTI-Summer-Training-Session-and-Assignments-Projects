#define F_CPU 8000000UL
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Config.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

int main(void)
{
	DIO_voidSetPortDirection(PORTA_ID, ALL_PORT_OUTPUT);

	DIO_voidSetPinDirection(PORTD_ID, PIN0, PIN_INPUT);
	DIO_voidSetPinDirection(PORTD_ID, PIN1, PIN_INPUT);

	u16 blink_delay_ms = 1000;

	while (1)
	{
		u8 s0 = DIO_voidGetBitValue(PORTD_ID, PIN0);
		u8 s1 = DIO_voidGetBitValue(PORTD_ID, PIN1);

		if (blink_delay_ms == 0)
		{
			DIO_voidSetPortValue(PORTA_ID, ALL_PORT_HIGH);
			_delay_ms(10);
			
			if (s0 == 0 && s1 == 1) blink_delay_ms = 150;
		}
		else if (blink_delay_ms > 3000)
		{
			DIO_voidSetPortValue(PORTA_ID, ALL_PORT_LOW);
			_delay_ms(10);
			
			if (s0 == 1 && s1 == 0) blink_delay_ms = 3000;
		}
		else
		{
			DIO_voidSetPortValue(PORTA_ID, ALL_PORT_HIGH);
			for (u16 elapsed = 0; elapsed < blink_delay_ms; elapsed += 10)
			{
				_delay_ms(10);
				
				s0 = DIO_voidGetBitValue(PORTD_ID, PIN0);
				s1 = DIO_voidGetBitValue(PORTD_ID, PIN1);

				if (s0 == 1 && s1 == 0)
				{
					if (blink_delay_ms > 15) blink_delay_ms -= 15; // Speed up faster
					else { blink_delay_ms = 0; break; }
				}
				else if (s0 == 0 && s1 == 1)
				{
					if (blink_delay_ms < 3000) blink_delay_ms += 15; // Slow down faster
					else { blink_delay_ms = 3005; break; }
				}
			}

			DIO_voidSetPortValue(PORTA_ID, ALL_PORT_LOW);
			for (u16 elapsed = 0; elapsed < blink_delay_ms; elapsed += 10)
			{
				_delay_ms(10);
				
				s0 = DIO_voidGetBitValue(PORTD_ID, PIN0);
				s1 = DIO_voidGetBitValue(PORTD_ID, PIN1);

				if (s0 == 1 && s1 == 0)
				{
					if (blink_delay_ms > 15) blink_delay_ms -= 15; // Speed up faster
					else { blink_delay_ms = 0; break; }
				}
				else if (s0 == 0 && s1 == 1)
				{
					if (blink_delay_ms < 3000) blink_delay_ms += 15; // Slow down faster
					else { blink_delay_ms = 3005; break; }
				}
			}
		}
	}
}