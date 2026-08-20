#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "SWITCH_Interface.h"

static u8 state = 0; 

void SWITCH_voidInit(u8 copy_u8Port, u8 copy_u8Pin)
{
	DIO_voidSetPinDirection(copy_u8Port, copy_u8Pin, PIN_INPUT);
}

u8 SWITCH_u8GetState(u8 copy_u8Port, u8 copy_u8Pin)
{
	if (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1)
	{
		_delay_ms(30);
		if (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1)
		{
			state ^= 1;

			while (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1);
		}
	}
	return state;
}