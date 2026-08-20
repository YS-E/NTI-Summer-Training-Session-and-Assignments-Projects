#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "7_Segment_Interface.h"

int main(void)
{
	HAL_7SEGMENT_INIT();
	HAL_BLINKER_INIT();


	u8 numbers[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

	while (1)
	{
		/*
		for (u8 i = 0; i < 10; i++)
		{
			HAL_7SEGMENT_WRITE(numbers[i]);
			_delay_ms(500);
		}
		*/
		
		HAL_BLINKER_UPDATE();
	}
}