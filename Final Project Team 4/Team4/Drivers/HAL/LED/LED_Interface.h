#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/* Public API Prototypes */
void LED_Init(u8 Port, u8 Pin);
void LED_On(u8 Port, u8 Pin);
void LED_Off(u8 Port, u8 Pin);
void LED_Toggle(u8 Port, u8 Pin);
u8 LED_ReadState(u8 Port, u8 Pin);

#endif /* LED_INTERFACE_H_ */