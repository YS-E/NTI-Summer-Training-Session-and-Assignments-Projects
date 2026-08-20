#ifndef BUTTON_CONFIG_H_
#define BUTTON_CONFIG_H_

#include "../../MCAL/DIO/DIO_Interface.h"

/* 1. Define Option Values First */
#define BUTTON_PULL_DOWN         1U
#define BUTTON_PULL_UP           0U

#define BUTTON_ACTIVE_LOW        0U  /* Pin connected to GND when pressed */
#define BUTTON_ACTIVE_HIGH       1U  /* Pin connected to VCC when pressed */

/* 2. Select Your Configurations */
#define BUTTON_PULL_TYPE         BUTTON_PULL_DOWN
#define BUTTON_ACTIVE_STATE      BUTTON_ACTIVE_HIGH

#endif /* BUTTON_CONFIG_H_ */