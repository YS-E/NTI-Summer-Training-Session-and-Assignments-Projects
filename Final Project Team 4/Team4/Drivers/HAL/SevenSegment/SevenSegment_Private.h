#ifndef SEVENSEG_PRIVATE_H_
#define SEVENSEG_PRIVATE_H_

#include "../../LIB/Std_Types.h"
#include "SevenSegment_Config.h"

#if (SEVENSEG_USE_DP == 1U)
#define SEVENSEG_NUM_PINS   8U
#else
#define SEVENSEG_NUM_PINS   7U
#endif

#endif /* SEVENSEG_PRIVATE_H_ */