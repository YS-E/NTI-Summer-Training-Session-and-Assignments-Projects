#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "LED_Interface.h"
#include "ADC_Interface.h"
#include "EXT_Interface.h"
#include "GIE_Interface.h"

#define LDR_ADC            ADC_CHANNEL0
#define NIGHT_LED_PORT     PORTB_ID
#define NIGHT_LED_PIN      PIN0

#define GREEN_LED_PORT     PORTB_ID
#define GREEN_LED_PIN      PIN1

#define RED_LED_PORT       PORTB_ID
#define RED_LED_PIN        PIN2

#define FIRE_PORT          PORTD_ID
#define FIRE_PIN           PIN2

#define DARK_LEVEL         2500UL

//volatile u8 fire_flag = 0;

void Fire_Sensor(void)
{
	LED_voidTurnOff(GREEN_LED_PORT, GREEN_LED_PIN);
	LED_voidTurnOn(RED_LED_PORT, RED_LED_PIN);
	
	while( DIO_voidGetBitValue(FIRE_PORT,FIRE_PIN) == 1);
	
	LED_voidTurnOn(GREEN_LED_PORT, GREEN_LED_PIN);
	LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);
}

int main(void)
{
	DIO_voidSetPinDirection(PORTA_ID, PIN0, PIN_INPUT);
	DIO_voidSetPinDirection(FIRE_PORT, FIRE_PIN, PIN_INPUT);

	LED_voidInit(NIGHT_LED_PORT, NIGHT_LED_PIN);
	LED_voidInit(GREEN_LED_PORT, GREEN_LED_PIN);
	LED_voidInit(RED_LED_PORT, RED_LED_PIN);

	ADC_INIT();
	ADC_CHANNEL_SELECT(LDR_ADC);

	EXT_voidSetCallBack(Fire_Sensor, EXT0);
	EXT_voidInit(EXT0, RISING_EDGE);
	GIE_Enable();

	LED_voidTurnOn(GREEN_LED_PORT, GREEN_LED_PIN);
	LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);

	u32 ldr_adc = 0;
	u16 ldr_voltage_mv = 0;
	u8 fire_pin_state = PIN_LOW;

	while (1)
	{
		ldr_adc = ADC_Read_value();
		ldr_voltage_mv = (u16)(((u32)ldr_adc * 5000UL) / 1024UL);

		if (ldr_voltage_mv < DARK_LEVEL)
		{
			LED_voidTurnOn(NIGHT_LED_PORT, NIGHT_LED_PIN);
		}
		else
		{
			LED_voidTurnOff(NIGHT_LED_PORT, NIGHT_LED_PIN);
		}

// 		if (fire_flag == 1)
// 		{
// 			fire_pin_state = DIO_voidGetBitValue(FIRE_PORT, FIRE_PIN);
// 			if (fire_pin_state == PIN_LOW)
// 			{
// 				LED_voidTurnOff(RED_LED_PORT, RED_LED_PIN);
// 				LED_voidTurnOn(GREEN_LED_PORT, GREEN_LED_PIN);
// 				fire_flag = 0;
// 			}
// 		}

		_delay_ms(10);
	}
}