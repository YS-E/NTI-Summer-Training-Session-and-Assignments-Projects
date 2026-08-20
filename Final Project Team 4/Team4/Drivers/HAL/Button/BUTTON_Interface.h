#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/* Button Output States */
#define BUTTON_RELEASED          0U
#define BUTTON_PRESSED           1U

/* Public Function Prototypes */
void Button_Init(u8 Port, u8 Pin);
u8 Button_Read(u8 Port, u8 Pin);

#endif /* BUTTON_INTERFACE_H_ */