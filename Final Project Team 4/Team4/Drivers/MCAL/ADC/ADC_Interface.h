#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../../LIB/Std_Types.h"
#include "ADC_Config.h"

/* Return Status Codes */
#define ADC_OK                     0U
#define ADC_NOT_OK                 1U
#define ADC_INVALID_PARAM          2U
#define ADC_NULL_POINTER           3U
#define ADC_BUSY_STATE             4U

/* Error Return Value for Direct Synchronous Reading */
#define ADC_READ_ERROR             0xFFFFU

/* Channel Definitions */
#define ADC_CHANNEL0               0U
#define ADC_CHANNEL1               1U
#define ADC_CHANNEL2               2U
#define ADC_CHANNEL3               3U
#define ADC_CHANNEL4               4U
#define ADC_CHANNEL5               5U
#define ADC_CHANNEL6               6U
#define ADC_CHANNEL7               7U

/**
 * @brief Initializes the ADC hardware according to ADC_Config.h
 * @return u8 Status Code
 */
u8 ADC_Init(void);

/**
 * @brief Selects active ADC input channel manually
 * @param Channel Target channel index (ADC_CHANNEL0 - ADC_CHANNEL7)
 * @return u8 Status Code
 */
u8 ADC_SelectChannel(u8 Channel);

/**
 * @brief Triggers conversion on currently active channel
 * @return u8 Status Code
 */
u8 ADC_StartConversion(void);

/**
 * @brief Synchronous (Blocking) Read with timeout protection
 * @param Channel Target channel index
 * @return u16 Digital result (0-1023) or ADC_READ_ERROR on failure
 */
u16 ADC_ReadValue(u8 Channel);

#if (ADC_INTERRUPT_FEATURE == ENABLED)
/**
 * @brief Asynchronous (Non-Blocking) Read using Interrupts and Callback (ONCE)
 * @param Channel Target channel index
 * @param Result Pointer to memory where result will be saved when conversion finishes
 * @param NotificationFunc Pointer to callback function executed on completion
 * @return u8 Status Code
 */
u8 ADC_ReadValueAsync(u8 Channel, u16 *Result, void (*NotificationFunc)(void));
#endif

#endif /* ADC_INTERFACE_H_ */