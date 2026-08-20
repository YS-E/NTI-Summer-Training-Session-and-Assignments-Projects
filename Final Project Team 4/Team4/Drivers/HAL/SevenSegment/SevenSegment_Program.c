#include "SevenSegment_Config.h"
#include "SevenSegment_Private.h"
#include "SevenSegment_Interface.h"

static const u8 SevenSeg_Ports[SEVENSEG_NUM_PINS] = {
	SEVENSEG_A_PORT, SEVENSEG_B_PORT, SEVENSEG_C_PORT, SEVENSEG_D_PORT,
	SEVENSEG_E_PORT, SEVENSEG_F_PORT, SEVENSEG_G_PORT
	#if (SEVENSEG_USE_DP == 1U)
	, SEVENSEG_DP_PORT
	#endif
};

static const u8 SevenSeg_Pins[SEVENSEG_NUM_PINS] = {
	SEVENSEG_A_PIN, SEVENSEG_B_PIN, SEVENSEG_C_PIN, SEVENSEG_D_PIN,
	SEVENSEG_E_PIN, SEVENSEG_F_PIN, SEVENSEG_G_PIN
	#if (SEVENSEG_USE_DP == 1U)
	, SEVENSEG_DP_PIN
	#endif
};

static const u8 SevenSeg_LUT[16] = {
	0x3F, /* 0 */  0x06, /* 1 */  0x5B, /* 2 */  0x4F, /* 3 */
	0x66, /* 4 */  0x6D, /* 5 */  0x7D, /* 6 */  0x07, /* 7 */
	0x7F, /* 8 */  0x6F, /* 9 */  0x77, /* A */  0x7C, /* b */
	0x39, /* C */  0x5E, /* d */  0x79, /* E */  0x71  /* F */
};

void SevenSeg_Init(void) {
	u8 i;
	for (i = 0; i < SEVENSEG_NUM_PINS; i++) {
		DIO_SetPinDirection(SevenSeg_Ports[i], SevenSeg_Pins[i], DIO_OUTPUT);
	}
	SevenSeg_Clear();
}

void SevenSeg_Clear(void) {
	u8 i;
	u8 OffState = (SEVENSEG_TYPE == SEVENSEG_COMMON_ANODE) ? DIO_HIGH : DIO_LOW;

	for (i = 0; i < SEVENSEG_NUM_PINS; i++) {
		DIO_SetPinValue(SevenSeg_Ports[i], SevenSeg_Pins[i], OffState);
	}
}

#if (SEVENSEG_USE_DP == 1U)
void SevenSeg_SetDP(u8 State) {
	u8 PinVal = State;

	#if (SEVENSEG_TYPE == SEVENSEG_COMMON_ANODE)
	PinVal = !PinVal;
	#endif

	DIO_SetPinValue(SEVENSEG_DP_PORT, SEVENSEG_DP_PIN,
	(PinVal != 0U) ? DIO_HIGH : DIO_LOW);
}
#endif

void SevenSeg_WriteNumber(u8 Number) {
	u8 Index = 0xFF;
	u8 Pattern;
	u8 BitVal;
	u8 i;

	if (Number <= 15) {
		Index = Number;
		} else if (Number >= '0' && Number <= '9') {
		Index = Number - '0';
		} else if (Number >= 'A' && Number <= 'F') {
		Index = Number - 'A' + 10;
		} else if (Number >= 'a' && Number <= 'f') {
		Index = Number - 'a' + 10;
	}

	if (Index > 15) {
		SevenSeg_Clear();
		return;
	}

	Pattern = SevenSeg_LUT[Index];

	#if (SEVENSEG_TYPE == SEVENSEG_COMMON_ANODE)
	Pattern = ~Pattern;
	#endif

	for (i = 0; i < 7; i++) {
		BitVal = (Pattern >> i) & 0x01U;
		DIO_SetPinValue(SevenSeg_Ports[i], SevenSeg_Pins[i],
		(BitVal != 0U) ? DIO_HIGH : DIO_LOW);
	}
}