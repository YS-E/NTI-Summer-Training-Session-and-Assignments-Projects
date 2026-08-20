#include "../../LIB/Std_Types.h"
#include "../../MCAL/PWM/PWM_Interface.h"
#include "FAN_Config.h"
#include "FAN_Interface.h"

void FAN_Init(const FAN_ConfigType *pConfig)
{
    if(pConfig == NULL)
    {
        return;
    }

    switch(pConfig->Channel)
    {
        case FAN_CHANNEL_TIMER0_OC0:
            /* Timer0: Fast PWM with prescaler 64 (~488 Hz at 8MHz) */
            PWM_Timer0Init(PWM_MODE_FAST, PWM_PRESCALER_64);
            PWM_Timer0SetDuty(FAN_SPEED_OFF_DUTY);
            break;

        case FAN_CHANNEL_TIMER1_OC1A:
        case FAN_CHANNEL_TIMER1_OC1B:
            /* Timer1: Custom frequency Fast PWM (TOP = ICR1) */
            PWM_Timer1Init(pConfig->Timer1FreqHz, PWM1_MODE_FAST);
            if(pConfig->Channel == FAN_CHANNEL_TIMER1_OC1A)
            {
                PWM_Timer1EnableChannelA();
                PWM_Timer1SetDutyA(FAN_SPEED_OFF_DUTY);
            }
            else
            {
                PWM_Timer1EnableChannelB();
                PWM_Timer1SetDutyB(FAN_SPEED_OFF_DUTY);
            }
            break;

        case FAN_CHANNEL_TIMER2_OC2:
            /* Timer2: Fast PWM with prescaler 64 (~488 Hz at 8MHz) */
            PWM_Timer2Init(PWM_MODE_FAST, PWM2_PRESCALER_64);
            PWM_Timer2SetDuty(FAN_SPEED_OFF_DUTY);
            break;

        default:
            break;
    }
}

void FAN_SetSpeed(const FAN_ConfigType *pConfig, u8 SpeedPercent)
{
    if(pConfig == NULL)
    {
        return;
    }

    if(SpeedPercent > 100)
    {
        SpeedPercent = 100;
    }

    switch(pConfig->Channel)
    {
        case FAN_CHANNEL_TIMER0_OC0:
            PWM_Timer0SetDuty(SpeedPercent);
            break;

        case FAN_CHANNEL_TIMER1_OC1A:
            PWM_Timer1SetDutyA(SpeedPercent);
            break;

        case FAN_CHANNEL_TIMER1_OC1B:
            PWM_Timer1SetDutyB(SpeedPercent);
            break;

        case FAN_CHANNEL_TIMER2_OC2:
            PWM_Timer2SetDuty(SpeedPercent);
            break;

        default:
            break;
    }
}

void FAN_SetSpeedLevel(const FAN_ConfigType *pConfig, FAN_SpeedLevelType Level)
{
    u8 Duty = FAN_SPEED_OFF_DUTY;

    switch(Level)
    {
        case FAN_SPEED_OFF:
            Duty = FAN_SPEED_OFF_DUTY;
            break;

        case FAN_SPEED_LOW:
            Duty = FAN_SPEED_LOW_DUTY;
            break;

        case FAN_SPEED_MED:
            Duty = FAN_SPEED_MED_DUTY;
            break;

        case FAN_SPEED_HIGH:
            Duty = FAN_SPEED_HIGH_DUTY;
            break;

        case FAN_SPEED_MAX:
            Duty = FAN_SPEED_MAX_DUTY;
            break;

        default:
            Duty = FAN_SPEED_OFF_DUTY;
            break;
    }

    FAN_SetSpeed(pConfig, Duty);
}

void FAN_SetState(const FAN_ConfigType *pConfig, FAN_StateType State)
{
    if(State == FAN_STATE_OFF)
    {
        FAN_SetSpeedLevel(pConfig, FAN_SPEED_OFF);
    }
    else
    {
        FAN_SetSpeedLevel(pConfig, FAN_SPEED_MAX);
    }
}

void FAN_Stop(const FAN_ConfigType *pConfig)
{
    if(pConfig == NULL)
    {
        return;
    }

    FAN_SetSpeedLevel(pConfig, FAN_SPEED_OFF);

    switch(pConfig->Channel)
    {
        case FAN_CHANNEL_TIMER0_OC0:
            PWM_Timer0Stop();
            break;

        case FAN_CHANNEL_TIMER1_OC1A:
            PWM_Timer1DisableChannelA();
            break;

        case FAN_CHANNEL_TIMER1_OC1B:
            PWM_Timer1DisableChannelB();
            break;

        case FAN_CHANNEL_TIMER2_OC2:
            PWM_Timer2Stop();
            break;

        default:
            break;
    }
}