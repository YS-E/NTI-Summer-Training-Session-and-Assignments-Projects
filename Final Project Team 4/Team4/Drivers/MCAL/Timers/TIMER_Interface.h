#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/*
 * ============================================================================
 * Single Plain Timer Driver for ATmega32 - covers Timer0, Timer1, Timer2
 * (Normal mode only - NOT for PWM)
 * ----------------------------------------------------------------------------
 * Separate driver from PWM_Interface.h / PWM_Program.c. Whichever timer you
 * pick, this driver always leaves its WGMxx and COMxx bits at 0, so OC0
 * (PB3), OC1A (PD5), OC1B (PD4) and OC2 (PD7) are never touched and stay
 * free as normal I/O pins. Use the PWM driver instead if you need an actual
 * duty-cycle waveform - a given timer must not be driven by both drivers
 * at the same time, since they'd fight over the same physical hardware.
 *
 * No interrupts are used anywhere in this driver (TOIEn is never set).
 * TIMER_IsOverflow() is a single non-blocking check meant to be polled
 * once per main-loop iteration - it never waits for the flag to be set.
 *
 * Timer0 and Timer2 are 8-bit (overflow every 256 ticks).
 * Timer1 is 16-bit (overflow every 65536 ticks).
 * ============================================================================
 */

typedef enum
{
	TIMER_0 = 0,
	TIMER_1 = 1,
	TIMER_2 = 2
}TIMER_IdType;

/*
 * u8Prescaler is the raw hardware clock-select value (0-7):
 *
 *   Value | Timer0 / Timer1 divisor | Timer2 divisor
 *   ------+--------------------------+-----------------
 *     0   | stopped                  | stopped
 *     1   | 1                        | 1
 *     2   | 8                        | 8
 *     3   | 64                       | 32
 *     4   | 256                      | 64
 *     5   | 1024                     | 128
 *     6   | (not implemented)        | 256
 *     7   | (not implemented)        | 1024
 *
 * (Timer0/Timer1 only implement values 0-5; Timer2 uses the full 0-7 range.)
 */

/* Configures the chosen timer in Normal mode and starts it counting immediately. */
void TIMER_Init(TIMER_IdType Timer, u8 u8Prescaler);

/* Stops the chosen timer (clock select = 000). Counter value is left as-is. */
void TIMER_Stop(TIMER_IdType Timer);

/* Direct access to the counter (8-bit timers only use the low byte of u16Count). */
void TIMER_SetCount(TIMER_IdType Timer, u16 u16Count);
u16  TIMER_GetCount(TIMER_IdType Timer);

/*
 * Non-blocking overflow check.
 * Returns 1 exactly once per hardware overflow of the chosen timer (and
 * clears its flag). Returns 0 immediately if no overflow has happened
 * since the last call - it never waits. Call this once per main-loop
 * iteration for each timer you are tracking.
 */
u8 TIMER_IsOverflow(TIMER_IdType Timer);

#endif /* TIMER_INTERFACE_H_ */
