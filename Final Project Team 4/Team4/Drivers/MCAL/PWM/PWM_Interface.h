#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/*
 * ============================================================================
 * PWM Driver for ATmega32
 * ----------------------------------------------------------------------------
 * Covers all three PWM-capable timers:
 *   - Timer0  -> OC0  (PB3) : 8-bit,  Fast / Phase Correct PWM
 *   - Timer1  -> OC1A (PD5), OC1B (PD4) : 16-bit, TOP = ICR1 (any frequency)
 *   - Timer2  -> OC2  (PD7) : 8-bit,  Fast / Phase Correct PWM
 *
 * All channels are configured for NON-INVERTING output.
 * ============================================================================
 */

/* Waveform mode shared by Timer0 / Timer2 (fixed 8-bit TOP = 0xFF) */
typedef enum
{
	PWM_MODE_FAST,           /* Fast PWM         (single-slope) */
	PWM_MODE_PHASE_CORRECT   /* Phase Correct PWM (dual-slope)  */
}PWM_ModeType;

/* Timer0 / Timer1 clock-select prescaler table (identical encoding) */
typedef enum
{
	PWM_PRESCALER_STOP  = 0,
	PWM_PRESCALER_1     = 1,
	PWM_PRESCALER_8     = 2,
	PWM_PRESCALER_64    = 3,
	PWM_PRESCALER_256   = 4,
	PWM_PRESCALER_1024  = 5
}PWM_PrescalerType;

/* Timer2 has its own, different clock-select prescaler table */
typedef enum
{
	PWM2_PRESCALER_STOP  = 0,
	PWM2_PRESCALER_1     = 1,
	PWM2_PRESCALER_8     = 2,
	PWM2_PRESCALER_32    = 3,
	PWM2_PRESCALER_64    = 4,
	PWM2_PRESCALER_128   = 5,
	PWM2_PRESCALER_256   = 6,
	PWM2_PRESCALER_1024  = 7
}PWM_Timer2PrescalerType;

/* Timer1 waveform sub-modes (TOP is always ICR1, so any frequency is possible) */
typedef enum
{
	PWM1_MODE_FAST,                /* Fast PWM,                  TOP = ICR1 */
	PWM1_MODE_PHASE_CORRECT,       /* Phase Correct PWM,         TOP = ICR1 */
	PWM1_MODE_PHASE_FREQ_CORRECT   /* Phase & Frequency Correct, TOP = ICR1 */
}PWM1_ModeType;

/* ============================= Timer0 -> OC0 (PB3) ====================== */
/* Duty starts at 0%. Prescaler also starts the timer. */
void PWM_Timer0Init(PWM_ModeType Copy_Mode, PWM_PrescalerType Copy_Prescaler);
void PWM_Timer0SetDuty(u8 DutyPercent);   /* 0 - 100 %            */
void PWM_Timer0SetDutyRaw(u8 Raw);        /* 0 - 255 (full range) */
void PWM_Timer0Stop(void);

/* ============================= Timer2 -> OC2 (PD7) ====================== */
void PWM_Timer2Init(PWM_ModeType Copy_Mode, PWM_Timer2PrescalerType Copy_Prescaler);
void PWM_Timer2SetDuty(u8 DutyPercent);   /* 0 - 100 %            */
void PWM_Timer2SetDutyRaw(u8 Raw);        /* 0 - 255 (full range) */
void PWM_Timer2Stop(void);

/* ==================== Timer1 -> OC1A (PD5) / OC1B (PD4) ================= */
/*
 * Copy_u32FreqHz : desired PWM frequency in Hz.
 * The driver automatically picks the smallest prescaler (1/8/64/256/1024)
 * that lets the required TOP value fit inside the 16-bit ICR1 register,
 * giving the best possible resolution for the requested frequency.
 * Both channels are enabled (non-inverting) and set to 0% duty by default.
 */
void PWM_Timer1Init(u32 Copy_u32FreqHz, PWM1_ModeType Copy_Mode);

void PWM_Timer1EnableChannelA(void);
void PWM_Timer1EnableChannelB(void);
void PWM_Timer1DisableChannelA(void);   /* OC1A disconnected, PD5 freed  */
void PWM_Timer1DisableChannelB(void);   /* OC1B disconnected, PD4 freed  */

void PWM_Timer1SetDutyA(u8 DutyPercent);    /* 0 - 100 % of TOP  */
void PWM_Timer1SetDutyB(u8 DutyPercent);    /* 0 - 100 % of TOP  */
void PWM_Timer1SetDutyRawA(u16 Raw);       /* 0 - TOP (ticks)   */
void PWM_Timer1SetDutyRawB(u16 Raw);       /* 0 - TOP (ticks)   */

u16  PWM_Timer1GetTop(void);   /* current ICR1 (resolution) value        */
void PWM_Timer1Stop(void);

#endif /* PWM_INTERFACE_H_ */
