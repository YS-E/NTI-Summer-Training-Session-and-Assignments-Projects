#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "LED_Interface.h"
#include "GIE_Interface.h"
#include "EXT_Interface.h"


//LED Pins
#define MAIN_LED_PORT   PORTA_ID
#define MAIN_LED_PIN    PIN3

#define INT0_LED_PORT   PORTA_ID 
#define INT0_LED_PIN    PIN0

#define INT1_LED_PORT   PORTA_ID  
#define INT1_LED_PIN    PIN1

#define INT2_LED_PORT   PORTA_ID  
#define INT2_LED_PIN    PIN2

// INT Pins
#define INT0_PIN_PORT   PORTD_ID
#define INT0_PIN_NUM    PIN2

#define INT1_PIN_PORT   PORTD_ID
#define INT1_PIN_NUM    PIN3

#define INT2_PIN_PORT   PORTB_ID
#define INT2_PIN_NUM    PIN2



void INT0_Func(void)
{
	LED_voidTurnOff(MAIN_LED_PORT, MAIN_LED_PIN);

	LED_voidTurnOn(INT0_LED_PORT, INT0_LED_PIN);
	_delay_ms(1000);
	LED_voidTurnOff(INT0_LED_PORT, INT0_LED_PIN);
}

void INT1_Func(void)
{
	GIE_Enable();

	LED_voidTurnOff(MAIN_LED_PORT, MAIN_LED_PIN);

	LED_voidTurnOn(INT1_LED_PORT, INT1_LED_PIN);
	_delay_ms(1000);
	LED_voidTurnOff(INT1_LED_PORT, INT1_LED_PIN);
}

void INT2_Func(void)
{
	GIE_Enable();

	LED_voidTurnOff(MAIN_LED_PORT, MAIN_LED_PIN);

	LED_voidTurnOn(INT2_LED_PORT, INT2_LED_PIN);
	_delay_ms(1000);
	LED_voidTurnOff(INT2_LED_PORT, INT2_LED_PIN);
}



int main(void)
{
	LED_voidInit(MAIN_LED_PORT, MAIN_LED_PIN);
	LED_voidInit(INT0_LED_PORT, INT0_LED_PIN);
	LED_voidInit(INT1_LED_PORT, INT1_LED_PIN);
	LED_voidInit(INT2_LED_PORT, INT2_LED_PIN);

	EXT_voidSetCallBack(INT0_Func, EXT0);
	EXT_voidSetCallBack(INT1_Func,  EXT1);
	EXT_voidSetCallBack(INT2_Func,  EXT2);

	EXT_voidInit(EXT0, RISING_EDGE);
	EXT_voidInit(EXT1, RISING_EDGE);
	EXT_voidInit(EXT2, RISING_EDGE);

	GIE_Enable();

	while (1)
	{
		LED_voidTurnOn(MAIN_LED_PORT, MAIN_LED_PIN);
		_delay_ms(200);

		LED_voidTurnOff(MAIN_LED_PORT, MAIN_LED_PIN);
		_delay_ms(200);
	}
}