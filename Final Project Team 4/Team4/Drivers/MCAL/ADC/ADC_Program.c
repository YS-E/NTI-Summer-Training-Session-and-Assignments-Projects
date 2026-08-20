#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "ADC_Private.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"

#if (ADC_INTERRUPT_FEATURE == ENABLED)
/* Private State Variables for Interrupt Handling */
static u16 *ADC_pAsyncResult = NULL;
static void (*ADC_pNotificationFunc)(void) = NULL;
static u8 ADC_BusyFlag = 0U;
#endif

u8 ADC_Init(void)
{
	/* 1. Configure Voltage Reference */
	#if (ADC_VREF_SELECTION == ADC_VREF_AREF)
	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);
	#elif (ADC_VREF_SELECTION == ADC_VREF_AVCC)
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);
	#elif (ADC_VREF_SELECTION == ADC_VREF_INTERNAL_2_56V)
	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);
	#else
	#error "Invalid ADC_VREF_SELECTION configured!"
	#endif

	/* 2. Configure Data Presentation */
	#if (ADC_ADJUST_SELECTION == ADC_RIGHT_ADJUST)
	CLR_BIT(ADMUX, ADMUX_ADLAR);
	#elif (ADC_ADJUST_SELECTION == ADC_LEFT_ADJUST)
	SET_BIT(ADMUX, ADMUX_ADLAR);
	#else
	#error "Invalid ADC_ADJUST_SELECTION configured!"
	#endif

	/* 3. Configure Prescaler */
	ADCSRA = (ADCSRA & ADC_PRESCALER_MASK) | ADC_PRESCALER_SELECTION;

	/* 4. Clear Interrupt Flag & Disable Interrupts initially */
	SET_BIT(ADCSRA, ADCSRA_ADIF);
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/* 5. Enable ADC Module */
	SET_BIT(ADCSRA, ADCSRA_ADEN);

	return ADC_OK;
}

u8 ADC_SelectChannel(u8 Channel)
{
	u8 ErrorStatus = ADC_OK;

	if (Channel <= ADC_CHANNEL7)
	{
		ADMUX = (ADMUX & ADC_CHANNEL_MASK) | Channel;
	}
	else
	{
		ErrorStatus = ADC_INVALID_PARAM;
	}

	return ErrorStatus;
}

u8 ADC_StartConversion(void)
{
	SET_BIT(ADCSRA, ADCSRA_ADSC);
	return ADC_OK;
}

u16 ADC_ReadValue(u8 Channel)
{
	u16 DigitalResult = ADC_READ_ERROR;
	u32 TimeoutCounter = 0U;

	if (Channel <= ADC_CHANNEL7)
	{
		/* Select channel */
		ADMUX = (ADMUX & ADC_CHANNEL_MASK) | Channel;

		/* Start conversion */
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/* Wait with timeout protection */
		while ((GET_BIT(ADCSRA, ADCSRA_ADIF) == 0U) && (TimeoutCounter < ADC_TIMEOUT_LIMIT))
		{
			TimeoutCounter++;
		}

		if (TimeoutCounter < ADC_TIMEOUT_LIMIT)
		{
			/* Clear Flag */
			SET_BIT(ADCSRA, ADCSRA_ADIF);

			/* Read result register */
			#if (ADC_ADJUST_SELECTION == ADC_RIGHT_ADJUST)
			DigitalResult = ADC_DATA_REG;
			#elif (ADC_ADJUST_SELECTION == ADC_LEFT_ADJUST)
			DigitalResult = (u16)(ADCH << 2U) | (ADCL >> 6U);
			#endif
		}
	}

	return DigitalResult;
}

#if (ADC_INTERRUPT_FEATURE == ENABLED)
u8 ADC_ReadValueAsync(u8 Channel, u16 *Result, void (*NotificationFunc)(void))
{
	u8 ErrorStatus = ADC_OK;

	if ((Result == NULL) || (NotificationFunc == NULL))
	{
		ErrorStatus = ADC_NULL_POINTER;
	}
	else if (Channel > ADC_CHANNEL7)
	{
		ErrorStatus = ADC_INVALID_PARAM;
	}
	else if (ADC_BusyFlag == 1U)
	{
		ErrorStatus = ADC_BUSY_STATE;
	}
	else
	{
		/* Lock state */
		ADC_BusyFlag = 1U;

		/* Store callback and result buffer */
		ADC_pAsyncResult = Result;
		ADC_pNotificationFunc = NotificationFunc;

		/* Select Channel */
		ADMUX = (ADMUX & ADC_CHANNEL_MASK) | Channel;

		/* FIX 1: Clear any existing pending flag BEFORE enabling interrupts */
		SET_BIT(ADCSRA, ADCSRA_ADIF);

		/* Enable ADC Interrupt */
		SET_BIT(ADCSRA, ADCSRA_ADIE);

		/* Start Conversion */
		SET_BIT(ADCSRA, ADCSRA_ADSC);
		
	}

	return ErrorStatus;
}

/* ADC ISR */
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	u8 Local_u8Low  = ADCL;
	u8 Local_u8High = ADCH;

	if (ADC_pAsyncResult != NULL)
	{
		#if (ADC_ADJUST_SELECTION == ADC_RIGHT_ADJUST)
		*ADC_pAsyncResult = (u16)Local_u8Low | ((u16)Local_u8High << 8U);
		#elif (ADC_ADJUST_SELECTION == ADC_LEFT_ADJUST)
		*ADC_pAsyncResult = (u16)(Local_u8High << 2U) | (Local_u8Low >> 6U);
		#endif
	}

	CLR_BIT(ADCSRA, ADCSRA_ADIE);
	ADC_BusyFlag = 0U;

	if (ADC_pNotificationFunc != NULL)
	{
		ADC_pNotificationFunc();
	}
}
#endif