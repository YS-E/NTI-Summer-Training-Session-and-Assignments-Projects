#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "BUTTON_Config.h"
#include "BUTTON_Private.h"
#include "BUTTON_Interface.h"

void Button_Init(u8 Port, u8 Pin) {
	DIO_SetPinDirection(Port, Pin, DIO_INPUT);

	#if (BUTTON_PULL_TYPE == BUTTON_PULL_UP)
	DIO_SetPinValue(Port, Pin, DIO_HIGH);
	#else
	DIO_SetPinValue(Port, Pin, DIO_LOW);
	#endif
}

u8 Button_Read(u8 Port, u8 Pin) {
	u8 PinValue = DIO_GetPinValue(Port, Pin);
	u8 ButtonState = BUTTON_RELEASED;

	#if (BUTTON_ACTIVE_STATE == BUTTON_ACTIVE_LOW)
	if (PinValue == DIO_LOW) {
		ButtonState = BUTTON_PRESSED;
		} else {
		ButtonState = BUTTON_RELEASED;
	}
	#elif (BUTTON_ACTIVE_STATE == BUTTON_ACTIVE_HIGH)
	if (PinValue == DIO_HIGH) {
		ButtonState = BUTTON_PRESSED;
		} else {
		ButtonState = BUTTON_RELEASED;
	}
	#endif

	return ButtonState;
}