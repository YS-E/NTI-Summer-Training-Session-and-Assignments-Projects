#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"

#include "LED_Interface.h"
#include "SWITCH_Interface.h"
#include "UART_Interface.h"

#define RX_LED_PORT     PORTB_ID
#define RX_LED_PIN      PIN0

#define TX_BUTTON_PORT  PORTD_ID
#define TX_BUTTON_PIN   PIN2

int main(void)
{
    u8 tx_data = 'L';
    u8 rx_data = 0;

    LED_voidInit(RX_LED_PORT, RX_LED_PIN);
    SWITCH_voidInit(TX_BUTTON_PORT, TX_BUTTON_PIN);
    
    USART_Init(9600);

    while (1) 
    {
        if (DIO_voidGetBitValue(TX_BUTTON_PORT, TX_BUTTON_PIN) == PIN_HIGH)
        {
            _delay_ms(30);
            if (DIO_voidGetBitValue(TX_BUTTON_PORT, TX_BUTTON_PIN) == PIN_HIGH)
            {
                USART_Transmit(tx_data);

                rx_data = USART_Receive();
// 				rx_data = 'k';
                if (rx_data == tx_data)
                {
                    LED_voidTurnOn(RX_LED_PORT, RX_LED_PIN);
                }
                else
                {
                    LED_voidTurnOff(RX_LED_PORT, RX_LED_PIN);
                }

                while (DIO_voidGetBitValue(TX_BUTTON_PORT, TX_BUTTON_PIN) == PIN_HIGH);
            }
        }
    }
}