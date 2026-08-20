#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/* Feature Switch Values */
#define ENABLED                    1U
#define DISABLED                   0U

/* Register Hardware Addresses */
#define ADMUX                      (*(volatile u8  *)0x27)
#define ADCSRA                     (*(volatile u8  *)0x26)
#define ADCH                       (*(volatile u8  *)0x25)
#define ADCL                       (*(volatile u8  *)0x24)
#define SFIOR                      (*(volatile u8  *)0x50)
#define ADC_DATA_REG               (*(volatile u16 *)0x24)

/* ADMUX Bit Positions */
#define ADMUX_REFS1                7U
#define ADMUX_REFS0                6U
#define ADMUX_ADLAR                5U

/* ADCSRA Bit Positions */
#define ADCSRA_ADEN                7U
#define ADCSRA_ADSC                6U
#define ADCSRA_ADATE               5U
#define ADCSRA_ADIF                4U
#define ADCSRA_ADIE                3U

/* Reference Voltage Options */
#define ADC_VREF_AREF              0U
#define ADC_VREF_AVCC              1U
#define ADC_VREF_INTERNAL_2_56V    3U

/* Adjust Options */
#define ADC_RIGHT_ADJUST           0U
#define ADC_LEFT_ADJUST            1U

/* Prescaler Options */
#define ADC_PRESCALER_2            1U
#define ADC_PRESCALER_4            2U
#define ADC_PRESCALER_8            3U
#define ADC_PRESCALER_16           4U
#define ADC_PRESCALER_32           5U
#define ADC_PRESCALER_64           6U
#define ADC_PRESCALER_128          7U

/* Bit Masks */
#define ADC_CHANNEL_MASK           0xE0U
#define ADC_PRESCALER_MASK         0xF8U

/* ADC Conversion Complete Vector Attribute */
#if (ADC_INTERRUPT_FEATURE == ENABLED)
void __vector_16(void) __attribute__((signal));
#endif

#endif /* ADC_PRIVATE_H_ */