#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
#include "PWM_Private.h"
#include "PWM_Config.h"
#include "PWM_Interface.h"

/* Current Timer1 TOP value (resolution), needed to convert % -> raw ticks */
static u16 Global_u16Timer1Top = 0xFFFF;

/* ============================================================================
 *                                  TIMER0
 * ==========================================================================*/
void PWM_Timer0Init(PWM_ModeType Mode, PWM_PrescalerType Prescaler)
{
	/* OC0 (PB3) must be an output for the waveform to reach the pin */
	SET_BIT(PWM_DDRB, PWM_OC0_PIN);

	/* Waveform Generation Mode (8-bit, TOP fixed at 0xFF) */
	if(Mode == PWM_MODE_FAST)
	{
		SET_BIT(PWM_TCCR0, TCCR0_WGM01);
		SET_BIT(PWM_TCCR0, TCCR0_WGM00);
	}
	else /* PWM_MODE_PHASE_CORRECT */
	{
		CLR_BIT(PWM_TCCR0, TCCR0_WGM01);
		SET_BIT(PWM_TCCR0, TCCR0_WGM00);
	}

	/* Non-inverting: clear OC0 on compare match (set/clear at BOTTOM) */
	SET_BIT(PWM_TCCR0, TCCR0_COM01);
	CLR_BIT(PWM_TCCR0, TCCR0_COM00);

	/* Start at 0% duty until the application requests otherwise */
	PWM_OCR0 = 0;

	/* Select clock source -> this also starts the timer */
	PWM_TCCR0 = (u8)((PWM_TCCR0 & PWM_CS_MASK) | (Prescaler & 0x07));
}

void PWM_Timer0SetDuty(u8 DutyPercent)
{
	if(DutyPercent > 100)
	{
		DutyPercent = 100;
	}
	/* OCR0 = Duty% * 255 / 100 */
	PWM_OCR0 = (u8)(((u16)DutyPercent * 255U) / 100U);
}

void PWM_Timer0SetDutyRaw(u8 Raw)
{
	PWM_OCR0 = Raw;
}

void PWM_Timer0Stop(void)
{
	/* Clock select = 000 -> Timer/Counter stopped */
	PWM_TCCR0 &= PWM_CS_MASK;
}

/* ============================================================================
 *                                  TIMER2
 * ==========================================================================*/
void PWM_Timer2Init(PWM_ModeType Mode, PWM_Timer2PrescalerType Prescaler)
{
	/* OC2 (PD7) must be an output for the waveform to reach the pin */
	SET_BIT(PWM_DDRD, PWM_OC2_PIN);

	if(Mode == PWM_MODE_FAST)
	{
		SET_BIT(PWM_TCCR2, TCCR2_WGM21);
		SET_BIT(PWM_TCCR2, TCCR2_WGM20);
	}
	else /* PWM_MODE_PHASE_CORRECT */
	{
		CLR_BIT(PWM_TCCR2, TCCR2_WGM21);
		SET_BIT(PWM_TCCR2, TCCR2_WGM20);
	}

	/* Non-inverting: clear OC2 on compare match (set/clear at BOTTOM) */
	SET_BIT(PWM_TCCR2, TCCR2_COM21);
	CLR_BIT(PWM_TCCR2, TCCR2_COM20);

	PWM_OCR2 = 0;

	PWM_TCCR2 = (u8)((PWM_TCCR2 & PWM_CS_MASK) | (Prescaler & 0x07));
}

void PWM_Timer2SetDuty(u8 DutyPercent)
{
	if(DutyPercent > 100)
	{
		DutyPercent = 100;
	}
	PWM_OCR2 = (u8)(((u16)DutyPercent * 255U) / 100U);
}

void PWM_Timer2SetDutyRaw(u8 Raw)
{
	PWM_OCR2 = Raw;
}

void PWM_Timer2Stop(void)
{
	PWM_TCCR2 &= PWM_CS_MASK;
}

/* ============================================================================
 *                                  TIMER1
 * ==========================================================================*/
