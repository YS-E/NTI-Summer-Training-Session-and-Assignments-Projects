#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "../../LIB/Bit_Math.h"


void DIO_SetPortDirection(u8 PortID,u8 PortDir)
{
	switch(PortID)
	{
	case PORTA_ID :   DIO_DDRA_REG= PortDir ; break ;
	case PORTB_ID :   DIO_DDRB_REG= PortDir ; break ;
	case PORTC_ID :   DIO_DDRC_REG= PortDir ; break ;
	case PORTD_ID :   DIO_DDRD_REG= PortDir ; break ;
	}
}

void DIO_SetPortValue(u8 PortID,u8 PortVal)
{

	switch(PortID)
	{
	case PORTA_ID :   DIO_PORTA_REG= PortVal ; break ;
	case PORTB_ID :   DIO_PORTB_REG= PortVal ; break ;
	case PORTC_ID :   DIO_PORTC_REG= PortVal ; break ;
	case PORTD_ID :   DIO_PORTD_REG= PortVal ; break ;
	}
}

void DIO_SetPinDirection(u8 PortID,u8 PinID,u8 PinDir)
{
	if(PinID>=PIN0&&PinID<=PIN7)
	{
		if(PinDir==DIO_OUTPUT)
		{
			switch(PortID)
			{
			case PORTA_ID:    SET_BIT(DIO_DDRA_REG,PinID); break;
			case PORTB_ID:    SET_BIT(DIO_DDRB_REG,PinID); break;
			case PORTC_ID:    SET_BIT(DIO_DDRC_REG,PinID); break;
			case PORTD_ID:    SET_BIT(DIO_DDRD_REG,PinID); break;

			default:   break;
			}
		}
		
		else if(PinDir==DIO_INPUT)
		{
			switch(PortID)
			{
			case PORTA_ID:   CLR_BIT(DIO_DDRA_REG,PinID); break;
			case PORTB_ID:   CLR_BIT(DIO_DDRB_REG,PinID); break;
			case PORTC_ID:   CLR_BIT(DIO_DDRC_REG,PinID); break;
			case PORTD_ID:   CLR_BIT(DIO_DDRD_REG,PinID); break;
			default:   break;
			}
		}
	}

}

void DIO_SetPinValue(u8 PortID,u8 PinID,u8 PinValue)
{
	if(PinID>=PIN0&&PinID<=PIN7)
	{
		if(PinValue==DIO_HIGH)
		{
			switch(PortID)
			{
			case PORTA_ID :    SET_BIT(DIO_PORTA_REG,PinID); break;
			case PORTB_ID :    SET_BIT(DIO_PORTB_REG,PinID); break;
			case PORTC_ID :    SET_BIT(DIO_PORTC_REG,PinID); break;
			case PORTD_ID :    SET_BIT(DIO_PORTD_REG,PinID); break;
			}
		}
		
		else if(PinValue==DIO_LOW)
		{
			switch(PortID)
			{
			case PORTA_ID : CLR_BIT(DIO_PORTA_REG,PinID); break;
			case PORTB_ID : CLR_BIT(DIO_PORTB_REG,PinID); break;
			case PORTC_ID : CLR_BIT(DIO_PORTC_REG,PinID); break;
			case PORTD_ID : CLR_BIT(DIO_PORTD_REG,PinID); break;

			}
		}
	}
}

u8 DIO_GetPinValue(u8 PortID , u8 PinID)
{
	u8 Local_PinVal = DIO_LOW;
	if(PinID >= PIN0 && PinID <= PIN7) {
		switch(PortID)
		{
		case PORTA_ID : Local_PinVal=GET_BIT(DIO_PINA_REG,PinID); break;
		case PORTB_ID : Local_PinVal=GET_BIT(DIO_PINB_REG,PinID); break;
		case PORTC_ID : Local_PinVal=GET_BIT(DIO_PINC_REG,PinID); break;
		case PORTD_ID : Local_PinVal=GET_BIT(DIO_PIND_REG,PinID); break;
		}
	}

	return Local_PinVal ;
}

void DIO_TogglePin(u8 PortID,u8 PinID)
{	if(PinID >= PIN0 && PinID <= PIN7) {
		switch (PortID)
		{
		case PORTA_ID :  TOG_BIT(DIO_PORTA_REG,PinID) ; break;
		case PORTB_ID :  TOG_BIT(DIO_PORTB_REG,PinID) ; break;
		case PORTC_ID :  TOG_BIT(DIO_PORTC_REG,PinID) ; break;
		case PORTD_ID :  TOG_BIT(DIO_PORTD_REG,PinID) ; break;
		}
	}
}





