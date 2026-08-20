#define F_CPU 8000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Interface.h"

#include "SWITCH_Interface.h"
#include "LED_Interface.h"

#include "SPI_Interface.h"

#define SWITCH_PORT PORTD_ID
#define SWITCH_PIN PIN0

int main(void)
{
	SPI_Master_Init();
	SWITCH_voidInit(SWITCH_PORT, SWITCH_PIN);
    
    while (1) 
    {
		if(SWITCH_u8GetState(SWITCH_PORT, SWITCH_PIN) == 1)
		{
			SPI_Send_Data(1);
		}
		else
			SPI_Send_Data(0);
		_delay_ms(50);
    }
}

