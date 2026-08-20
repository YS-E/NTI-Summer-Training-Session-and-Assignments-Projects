#ifndef	DIO_INTERFACE_H_
#define	DIO_INTERFACE_H_

#include "../../LIB/Std_Types.h"

// Port ID Macros
// Allows usage of 'A' as the PortID

#define PORTA_ID        ('A')
#define PORTB_ID        ('B')
#define PORTC_ID        ('C')
#define PORTD_ID        ('D')

// Pin ID Macros
// Allows usage of numbers at PinID

#define PIN0         (0x00)
#define PIN1         (0x01)
#define PIN2         (0x02)
#define PIN3         (0x03)
#define PIN4         (0x04)
#define PIN5         (0x05)
#define PIN6         (0x06)
#define PIN7         (0x07)

// Direction Macros

#define DIO_OUTPUT         (0x01)
#define DIO_INPUT          (0x00)

#define DIO_HIGH           (0x01)
#define DIO_LOW            (0x00)

#define DIO_ALL_OUTPUT    (0xFF)
#define DIO_ALL_INPUT     (0x00)

#define DIO_ALL_HIGH      (0xFF)
#define DIO_ALL_LOW       (0x00)

/*Prototypes*/
void    DIO_SetPortDirection(u8 PortID,u8 PortDir);
void    DIO_SetPortValue(u8 PortID,u8 PortVal);
void	DIO_SetPinDirection(u8 PortID,u8 PinID,u8 PinDir);
void    DIO_SetPinValue(u8 PortID,u8 PinID,u8 PinValue);
void	DIO_TogglePin(u8 PortID,u8 PinID);
u8		DIO_GetPinValue(u8 PortID , u8 PinID);

#endif
