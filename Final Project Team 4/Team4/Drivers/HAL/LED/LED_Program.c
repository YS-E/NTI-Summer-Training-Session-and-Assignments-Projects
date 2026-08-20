#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LED_Config.h"
#include "LED_Private.h"
#include "LED_Interface.h"

void LED_Init(u8 Port, u8 Pin) {
	DIO_SetPinDirection(Port, Pin, DIO_OUTPUT);
	LED_Off(Port, Pin);
}

void LED_On(u8 Port, u8 Pin) {
	#if (LED_CONNECTION_TYPE == LED_ACTIVE_HIGH)
	DIO_SetPinValue(Port, Pin, DIO_HIGH);
	#elif (LED_CONNECTION_TYPE == LED_ACTIVE_LOW)
	DIO_SetPinValue(Port, Pin, DIO_LOW);
	#endif
}

void LED_Off(u8 Port, u8 Pin) {
	#if (LED_CONNECTION_TYPE == LED_ACTIVE_HIGH)
	DIO_SetPinValue(Port, Pin, DIO_LOW);
	#elif (LED_CONNECTION_TYPE == LED_ACTIVE_LOW)
	DIO_SetPinValue(Port, Pin, DIO_HIGH);
	#endif
}

void LED_Toggle(u8 Port, u8 Pin) {
	if (DIO_GetPinValue(Port, Pin) == DIO_HIGH) {
		DIO_SetPinValue(Port, Pin, DIO_LOW);
		} else {
		DIO_SetPinValue(Port, Pin, DIO_HIGH);
	}
}

u8 LED_ReadState(u8 Port, u8 Pin) {
	u8 PinValue = DIO_GetPinValue(Port, Pin);
	u8 LedState = 0U;

	#if (LED_CONNECTION_TYPE == LED_ACTIVE_HIGH)
	LedState = PinValue;
	#elif (LED_CONNECTION_TYPE == LED_ACTIVE_LOW)
	LedState = (PinValue == DIO_LOW) ? 1U : 0U;
	#endif

	return LedState;
}