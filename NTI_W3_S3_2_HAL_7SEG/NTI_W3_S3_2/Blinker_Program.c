#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "Blinker_Config.h"
#include "Blinker_Interface.h"
#include "Blinker_Private.h"

static u16 speed_presets[SET_NUM] = SET_ARR;
static s8 current_index = START_DEFUALT;

void HAL_BLINKER_INIT(void)
{
	DIO_voidSetPinDirection(LED_PORT, LED_PIN, PIN_OUTPUT);
	
	DIO_voidSetPinDirection(FASTER_PORT, FASTER_PIN, PIN_INPUT);
	DIO_voidSetPinDirection(SLOWER_PORT, SLOWER_PIN, PIN_INPUT);
}

static void Blinker_voidIncreaseSpeed(void)
{
	if (current_index < SET_MAX)
	{
		current_index++;
	}
}

static void Blinker_voidDecreaseSpeed(void)
{
	if (current_index > SET_MIN)
	{
		current_index--;
	}
}

void HAL_BLINKER_UPDATE(void)
{
	u8 faster_btn = DIO_voidGetBitValue(FASTER_PORT, FASTER_PIN);
	u8 slower_btn = DIO_voidGetBitValue(SLOWER_PORT, SLOWER_PIN);

	if (faster_btn == 1)
	{
		_delay_ms(30);
		if (DIO_voidGetBitValue(FASTER_PORT, FASTER_PIN) == 1)
		{
			Blinker_voidIncreaseSpeed();
			while (DIO_voidGetBitValue(FASTER_PORT, FASTER_PIN) == 1);
		}
	}
	else if (slower_btn == 1)
	{
		_delay_ms(30);
		if (DIO_voidGetBitValue(SLOWER_PORT, SLOWER_PIN) == 1)
		{
			Blinker_voidDecreaseSpeed();
			while (DIO_voidGetBitValue(SLOWER_PORT, SLOWER_PIN) == 1);
		}
	}

	u16 current_delay = speed_presets[current_index];

	if (current_delay == 3000)				//off value
	{
		DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_LOW);
		_delay_ms(10);
	}
	else if (current_delay == 0)
	{
		DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_HIGH);
		_delay_ms(10);
	}
	else
	{
		DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_HIGH);
		for (u16 elapsed = 0; elapsed < current_delay; elapsed += 10)
		{
			_delay_ms(10);
			if (DIO_voidGetBitValue(FASTER_PORT, FASTER_PIN) == 1 ||
			DIO_voidGetBitValue(SLOWER_PORT, SLOWER_PIN) == 1)
			{
				break;
			}
		}

		DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_LOW);
		for (u16 elapsed = 0; elapsed < current_delay; elapsed += 10)
		{
			_delay_ms(10);
			if (DIO_voidGetBitValue(FASTER_PORT, FASTER_PIN) == 1 ||
			DIO_voidGetBitValue(SLOWER_PORT, SLOWER_PIN) == 1)
			{
				break;
			}
		}
	}
}