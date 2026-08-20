#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/**
 * @brief Select ADC Voltage Reference
 *        Options:
 *          - ADC_VREF_AREF
 *          - ADC_VREF_AVCC
 *          - ADC_VREF_INTERNAL_2_56V
 */
#define ADC_VREF_SELECTION         ADC_VREF_AVCC

/**
 * @brief Select Data Alignment Mode
 *        Options:
 *          - ADC_RIGHT_ADJUST
 *          - ADC_LEFT_ADJUST
 */
#define ADC_ADJUST_SELECTION       ADC_RIGHT_ADJUST

/**
 * @brief Select ADC Prescaler Division Factor
 *        Options:
 *          - ADC_PRESCALER_2
 *          - ADC_PRESCALER_4
 *          - ADC_PRESCALER_8
 *          - ADC_PRESCALER_16
 *          - ADC_PRESCALER_32
 *          - ADC_PRESCALER_64
 *          - ADC_PRESCALER_128
 */
#define ADC_PRESCALER_SELECTION    ADC_PRESCALER_64

/**
 * @brief Enable or Disable Interrupt (Asynchronous) Feature
 *        Options:
 *          - ENABLED
 *          - DISABLED
 */
#define ADC_INTERRUPT_FEATURE      ENABLED

/**
 * @brief Polling Timeout Limit for synchronous read safety
 */
#define ADC_TIMEOUT_LIMIT          50000UL

#endif /* ADC_CONFIG_H_ */