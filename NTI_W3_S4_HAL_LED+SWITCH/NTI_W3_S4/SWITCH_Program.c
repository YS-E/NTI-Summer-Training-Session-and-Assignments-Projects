#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "SWITCH_Interface.h"

void SWITCH_voidInit(u8 copy_u8Port, u8 copy_u8Pin)
{
	DIO_voidSetPinDirection(copy_u8Port, copy_u8Pin, PIN_INPUT);
}

u8 SWITCH_u8GetState(u8 copy_u8Port, u8 copy_u8Pin)
{
	u8 Local_u8State = 0;

	if (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1)
	{
		_delay_ms(30); 
		if (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1)
		{
			Local_u8State = 1;
			while (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1);
		}
	}

	return Local_u8State;
}

u8 SWITCH_u8GetToggleState(u8 copy_u8Port, u8 copy_u8Pin)
{
	static u8 Local_u8ToggleState = 0;

	if (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1)
	{
		_delay_ms(30); 
		if (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1)
		{
			Local_u8ToggleState ^= 1;
			while (DIO_voidGetBitValue(copy_u8Port, copy_u8Pin) == 1);
		}
	}

	return Local_u8ToggleState;
}