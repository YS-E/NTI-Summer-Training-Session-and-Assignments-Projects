#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/* ============================== Timer0 (8-bit) ============================ */
#define TIMER_TCCR0    (*((volatile u8 *)0x53))
#define TIMER_TCNT0    (*((volatile u8 *)0x52))

#define TCCR0_WGM01    3
#define TCCR0_WGM00    6
#define TCCR0_COM01    5
#define TCCR0_COM00    4

/* ============================== Timer1 (16-bit) ============================ */
#define TIMER_TCCR1A   (*((volatile u8 *)0x4F))
#define TIMER_TCCR1B   (*((volatile u8 *)0x4E))
#define TIMER_TCNT1H   (*((volatile u8 *)0x4D))
#define TIMER_TCNT1L   (*((volatile u8 *)0x4C))

#define TCCR1A_COM1A1  7
#define TCCR1A_COM1A0  6
#define TCCR1A_COM1B1  5
#define TCCR1A_COM1B0  4
#define TCCR1A_WGM11   1
#define TCCR1A_WGM10   0

#define TCCR1B_WGM13   4
#define TCCR1B_WGM12   3

/* ============================== Timer2 (8-bit) ============================ */
#define TIMER_TCCR2    (*((volatile u8 *)0x45))
#define TIMER_TCNT2    (*((volatile u8 *)0x44))

#define TCCR2_WGM21    3
#define TCCR2_WGM20    6
#define TCCR2_COM21    5
#define TCCR2_COM20    4

/* ============================== Shared ===================================== */
#define TIMER_TIFR     (*((volatile u8 *)0x58))

#define TIFR_TOV0      0   /* Timer0 overflow flag bit inside TIFR */
#define TIFR_TOV1      2   /* Timer1 overflow flag bit inside TIFR */
#define TIFR_TOV2      6   /* Timer2 overflow flag bit inside TIFR */

/* Clock-select field mask (bits 2:0 of TCCR0 / TCCR1B / TCCR2) */
#define TIMER_CS_MASK  0xF8

#endif /* TIMER_PRIVATE_H_ */
