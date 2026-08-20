#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Interface.h"

#include "SPI_Private.h"
#include "SPI_Interface.h"
#include "SPI_Config.h"

void SPI_Master_Init()
{
    /* Disable SPI Interrupt */
    CLR_BIT(SPCR, SPIE);
    
    /* Send LSB */
    SET_BIT(SPCR, DORD);	
    
    /* Master Mode */
    SET_BIT(SPCR, MSTR);	

    /* Clock Polarity & Phase */
    CLR_BIT(SPCR, CPOL);
    CLR_BIT(SPCR, CPHA);

    /* Select Fcpu/16 */
    SET_BIT(SPCR, SPR0);
    CLR_BIT(SPCR, SPR1);				
    CLR_BIT(SPSR, SPI2X);
        
    /* Pin Configuration for Master: MOSI (PB5), SCK (PB7), SS (PB4) -> Output | MISO (PB6) -> Input */
    DIO_voidSetPinDirection(PORTB_ID, PIN5, PIN_OUTPUT);		
    DIO_voidSetPinDirection(PORTB_ID, PIN7, PIN_OUTPUT);		
    DIO_voidSetPinDirection(PORTB_ID, PIN4, PIN_OUTPUT);
	
    DIO_voidSetPinDirection(PORTB_ID, PIN6, PIN_INPUT);
            
    /* Enable SPI */
    SET_BIT(SPCR, SPE);	
}

void SPI_Slave_Init()
{
    /* Disable SPI Interrupt */
    CLR_BIT(SPCR, SPIE);
    
    /* Send LSB */
    SET_BIT(SPCR, DORD);
    
    /* Slave Mode */
    CLR_BIT(SPCR, MSTR);
    
    /* Clock Polarity & Phase */
    CLR_BIT(SPCR, CPOL);
    CLR_BIT(SPCR, CPHA);

    /* Pin Configuration for Slave: MISO (PB6) -> Output | MOSI (PB5), SCK (PB7), SS (PB4) -> Input */
    DIO_voidSetPinDirection(PORTB_ID, PIN6, PIN_OUTPUT);
	
    DIO_voidSetPinDirection(PORTB_ID, PIN7, PIN_INPUT);
    DIO_voidSetPinDirection(PORTB_ID, PIN4, PIN_INPUT);
    DIO_voidSetPinDirection(PORTB_ID, PIN5, PIN_INPUT);
    
    /* Enable SPI */
    SET_BIT(SPCR, SPE);
}

void SPI_Send_Data(u8 spi_data)
{
    SPDR = spi_data;
    while(GET_BIT(SPSR, SPIF) == 0);
}

u8 SPI_Read_Data(void)
{
    while(GET_BIT(SPSR, SPIF) == 0);
    return SPDR;
}