void PWM_Timer1Init(u32 FreqHz, PWM1_ModeType Mode)
{
	static const u16 Prescalers[5] = {1U, 8U, 64U, 256U, 1024U};
	static const u8  CSBits[5]      = {1U, 2U, 3U, 4U, 5U};

	u8  Index;
	u8  Prescale = CSBits[4];
	u32 Top      = 0xFFFFUL;

	if(FreqHz == 0)
	{
		FreqHz = 1; /* guard against divide-by-zero */
	}

	/* Pick the smallest prescaler that keeps TOP inside the 16-bit range,
	 * which maximizes the duty-cycle resolution for the requested frequency */
	for(Index = 0; Index < 5; Index++)
	{
		u32 CandidateTop;

		if(Mode == PWM1_MODE_FAST)
		{
			/* f = F_CPU / (N * (1 + TOP))  =>  TOP = F_CPU / (N * f) - 1 */
			CandidateTop = (F_CPU / ((u32)Prescalers[Index] * FreqHz));
			if(CandidateTop > 0)
			{
				CandidateTop -= 1;
			}
		}
		else
		{
			/* Phase (& Frequency) Correct: f = F_CPU / (2*N*TOP) => TOP = F_CPU/(2*N*f) */
			CandidateTop = (F_CPU / (2UL * (u32)Prescalers[Index] * FreqHz));
		}

		if(CandidateTop <= 0xFFFFUL)
		{
			Prescale = CSBits[Index];
			Top     = CandidateTop;
			break;
		}
	}

	if(Top == 0)
	{
		Top = 1; /* TOP = 0 would disable PWM entirely */
	}

	Global_u16Timer1Top = (u16)Top;

	/* Waveform Generation Mode: TOP = ICR1 in all three sub-modes */
	switch(Mode)
	{
		case PWM1_MODE_FAST:
			/* WGM13:0 = 1110 */
			SET_BIT(PWM_TCCR1B, TCCR1B_WGM13);
			SET_BIT(PWM_TCCR1B, TCCR1B_WGM12);
			SET_BIT(PWM_TCCR1A, TCCR1A_WGM11);
			CLR_BIT(PWM_TCCR1A, TCCR1A_WGM10);
			break;

		case PWM1_MODE_PHASE_CORRECT:
			/* WGM13:0 = 1010 */
			SET_BIT(PWM_TCCR1B, TCCR1B_WGM13);
			CLR_BIT(PWM_TCCR1B, TCCR1B_WGM12);
			SET_BIT(PWM_TCCR1A, TCCR1A_WGM11);
			CLR_BIT(PWM_TCCR1A, TCCR1A_WGM10);
			break;

		case PWM1_MODE_PHASE_FREQ_CORRECT:
		default:
			/* WGM13:0 = 1000 */
			SET_BIT(PWM_TCCR1B, TCCR1B_WGM13);
			CLR_BIT(PWM_TCCR1B, TCCR1B_WGM12);
			CLR_BIT(PWM_TCCR1A, TCCR1A_WGM11);
			CLR_BIT(PWM_TCCR1A, TCCR1A_WGM10);
			break;
	}

	/* Load TOP into ICR1 (high byte first, per datasheet 16-bit access rule) */
	PWM_ICR1H = (u8)(Global_u16Timer1Top >> 8);
	PWM_ICR1L = (u8)(Global_u16Timer1Top);

	/* Start both compare outputs at 0% duty */
	PWM_OCR1AH = 0; PWM_OCR1AL = 0;
	PWM_OCR1BH = 0; PWM_OCR1BL = 0;

	/* Enable both channels by default (non-inverting, pins as outputs) */
	PWM_Timer1EnableChannelA();
	PWM_Timer1EnableChannelB();

	/* Select clock source -> this also starts the timer */
	PWM_TCCR1B = (u8)((PWM_TCCR1B & PWM_CS_MASK) | (Prescale & 0x07));
}

void PWM_Timer1EnableChannelA(void)
{
	SET_BIT(PWM_DDRD, PWM_OC1A_PIN);
	SET_BIT(PWM_TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(PWM_TCCR1A, TCCR1A_COM1A0);
}

void PWM_Timer1EnableChannelB(void)
{
	SET_BIT(PWM_DDRD, PWM_OC1B_PIN);
	SET_BIT(PWM_TCCR1A, TCCR1A_COM1B1);
	CLR_BIT(PWM_TCCR1A, TCCR1A_COM1B0);
}

void PWM_Timer1DisableChannelA(void)
{
	/* COM1A1:0 = 00 -> OC1A disconnected, PD5 back to normal I/O */
	CLR_BIT(PWM_TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(PWM_TCCR1A, TCCR1A_COM1A0);
}

void PWM_Timer1DisableChannelB(void)
{
	/* COM1B1:0 = 00 -> OC1B disconnected, PD4 back to normal I/O */
	CLR_BIT(PWM_TCCR1A, TCCR1A_COM1B1);
	CLR_BIT(PWM_TCCR1A, TCCR1A_COM1B0);
}

void PWM_Timer1SetDutyA(u8 DutyPercent)
{
	u16 Compare;

	if(DutyPercent > 100)
	{
		DutyPercent = 100;
	}
	Compare = (u16)(((u32)DutyPercent * Global_u16Timer1Top) / 100U);
	PWM_Timer1SetDutyRawA(Compare);
}

void PWM_Timer1SetDutyB(u8 DutyPercent)
{
	u16 Compare;

	if(DutyPercent > 100)
	{
		DutyPercent = 100;
	}
	Compare = (u16)(((u32)DutyPercent * Global_u16Timer1Top) / 100U);
	PWM_Timer1SetDutyRawB(Compare);
}

void PWM_Timer1SetDutyRawA(u16 Raw)
{
	if(Raw > Global_u16Timer1Top)
	{
		Raw = Global_u16Timer1Top;
	}
	PWM_OCR1AH = (u8)(Raw >> 8);
	PWM_OCR1AL = (u8)(Raw);
}

void PWM_Timer1SetDutyRawB(u16 Raw)
{
	if(Raw > Global_u16Timer1Top)
	{
		Raw = Global_u16Timer1Top;
	}
	PWM_OCR1BH = (u8)(Raw >> 8);
	PWM_OCR1BL = (u8)(Raw);
}

u16 PWM_Timer1GetTop(void)
{
	return Global_u16Timer1Top;
}

void PWM_Timer1Stop(void)
{
	/* Clock select = 000 -> Timer/Counter stopped */
	PWM_TCCR1B &= PWM_CS_MASK;
}
