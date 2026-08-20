#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
#include "../DIO/DIO_Interface.h"
#include "EXT_Private.h"
#include "EXT_Config.h"
#include "EXT_Interface.h"

static void (*ptr_ArrCallBack[3])(void) = {NULL,NULL,NULL};


void EXT_Init(u8 ExtNum,u8 ControlSens)
{
	switch(ExtNum)
	{
	case EXT0:
	DIO_SetPinDirection(PORTD_ID, PIN2, DIO_INPUT);
	switch(ControlSens)
	{
		case LOW_LEVEL:          CLR_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case ANY_LOGICAL_CHANGE: SET_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case FALLING_EDGE:       CLR_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		case RISING_EDGE:        SET_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		default: break;
	}
	SET_BIT(GIFR, GIFR_INTF0);
	SET_BIT(GICR, GICR_INT0);
	break;

	case EXT1:
	DIO_SetPinDirection(PORTD_ID, PIN3, DIO_INPUT);
	switch(ControlSens)
	{
		case LOW_LEVEL:          CLR_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case ANY_LOGICAL_CHANGE: SET_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case FALLING_EDGE:       CLR_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		case RISING_EDGE:        SET_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		default: break;
	}
	SET_BIT(GIFR, GIFR_INTF1);
	SET_BIT(GICR, GICR_INT1);
	break;

	case EXT2 :

		DIO_SetPinDirection(PORTB_ID,PIN2,DIO_INPUT);
		if(ControlSens==FALLING_EDGE)
		{
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
		}

		else if(ControlSens==RISING_EDGE)
		{
			SET_BIT(MCUCSR,MCUCSR_ISC2);
		}
		
		SET_BIT(GIFR, GIFR_INTF2);
		SET_BIT(GICR,GICR_INT2);

		break ;

	}
}

void EXT_SetCallBack(  void (*ptr_ext)(void) ,u8 ExtNum )
{
	if(ptr_ext!=NULL)
	{
		switch(ExtNum)
		{
		case EXT0:
			ptr_ArrCallBack[ 0 ]= ptr_ext;
			break;
		case EXT1:
			ptr_ArrCallBack[ 1 ]= ptr_ext;
			break;
		case EXT2:
			ptr_ArrCallBack[ 2 ]= ptr_ext;
			break;
		default: break;
		}
	}
}

void EXT_Disable(u8 ExtNum)
{
	switch(ExtNum)
	{
		case EXT0: CLR_BIT(GICR, GICR_INT0); break;
		case EXT1: CLR_BIT(GICR, GICR_INT1); break;
		case EXT2: CLR_BIT(GICR, GICR_INT2); break;
		default: break;
	}
}

// Standard AVR functions to use interrupts
// remove anything with an empty comment to disable nesting
void __vector_1 (void) __attribute__ ((signal));
void __vector_1 (void)
{
    if (ptr_ArrCallBack[0] != NULL)
    {
        ptr_ArrCallBack[0]();
    }
}

void __vector_2 (void) __attribute__ ((signal));
void __vector_2 (void)
{
    CLR_BIT(GICR, GICR_INT1); //
    CLR_BIT(GICR, GICR_INT2); //

    SET_BIT(SREG, SREG_I);
    if (ptr_ArrCallBack[1] != NULL)
    {
        ptr_ArrCallBack[1]();
    }

    CLR_BIT(SREG, SREG_I); //

    SET_BIT(GICR, GICR_INT1); //
    SET_BIT(GICR, GICR_INT2); //
}

void __vector_3 (void) __attribute__ ((signal));
void __vector_3 (void)
{
    CLR_BIT(GICR, GICR_INT2); //
    SET_BIT(SREG, SREG_I); //

    if (ptr_ArrCallBack[2] != NULL)
    {
        ptr_ArrCallBack[2]();
    }

    CLR_BIT(SREG, SREG_I); //
    SET_BIT(GICR, GICR_INT2); //
}

