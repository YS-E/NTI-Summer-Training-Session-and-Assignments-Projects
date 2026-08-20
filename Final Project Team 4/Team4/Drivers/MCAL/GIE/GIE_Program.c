#include "../../LIB/Bit_Math.h"
#include "GIE_Private.h"

void GIE_Enable(void)
{
    SET_BIT(SREG,7);
}

void GIE_Disable(void)
{
	CLR_BIT(SREG,7);
}


