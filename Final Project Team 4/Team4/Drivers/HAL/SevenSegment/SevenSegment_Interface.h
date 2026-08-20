#ifndef SEVENSEG_INTERFACE_H_
#define SEVENSEG_INTERFACE_H_

#include "../../LIB/Std_Types.h"
#include "SevenSegment_Config.h"

/* Prototypes */
void SevenSeg_Init(void);
void SevenSeg_WriteNumber(u8 Number);
void SevenSeg_Clear(void);

#if (SEVENSEG_USE_DP == 1U)
void SevenSeg_SetDP(u8 State);
#endif

#endif /* SEVENSEG_INTERFACE_H_ */