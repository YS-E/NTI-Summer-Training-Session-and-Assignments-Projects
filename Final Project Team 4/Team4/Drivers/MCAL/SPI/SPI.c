#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
#include "../DIO/DIO_Interface.h"

#include "SPI_Private.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"

void SPI_InitMaster(void)
{
	/* Configure Data Order */
	#if SPI_DATA_ORDER == SPI_LSB_FIRST
	SET_BIT(SPCR, DORD);
	#else
	CLR_BIT(SPCR, DORD);
	#endif

	/* Configure Clock Polarity */
	#if SPI_CLOCK_POLARITY == SPI_IDLE_HIGH
	SET_BIT(SPCR, CPOL);
	#else
	CLR_BIT(SPCR, CPOL);
	#endif

	/* Configure Clock Phase */
	#if SPI_CLOCK_PHASE == SPI_SAMPLE_TRAILING
	SET_BIT(SPCR, CPHA);
	#else
	CLR_BIT(SPCR, CPHA);
	#endif

	/* Configure Clock Rate Prescaler */
	#if SPI_CLOCK_RATE == SPI_PRESCALER_4
	CLR_BIT(SPCR, SPR0); CLR_BIT(SPCR, SPR1); CLR_BIT(SPSR, SPI2X);
	#elif SPI_CLOCK_RATE == SPI_PRESCALER_16
	SET_BIT(SPCR, SPR0); CLR_BIT(SPCR, SPR1); CLR_BIT(SPSR, SPI2X);
	#elif SPI_CLOCK_RATE == SPI_PRESCALER_64
	CLR_BIT(SPCR, SPR0); SET_BIT(SPCR, SPR1); CLR_BIT(SPSR, SPI2X);
	#elif SPI_CLOCK_RATE == SPI_PRESCALER_128
	SET_BIT(SPCR, SPR0); SET_BIT(SPCR, SPR1); CLR_BIT(SPSR, SPI2X);
	#elif SPI_CLOCK_RATE == SPI_PRESCALER_2
	CLR_BIT(SPCR, SPR0); CLR_BIT(SPCR, SPR1); SET_BIT(SPSR, SPI2X);
	#elif SPI_CLOCK_RATE == SPI_PRESCALER_8
	SET_BIT(SPCR, SPR0); CLR_BIT(SPCR, SPR1); SET_BIT(SPSR, SPI2X);
	#elif SPI_CLOCK_RATE == SPI_PRESCALER_32
	CLR_BIT(SPCR, SPR0); SET_BIT(SPCR, SPR1); SET_BIT(SPSR, SPI2X);
	#endif

	/* Enable Master Mode */
	SET_BIT(SPCR, MSTR);

	/* Setup Master Pins (PB4: SS, PB5: MOSI, PB6: MISO, PB7: SCK) */
	DIO_SetPinDirection(SPI_DEFAULT_SS_PORT, SPI_DEFAULT_SS_PIN, DIO_OUTPUT);
	DIO_SetPinValue(SPI_DEFAULT_SS_PORT, SPI_DEFAULT_SS_PIN, DIO_HIGH); /* Deselect initially */

	DIO_SetPinDirection(PORTB_ID, PIN5, DIO_OUTPUT);
	DIO_SetPinDirection(PORTB_ID, PIN6, DIO_INPUT);
	DIO_SetPinDirection(PORTB_ID, PIN7, DIO_OUTPUT);

	/* Enable Peripheral */
	SET_BIT(SPCR, SPE);
}

void SPI_InitSlave(void)
{
	/* Configure Data Order */
	#if SPI_DATA_ORDER == SPI_LSB_FIRST
	SET_BIT(SPCR, DORD);
	#else
	CLR_BIT(SPCR, DORD);
	#endif

	/* Configure Clock Polarity */
	#if SPI_CLOCK_POLARITY == SPI_IDLE_HIGH
	SET_BIT(SPCR, CPOL);
	#else
	CLR_BIT(SPCR, CPOL);
	#endif

	/* Configure Clock Phase */
	#if SPI_CLOCK_PHASE == SPI_SAMPLE_TRAILING
	SET_BIT(SPCR, CPHA);
	#else
	CLR_BIT(SPCR, CPHA);
	#endif

	/* Enable Slave Mode */
	CLR_BIT(SPCR, MSTR);

	/* Setup Slave Pins (PB4: SS, PB5: MOSI, PB6: MISO, PB7: SCK) */
	DIO_SetPinDirection(PORTB_ID, PIN4, DIO_INPUT);
	DIO_SetPinDirection(PORTB_ID, PIN5, DIO_INPUT);
	DIO_SetPinDirection(PORTB_ID, PIN6, DIO_OUTPUT);
	DIO_SetPinDirection(PORTB_ID, PIN7, DIO_INPUT);

	/* Enable Peripheral */
	SET_BIT(SPCR, SPE);
}

void SPI_SelectSlave(u8 port, u8 pin)
{
	DIO_SetPinDirection(port, pin, DIO_OUTPUT);
	DIO_SetPinValue(port, pin, DIO_LOW);
}

void SPI_DeselectSlave(u8 port, u8 pin)
{
	DIO_SetPinDirection(port, pin, DIO_OUTPUT);
	DIO_SetPinValue(port, pin, DIO_HIGH);
}

void SPI_Transmit(u8 value)
{
	SPDR = value;
	while (GET_BIT(SPSR, SPIF) == 0);
}

u8 SPI_Receive(void)
{
	while (GET_BIT(SPSR, SPIF) == 0);
	return SPDR;
}

u8 SPI_Transceive(u8 value)
{
	SPDR = value;
	while (GET_BIT(SPSR, SPIF) == 0);
	return SPDR;
}

void SPI_TransmitToSlave(u8 port, u8 pin, u8 value)
{
	SPI_SelectSlave(port, pin);
	SPI_Transmit(value);
	SPI_DeselectSlave(port, pin);
}

u8 SPI_TransceiveWithSlave(u8 port, u8 pin, u8 value)
{
	u8 receivedData = 0;
	SPI_SelectSlave(port, pin);
	receivedData = SPI_Transceive(value);
	SPI_DeselectSlave(port, pin);
	return receivedData;
}