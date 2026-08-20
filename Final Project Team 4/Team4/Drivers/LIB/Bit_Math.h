// File guard
// disallows compiler to include this multiple times from more than one file
// to prevent any redefinition errors
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

// Bit Math
#define SET_BIT(REG, BIT)   ((REG) |=  (1U << (BIT)))
#define CLR_BIT(REG, BIT)   ((REG) &= ~(1U << (BIT)))
#define TOG_BIT(REG, BIT)   ((REG) ^=  (1U << (BIT)))
#define GET_BIT(REG, BIT)   (((REG) >> (BIT)) & 1U)

// the end of the file guard
#endif
