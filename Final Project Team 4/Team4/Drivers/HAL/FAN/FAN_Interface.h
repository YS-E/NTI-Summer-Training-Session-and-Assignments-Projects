#ifndef FAN_INTERFACE_H_
#define FAN_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/* Fan Timer / PWM Channel Selector */
typedef enum
{
    FAN_CHANNEL_TIMER0_OC0,     /* PB3 */
    FAN_CHANNEL_TIMER1_OC1A,    /* PD5 */
    FAN_CHANNEL_TIMER1_OC1B,    /* PD4 */
    FAN_CHANNEL_TIMER2_OC2      /* PD7 */
} FAN_ChannelType;

/* Fan State */
typedef enum
{
    FAN_STATE_OFF = 0,
    FAN_STATE_ON  = 1
} FAN_StateType;

/* Discrete Fan Speed Presets */
typedef enum
{
    FAN_SPEED_OFF = 0,
    FAN_SPEED_LOW,
    FAN_SPEED_MED,
    FAN_SPEED_HIGH,
    FAN_SPEED_MAX
} FAN_SpeedLevelType;

/* Configuration structure for HAL initialization */
typedef struct
{
    FAN_ChannelType Channel;
    u32             Timer1FreqHz; /* Only used if Channel is TIMER1_OC1A or TIMER1_OC1B */
} FAN_ConfigType;

/* API Prototypes */
void FAN_Init(const FAN_ConfigType *pConfig);
void FAN_SetSpeed(const FAN_ConfigType *pConfig, u8 SpeedPercent);              /* Direct 0 - 100 % */
void FAN_SetSpeedLevel(const FAN_ConfigType *pConfig, FAN_SpeedLevelType Level); /* Stepped Presets */
void FAN_SetState(const FAN_ConfigType *pConfig, FAN_StateType State);
void FAN_Stop(const FAN_ConfigType *pConfig);

#endif /* FAN_INTERFACE_H_ */