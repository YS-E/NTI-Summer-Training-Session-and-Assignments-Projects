#ifndef SEVENSEG_CONFIG_H_
#define SEVENSEG_CONFIG_H_

#include "../../MCAL/DIO/DIO_Interface.h"

/* Display Polarity Configuration */
#define SEVENSEG_COMMON_CATHODE    1U
#define SEVENSEG_COMMON_ANODE      0U
#define SEVENSEG_TYPE              SEVENSEG_COMMON_CATHODE

/* Feature Switch for Decimal Point */
#define SEVENSEG_USE_DP            0U

/* Hardware Pin Mappings */
#define SEVENSEG_A_PORT            PORTC_ID
#define SEVENSEG_A_PIN             PIN0

#define SEVENSEG_B_PORT            PORTC_ID
#define SEVENSEG_B_PIN             PIN1

#define SEVENSEG_C_PORT            PORTC_ID
#define SEVENSEG_C_PIN             PIN2

#define SEVENSEG_D_PORT            PORTC_ID
#define SEVENSEG_D_PIN             PIN3

#define SEVENSEG_E_PORT            PORTC_ID
#define SEVENSEG_E_PIN             PIN4

#define SEVENSEG_F_PORT            PORTC_ID
#define SEVENSEG_F_PIN             PIN5

#define SEVENSEG_G_PORT            PORTC_ID
#define SEVENSEG_G_PIN             PIN6

#if (SEVENSEG_USE_DP == 1U)
#define SEVENSEG_DP_PORT           PORTC_ID
#define SEVENSEG_DP_PIN            PIN7
#endif

#endif /* SEVENSEG_CONFIG_H_ */