#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "SWITCH_Interface.h"

#define UP_BTN_PORT    PORTD_ID
#define UP_BTN_PIN     PIN0

#define DOWN_BTN_PORT  PORTD_ID
#define DOWN_BTN_PIN   PIN1

int main(void)
{
	LCD_voidInit();
	SWITCH_voidInit(UP_BTN_PORT, UP_BTN_PIN);
	SWITCH_voidInit(DOWN_BTN_PORT, DOWN_BTN_PIN);
	u8 *message = "NTI HELLO";
	s16 counter = 0;
	u8 location = 0;
	Lcd_Goto_Row_Column(1, 0);
	Lcd_Displaynum(counter);

	while (1)
	{
		
		Lcd_Goto_Row_Column(0, 0);
		Lcd_DisplayStr((u8*)"                     ");
		Lcd_Goto_Row_Column(0, location);
		Lcd_DisplayStr((u8*)message);
		_delay_ms(100);
		
		if (SWITCH_u8GetState(UP_BTN_PORT, UP_BTN_PIN) == 1)
		{
			if (counter < 9)
			{
				counter++;
			}
			
			Lcd_Goto_Row_Column(1, 0);
			Lcd_Displaynum(counter);
		}

		if (SWITCH_u8GetState(DOWN_BTN_PORT, DOWN_BTN_PIN) == 1)
		{
			if (counter > 0)
			{
				counter--;
			}

			Lcd_Goto_Row_Column(1, 0);
			Lcd_Displaynum(counter);
		}
		location++;
		if (location == 16) location = 0;
	}
}