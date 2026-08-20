#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "LCD_Interface.h"
#include "ADC_Interface.h"

#define MOTOR_PORT    PORTB_ID
#define MOTOR_PIN     PIN0

#define LED_PORT    PORTB_ID
#define LED_PIN     PIN1

u16 adc_val = 0;
u16 voltage_mv = 0;
u16 temperature_c = 0;

int main(void)
{
	DIO_voidSetPinDirection(PORTA_ID, PIN1, PIN_INPUT);
	DIO_voidSetPinDirection(MOTOR_PORT, MOTOR_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(LED_PORT, LED_PIN, PIN_OUTPUT);

	ADC_INIT();
	ADC_CHANNEL_SELECT(ADC_CHANNEL1);

	LCD_voidInit();

	while (1)
	{
		adc_val = ADC_Read_value();

		voltage_mv = ((u32)adc_val * 5000UL) / 1024UL;

		temperature_c = (u16)(voltage_mv / 10UL);

		if (temperature_c > 30)
		{
			DIO_voidSetPinValue(MOTOR_PORT, MOTOR_PIN, PIN_HIGH);
			DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_HIGH);

			Lcd_Goto_Row_Column(0, 0);
			Lcd_DisplayStr((u8*)"Temp: ");
			Lcd_Displaynum(temperature_c);
			Lcd_DisplayStr((u8*)" C    ");

			Lcd_Goto_Row_Column(1, 0);
			Lcd_DisplayStr((u8*)" WARNING !!!!!!!");
		}
		else
		{
			DIO_voidSetPinValue(MOTOR_PORT, MOTOR_PIN, PIN_LOW);
			DIO_voidSetPinValue(LED_PORT, LED_PIN, PIN_LOW);


			Lcd_Goto_Row_Column(0, 0);
			Lcd_DisplayStr((u8*)"Temp: ");
			Lcd_Displaynum(temperature_c);
			Lcd_DisplayStr((u8*)" C    ");

			Lcd_Goto_Row_Column(1, 0);
			Lcd_DisplayStr((u8*)"Volt: ");
			Lcd_Displaynum((u16)voltage_mv);
			Lcd_DisplayStr((u8*)" mV      ");
		}

		_delay_ms(100);
	}
}