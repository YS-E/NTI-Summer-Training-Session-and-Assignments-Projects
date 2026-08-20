#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#include "../../LIB/Std_Types.h"
#include "DIO_Config.h"

#if DIO_USE_AVR_REGISTERS

#include <avr/io.h>

#define DIO_PORTA_REG    PORTA
#define DIO_DDRA_REG     DDRA
#define DIO_PINA_REG     PINA

#define DIO_PORTB_REG    PORTB
#define DIO_DDRB_REG     DDRB
#define DIO_PINB_REG     PINB

#define DIO_PORTC_REG    PORTC
#define DIO_DDRC_REG     DDRC
#define DIO_PINC_REG     PINC

#define DIO_PORTD_REG    PORTD
#define DIO_DDRD_REG     DDRD
#define DIO_PIND_REG     PIND

#else

#define DIO_PORTA_REG    *((volatile u8*)0x3B)
#define DIO_DDRA_REG     *((volatile u8*)0x3A)
#define DIO_PINA_REG     *((volatile u8*)0x39)

#define DIO_PORTB_REG    *((volatile u8*)0x38)
#define DIO_DDRB_REG     *((volatile u8*)0x37)
#define DIO_PINB_REG     *((volatile u8*)0x36)

#define DIO_PORTC_REG    *((volatile u8*)0x35)
#define DIO_DDRC_REG     *((volatile u8*)0x34)
#define DIO_PINC_REG     *((volatile u8*)0x33)

#define DIO_PORTD_REG    *((volatile u8*)0x32)
#define DIO_DDRD_REG     *((volatile u8*)0x31)
#define DIO_PIND_REG     *((volatile u8*)0x30)

#endif

#endif /* DIO_PRIVATE_H_ */