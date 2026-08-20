#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/* Hardware Register Definitions */
#define SPCR    (*((volatile u8 *)0x2D))
#define SPSR    (*((volatile u8 *)0x2E))
#define SPDR    (*((volatile u8 *)0x2F))

/* SPCR Control Register Bits */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

/* SPSR Status Register Bits */
#define SPIF    7
#define WCOL    6
#define SPI2X   0

/* Configuration Constants */
#define SPI_MSB_FIRST           0
#define SPI_LSB_FIRST           1

#define SPI_IDLE_LOW            0
#define SPI_IDLE_HIGH           1

#define SPI_SAMPLE_LEADING      0
#define SPI_SAMPLE_TRAILING     1

#define SPI_PRESCALER_4         0
#define SPI_PRESCALER_16        1
#define SPI_PRESCALER_64        2
#define SPI_PRESCALER_128       3
#define SPI_PRESCALER_2         4
#define SPI_PRESCALER_8         5
#define SPI_PRESCALER_32        6

#endif /* SPI_PRIVATE_H_ */