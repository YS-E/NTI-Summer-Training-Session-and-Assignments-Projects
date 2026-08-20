#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* Data Order: SPI_MSB_FIRST, SPI_LSB_FIRST */
#define SPI_DATA_ORDER          SPI_MSB_FIRST

/* Clock Polarity: SPI_IDLE_LOW, SPI_IDLE_HIGH */
#define SPI_CLOCK_POLARITY      SPI_IDLE_LOW

/* Clock Phase: SPI_SAMPLE_LEADING, SPI_SAMPLE_TRAILING */
#define SPI_CLOCK_PHASE         SPI_SAMPLE_LEADING

/* Clock Rate Prescaler (Master Mode Only) */
#define SPI_CLOCK_RATE          SPI_PRESCALER_16

/* Default Hardware SS Pin Configuration */
#define SPI_DEFAULT_SS_PORT     PORTB_ID
#define SPI_DEFAULT_SS_PIN      PIN4

#endif /* SPI_CONFIG_H_ */