#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
#include "UART_Private.h"
#include "UART_Config.h"
#include "UART_Interface.h"

void USART_Init(u32 baud_rate, u8 data_bits, u8 stop_bits)
{
	u16 baud_prescale;
	u8 ucsrc_var = 0;

	/* Calculate baud rate prescaler */
	baud_prescale = ((F_CPU / (baud_rate * 16UL))) - 1;

	/* Speed mode Normal */
	CLR_BIT(UCSRA, 1);
	
	/* Enable Receiver and Transmitter */
	SET_BIT(UCSRB, 3);
	SET_BIT(UCSRB, 4); 

	/* Select UCSRC Register */
	SET_BIT(ucsrc_var, 7);

	/* Configure Data Bits */
	switch (data_bits)
	{
		case 5:
		/* UCSZ1 = 0, UCSZ0 = 0 */
		CLR_BIT(ucsrc_var, 2);
		CLR_BIT(ucsrc_var, 1);
		break;
		case 6:
		/* UCSZ1 = 0, UCSZ0 = 1 */
		CLR_BIT(ucsrc_var, 2);
		SET_BIT(ucsrc_var, 1);
		break;
		case 7:
		/* UCSZ1 = 1, UCSZ0 = 0 */
		SET_BIT(ucsrc_var, 2);
		CLR_BIT(ucsrc_var, 1);
		break;
		case 8:
		default:
		/* UCSZ1 = 1, UCSZ0 = 1 */
		SET_BIT(ucsrc_var, 2);
		SET_BIT(ucsrc_var, 1);
		break;
	}

	/* Configure Stop Bits */
	if (stop_bits == 2)
	{
		SET_BIT(ucsrc_var, 3); /* USBS = 1 (2 Stop Bits) */
	}
	else
	{
		CLR_BIT(ucsrc_var, 3); /* USBS = 0 (1 Stop Bit) */
	}

	/* Write configuration to UCSRC */
	UCSRC = ucsrc_var;

	/* Set Baud Rate: URSEL must be 0 for UBRRH */
	UBRRH = (u8)((baud_prescale >> 8) & 0x7F);
	UBRRL = (u8)baud_prescale;
}

void USART_Transmit(u8 data)
{
	u32 timeout = 0;

	while ((GET_BIT(UCSRA, 5) == 0) && (timeout < USART_TIMEOUT))
	{
		timeout++;
	}
	
	if (timeout < USART_TIMEOUT)
	{
		UDR = data;
	}
}

u8 USART_Receive(void)
{
	u32 timeout = 0;

	while ((GET_BIT(UCSRA, 7) == 0) && (timeout < USART_TIMEOUT))
	{
		timeout++;
	}

	if (timeout < USART_TIMEOUT)
	{
		return UDR;
	}
	
	return 0;
}

void USART_SendString(const char *str)
{
	u8 i = 0;
	while (str[i] != '\0')
	{
		USART_Transmit(str[i]);
		i++;
	}
}