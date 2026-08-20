#ifndef PWM_PRIVATE_H_
#define PWM_PRIVATE_H_

#include "../../LIB/Std_Types.h"

/* ============================== Timer0 ================================= */
#define PWM_TCCR0      (*((volatile u8 *)0x53))
#define PWM_TCNT0      (*((volatile u8 *)0x52))
#define PWM_OCR0       (*((volatile u8 *)0x5C))

#define TCCR0_FOC0     7
#define TCCR0_WGM00    6
#define TCCR0_COM01    5
#define TCCR0_COM00    4
#define TCCR0_WGM01    3
#define TCCR0_CS02     2
#define TCCR0_CS01     1
#define TCCR0_CS00     0

/* ============================== Timer1 ================================= */
#define PWM_TCCR1A     (*((volatile u8 *)0x4F))
#define PWM_TCCR1B     (*((volatile u8 *)0x4E))
#define PWM_TCNT1H     (*((volatile u8 *)0x4D))
#define PWM_TCNT1L     (*((volatile u8 *)0x4C))
#define PWM_OCR1AH     (*((volatile u8 *)0x4B))
#define PWM_OCR1AL     (*((volatile u8 *)0x4A))
#define PWM_OCR1BH     (*((volatile u8 *)0x49))
#define PWM_OCR1BL     (*((volatile u8 *)0x48))
#define PWM_ICR1H      (*((volatile u8 *)0x47))
#define PWM_ICR1L      (*((volatile u8 *)0x46))

#define TCCR1A_COM1A1  7
#define TCCR1A_COM1A0  6
#define TCCR1A_COM1B1  5
#define TCCR1A_COM1B0  4
#define TCCR1A_FOC1A   3
#define TCCR1A_FOC1B   2
#define TCCR1A_WGM11   1
#define TCCR1A_WGM10   0

#define TCCR1B_ICNC1   7
#define TCCR1B_ICES1   6
#define TCCR1B_WGM13   4
#define TCCR1B_WGM12   3
#define TCCR1B_CS12    2
#define TCCR1B_CS11    1
#define TCCR1B_CS10    0

/* ============================== Timer2 ================================= */
#define PWM_TCCR2      (*((volatile u8 *)0x45))
#define PWM_TCNT2      (*((volatile u8 *)0x44))
#define PWM_OCR2       (*((volatile u8 *)0x43))

#define TCCR2_FOC2     7
#define TCCR2_WGM20    6
#define TCCR2_COM21    5
#define TCCR2_COM20    4
#define TCCR2_WGM21    3
#define TCCR2_CS22     2
#define TCCR2_CS21     1
#define TCCR2_CS20     0

/* =========================== Port Registers ============================ */
/* OC0 -> PB3 , OC1A -> PD5 , OC1B -> PD4 , OC2 -> PD7 */
#define PWM_DDRB       (*((volatile u8 *)0x37))
#define PWM_DDRD       (*((volatile u8 *)0x31))

#define PWM_OC0_PIN    3
#define PWM_OC1A_PIN   5
#define PWM_OC1B_PIN   4
#define PWM_OC2_PIN    7

/* Clock-select field mask (bits 2:0 of TCCRn / TCCR1B) */
#define PWM_CS_MASK    0xF8

#endif /* PWM_PRIVATE_H_ */
