#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"

#include "7_Segment_Config.h"
#include "7_Segment_Interface.h"
#include "7_Segment_Private.h"

void HAL_7SEGMENT_INIT(void)
{
	DIO_voidSetPinDirection(SEGMANTA_PORT, SEGMANTA_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(SEGMANTB_PORT, SEGMANTB_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(SEGMANTC_PORT, SEGMANTC_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(SEGMANTD_PORT, SEGMANTD_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(SEGMANTE_PORT, SEGMANTE_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(SEGMANTF_PORT, SEGMANTF_PIN, PIN_OUTPUT);
	DIO_voidSetPinDirection(SEGMANTG_PORT, SEGMANTG_PIN, PIN_OUTPUT);
}

void HAL_7SEGMENT_WRITE(u8 display_number)
{
	switch (display_number)
	{
		case ZERO:
			display_zero();
			break;

		case ONE:
			display_one();
			break;

		case TWO:
			display_two();
			break;

		case THREE:
			display_three();
			break;

		default:
			break;
	}
}

void display_zero(void)
{
	DIO_voidSetPinValue(SEGMANTA_PORT, SEGMANTA_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTB_PORT, SEGMANTB_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTC_PORT, SEGMANTC_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTD_PORT, SEGMANTD_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTE_PORT, SEGMANTE_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTF_PORT, SEGMANTF_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTG_PORT, SEGMANTG_PIN, PIN_LOW);
}

void display_one(void)
{
	DIO_voidSetPinValue(SEGMANTA_PORT, SEGMANTA_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTB_PORT, SEGMANTB_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTC_PORT, SEGMANTC_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTD_PORT, SEGMANTD_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTE_PORT, SEGMANTE_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTF_PORT, SEGMANTF_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTG_PORT, SEGMANTG_PIN, PIN_LOW);
}

void display_two(void)
{
	DIO_voidSetPinValue(SEGMANTA_PORT, SEGMANTA_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTB_PORT, SEGMANTB_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTC_PORT, SEGMANTC_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTD_PORT, SEGMANTD_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTE_PORT, SEGMANTE_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTF_PORT, SEGMANTF_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTG_PORT, SEGMANTG_PIN, PIN_HIGH);
}

void display_three(void)
{
	DIO_voidSetPinValue(SEGMANTA_PORT, SEGMANTA_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTB_PORT, SEGMANTB_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTC_PORT, SEGMANTC_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTD_PORT, SEGMANTD_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTE_PORT, SEGMANTE_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTF_PORT, SEGMANTF_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTG_PORT, SEGMANTG_PIN, PIN_HIGH);
}

void display_four(void)
{
	DIO_voidSetPinValue(SEGMANTA_PORT, SEGMANTA_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTB_PORT, SEGMANTB_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTC_PORT, SEGMANTC_PIN, PIN_HIGH);
	DIO_voidSetPinValue(SEGMANTD_PORT, SEGMANTD_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTE_PORT, SEGMANTE_PIN, PIN_LOW);
	DIO_voidSetPinValue(SEGMANTF_PORT, SEGMANTF_PIN, PIN_HIGH;
	DIO_voidSetPinValue(SEGMANTG_PORT, SEGMANTG_PIN, PIN_HIGH);
}