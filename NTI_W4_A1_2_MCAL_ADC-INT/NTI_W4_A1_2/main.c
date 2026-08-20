#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "EXT_Interface.h"
#include "GIE_Interface.h"
#include "LCD_Interface.h"
#include "LED_Interface.h"

/* Special Function IO Register Definition */
#define SFIOR_REG   *((volatile u8*)0x50)
#define ADTS0       5
#define ADTS1       6
#define ADTS2       7

/* ADCSRA Register Bits */
#define ADCSRA_REG  *((volatile u8*)0x26)
#define ADATE       5
#define ADIE        3

/* ADC Data Register (Combined Low + High) */
#define ADC_DATA    *((volatile u16*)0x24)

/* Pin Configurations */
#define ALARM_LED_PORT     PORTB_ID
#define ALARM_LED_PIN      PIN0
#define NORMAL_LED_PORT    PORTB_ID
#define NORMAL_LED_PIN     PIN1

volatile u16 g_lm35_raw = 0;
volatile u8  g_hazard_flag = 0;

/* ADC Conversion Complete ISR (Vector 16) defined directly in main */
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	g_lm35_raw = ADC_DATA;
	g_hazard_flag = 1;
}

int main(void)
{
	/* 1. Pin Configuration */
	DIO_voidSetPinDirection(PORTA_ID, PIN0, PIN_INPUT); /* LM35 Analog Input */
	DIO_voidSetPinDirection(PORTD_ID, PIN2, PIN_INPUT); /* Gas/Flame on INT0 */

	/* 2. LED Indicators */
	LED_voidInit(ALARM_LED_PORT, ALARM_LED_PIN);
	LED_voidInit(NORMAL_LED_PORT, NORMAL_LED_PIN);
	LED_voidTurnOn(NORMAL_LED_PORT, NORMAL_LED_PIN);
	LED_voidTurnOff(ALARM_LED_PORT, ALARM_LED_PIN);

	/* 3. LCD Setup */
	LCD_voidInit();


	/* 4. ADC & Auto-Trigger Setup */
	ADC_INIT();
	ADC_CHANNEL_SELECT(ADC_CHANNEL0);

	/* Set Auto-Trigger source to EXT0 (ADTS[2:0] = 010) */
	CLR_BIT(SFIOR_REG, ADTS2);
	SET_BIT(SFIOR_REG, ADTS1);
	CLR_BIT(SFIOR_REG, ADTS0);

	/* Enable Auto-Trigger and ADC Interrupt */
	SET_BIT(ADCSRA_REG, ADATE);
	SET_BIT(ADCSRA_REG, ADIE);

	/* 5. Enable External Interrupt 0 on Rising Edge & Global Interrupts */
	EXT_voidInit(EXT0, RISING_EDGE);
	EXT_voidSetCallBack(__vector_16, EXT0);
	GIE_Enable();

	u16 temp_celsius = 0;

	while (1)
	{
		if (g_hazard_flag == 1)
		{
			/* Convert Raw ADC to Temperature in Celsius */
			u16 voltage_mv = (u16)(((u32)g_lm35_raw * 5000UL) / 1024UL);
			temp_celsius = voltage_mv / 10;

			/* Visual Alert */
			LED_voidTurnOff(NORMAL_LED_PORT, NORMAL_LED_PIN);
			LED_voidTurnOn(ALARM_LED_PORT, ALARM_LED_PIN);

			/* LCD Status Update */
			Lcd_Goto_Row_Column(0, 0);
			Lcd_DisplayStr((u8*)"FIRE/GAS ALERT! ");
			Lcd_Goto_Row_Column(1, 0);
			Lcd_DisplayStr((u8*)"Temp: ");
			Lcd_Displaynum(temp_celsius);
			Lcd_DisplayStr((u8*)" C   ");

			g_hazard_flag = 0;
		}

		_delay_ms(100);
	}
}