#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "LED_Interface.h"
#include "SWITCH_Interface.h"
#include "7_Segment_Interface.h"

#define RED_LED_PORT    PORTB_ID
#define RED_LED_PIN     PIN0

#define YELLOW_LED_PORT PORTB_ID
#define YELLOW_LED_PIN  PIN1

#define GREEN_LED_PORT  PORTB_ID
#define GREEN_LED_PIN   PIN2

#define BLUE_LED_PORT   PORTB_ID
#define BLUE_LED_PIN    PIN3

#define SWITCH_PORT     PORTD_ID
#define SWITCH_PIN      PIN0

int main(void)
{
	// Set-up
	HAL_7SEGMENT_INIT();
	LED_voidInit(RED_LED_PORT, RED_LED_PIN);
	LED_voidInit(YELLOW_LED_PORT, YELLOW_LED_PIN);
	LED_voidInit(GREEN_LED_PORT, GREEN_LED_PIN);
	LED_voidInit(BLUE_LED_PORT, BLUE_LED_PIN); 
	SWITCH_voidInit(SWITCH_PORT, SWITCH_PIN);

	s8 count = 9;
	u8 night_mode = 0;

	while (1)
	{
		night_mode = SWITCH_u8GetState(SWITCH_PORT, SWITCH_PIN);

		HAL_7SEGMENT_WRITE(count);

		if (night_mode == 0)
		{
			LED_voidTurnOff(BLUE_LED_PORT, BLUE_LED_PIN);

			if (count >= 7)
			{
				LED_voidTurnOn(RED_LED_PORT, RED_LED_PIN);
				LED_voidTurnOff(YELLOW_LED_PORT, YELLOW_LED_PIN);
				LED_voidTurnOff(GREEN_LED_PORT, GREEN_LED_PIN);
			}
			else if (count >= 4)
			{
				LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);
				LED_voidTurnOn(YELLOW_LED_PORT, YELLOW_LED_PIN);
				LED_voidTurnOff(GREEN_LED_PORT, GREEN_LED_PIN);
			}
			else
			{
				LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);
				LED_voidTurnOff(YELLOW_LED_PORT, YELLOW_LED_PIN);
				LED_voidTurnOn(GREEN_LED_PORT, GREEN_LED_PIN);
			}
		}
		else if (night_mode == 1) 
		{
			LED_voidTurnOn(BLUE_LED_PORT, BLUE_LED_PIN);

			if (count >= 8)
			{
				LED_voidTurnOn(RED_LED_PORT, RED_LED_PIN);
				LED_voidTurnOff(YELLOW_LED_PORT, YELLOW_LED_PIN);
				LED_voidTurnOff(GREEN_LED_PORT, GREEN_LED_PIN);
			}
			else if (count >= 6)
			{
				LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);
				LED_voidTurnOn(YELLOW_LED_PORT, YELLOW_LED_PIN);
				LED_voidTurnOff(GREEN_LED_PORT, GREEN_LED_PIN);
			}
			else
			{
				LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);
				LED_voidTurnOff(YELLOW_LED_PORT, YELLOW_LED_PIN);
				LED_voidTurnOn(GREEN_LED_PORT, GREEN_LED_PIN);
			}
		}

		for (u16 i = 0; i < 100; i++)
		{
			_delay_ms(10);
			night_mode = SWITCH_u8GetState(SWITCH_PORT, SWITCH_PIN);
		}

		count--;
		if (count < 0)
		{
			count = 9;
		}
	}
}