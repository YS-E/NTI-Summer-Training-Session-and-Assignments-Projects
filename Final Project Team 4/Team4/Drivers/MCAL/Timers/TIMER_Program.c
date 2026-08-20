#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
#include "TIMER_Private.h"
#include "TIMER_Config.h"
#include "TIMER_Interface.h"

void TIMER_Init(TIMER_IdType Timer, u8 Prescaler)
{
	switch(Timer)
	{
	case TIMER_0:
		/* Normal mode: WGM01:0 = 00 -> free-running counter, no waveform generation */
		CLR_BIT(TIMER_TCCR0, TCCR0_WGM01);
		CLR_BIT(TIMER_TCCR0, TCCR0_WGM00);
		/* OC0 (PB3) left untouched: COM01:0 = 00 -> Normal port operation */
		CLR_BIT(TIMER_TCCR0, TCCR0_COM01);
		CLR_BIT(TIMER_TCCR0, TCCR0_COM00);

		TIMER_TCNT0 = 0U;
		SET_BIT(TIMER_TIFR, TIFR_TOV0);   /* clear any stale overflow flag */

		/* Select clock source -> this also starts the timer */
		TIMER_TCCR0 = (u8)((TIMER_TCCR0 & TIMER_CS_MASK) | (Prescaler & 0x07U));
		break;

	case TIMER_1:
		/* Normal mode: WGM13:0 = 0000 -> free-running counter, no waveform generation */
		CLR_BIT(TIMER_TCCR1B, TCCR1B_WGM13);
		CLR_BIT(TIMER_TCCR1B, TCCR1B_WGM12);
		CLR_BIT(TIMER_TCCR1A, TCCR1A_WGM11);
		CLR_BIT(TIMER_TCCR1A, TCCR1A_WGM10);
		/* OC1A/OC1B (PD5/PD4) left untouched: COM1A1:0 = COM1B1:0 = 00 */
		CLR_BIT(TIMER_TCCR1A, TCCR1A_COM1A1);
		CLR_BIT(TIMER_TCCR1A, TCCR1A_COM1A0);
		CLR_BIT(TIMER_TCCR1A, TCCR1A_COM1B1);
		CLR_BIT(TIMER_TCCR1A, TCCR1A_COM1B0);

		/* 16-bit write: high byte first, per datasheet 16-bit access rule */
		TIMER_TCNT1H = 0U;
		TIMER_TCNT1L = 0U;
		SET_BIT(TIMER_TIFR, TIFR_TOV1);   /* clear any stale overflow flag */

		/* Select clock source -> this also starts the timer */
		TIMER_TCCR1B = (u8)((TIMER_TCCR1B & TIMER_CS_MASK) | (Prescaler & 0x07U));
		break;

	case TIMER_2:
	default:
		/* Normal mode: WGM21:0 = 00 -> free-running counter, no waveform generation */
		CLR_BIT(TIMER_TCCR2, TCCR2_WGM21);
		CLR_BIT(TIMER_TCCR2, TCCR2_WGM20);
		/* OC2 (PD7) left untouched: COM21:0 = 00 -> Normal port operation */
		CLR_BIT(TIMER_TCCR2, TCCR2_COM21);
		CLR_BIT(TIMER_TCCR2, TCCR2_COM20);

		TIMER_TCNT2 = 0U;
		SET_BIT(TIMER_TIFR, TIFR_TOV2);   /* clear any stale overflow flag */

		/* Select clock source -> this also starts the timer */
		TIMER_TCCR2 = (u8)((TIMER_TCCR2 & TIMER_CS_MASK) | (Prescaler & 0x07U));
		break;
	}
}

void TIMER_Stop(TIMER_IdType Timer)
{
	switch(Timer)
	{
	case TIMER_0: TIMER_TCCR0  &= TIMER_CS_MASK; break;
	case TIMER_1: TIMER_TCCR1B &= TIMER_CS_MASK; break;
	case TIMER_2:
	default:      TIMER_TCCR2  &= TIMER_CS_MASK; break;
	}
}

void TIMER_SetCount(TIMER_IdType Timer, u16 Count)
{
	switch(Timer)
	{
	case TIMER_0:
		TIMER_TCNT0 = (u8)Count;
		break;

	case TIMER_1:
		/* 16-bit write: high byte first, per datasheet 16-bit access rule */
		TIMER_TCNT1H = (u8)(Count >> 8);
		TIMER_TCNT1L = (u8)(Count);
		break;

	case TIMER_2:
	default:
		TIMER_TCNT2 = (u8)Count;
		break;
	}
}

u16 TIMER_GetCount(TIMER_IdType Timer)
{
	u16 Result = 0U;
	u8  Low;

	switch(Timer)
	{
	case TIMER_0:
		Result = (u16)TIMER_TCNT0;
		break;

	case TIMER_1:
		/* 16-bit read: low byte first, per datasheet 16-bit access rule */
		Low     = TIMER_TCNT1L;
		Result = (u16)(((u16)TIMER_TCNT1H << 8) | Low);
		break;

	case TIMER_2:
	default:
		Result = (u16)TIMER_TCNT2;
		break;
	}

	return Result;
}

u8 TIMER_IsOverflow(TIMER_IdType Timer)
{
	u8 Result  = 0U;
	u8 FlagBit = TIFR_TOV2;

	switch(Timer)
	{
	case TIMER_0: FlagBit = TIFR_TOV0; break;
	case TIMER_1: FlagBit = TIFR_TOV1; break;
	case TIMER_2:
	default:      FlagBit = TIFR_TOV2; break;
	}

	if (GET_BIT(TIMER_TIFR, FlagBit) != 0U)
	{
		SET_BIT(TIMER_TIFR, FlagBit);   /* write 1 to clear the flag */
		Result = 1U;
	}

	return Result;
}
