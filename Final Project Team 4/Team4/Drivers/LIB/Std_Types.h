// File guard
// disallows compiler to include this multiple times from more than one file
// to prevent any redefinition errors
#ifndef STD_TYPES_H_
#define STD_TYPES_H_


// Machine Independent types
// Unsigned, Signed, Floating pointer
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef float    f32;
typedef double   f64;

// NULL Address
#define NULL ( (void *) 0x00)

// the end of the file guard
#endif