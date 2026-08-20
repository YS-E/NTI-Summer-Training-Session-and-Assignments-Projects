#define F_CPU 8000000UL
#include <avr/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Interface.h"

#include "SWITCH_Interface.h"
#include "LED_Interface.h"

#include "SPI_Interface.h"

#define LED_RED_PORT PORTB_ID
#define LED_RED_PIN PIN0

int main(void)
{
    LED_voidInit(LED_RED_PORT, LED_RED_PIN);
	SPI_Slave_Init();
	
    while (1) 
    {
		if(SPI_Read_Data() == 1)
		{
			LED_voidTurnOn(LED_RED_PORT, LED_RED_PIN);
		}
		else
			LED_voidTurnOff(LED_RED_PORT, LED_RED_PIN);
    }
}

