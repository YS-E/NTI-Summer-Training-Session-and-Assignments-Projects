/*
 * SPI_Private.h
 *
 * Created: 6/30/2023 7:25:52 PM
 *  Author: Rizk
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPIE 7
#define SPE  6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

#define SPIF  7
#define WCOL  6
#define SPI2X 0


#define SPCR *((volatile u8 *)0x2D)
#define SPSR *((volatile u8 *)0x2E)
#define SPDR *((volatile u8 *)0x2F)



#endif /* SPI_PRIVATE_H_ */