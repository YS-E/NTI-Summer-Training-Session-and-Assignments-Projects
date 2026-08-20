/*
 * LED_Program.c
 *
 * Created: 12/08/2026 11:49:38 am
 *  Author: YS
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "LED_Interface.h"

void LED_voidInit(u8 copy_u8Port, u8 copy_u8Pin)
{
	DIO_voidSetPinDirection(copy_u8Port, copy_u8Pin, PIN_OUTPUT);
}

void LED_voidTurnOn(u8 copy_u8Port, u8 copy_u8Pin)
{
	DIO_voidSetPinValue(copy_u8Port, copy_u8Pin, PIN_HIGH);
}

void LED_voidTurnOff(u8 copy_u8Port, u8 copy_u8Pin)
{
	DIO_voidSetPinValue(copy_u8Port, copy_u8Pin, PIN_LOW);
}