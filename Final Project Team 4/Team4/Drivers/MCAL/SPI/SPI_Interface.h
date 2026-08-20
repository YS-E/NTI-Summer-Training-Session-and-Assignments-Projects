#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_InitMaster(void);
void SPI_InitSlave(void);

/* Slave Select Management */
void SPI_SelectSlave(u8 port, u8 pin);
void SPI_DeselectSlave(u8 port, u8 pin);

/* Standard Byte Transfer */
void SPI_Transmit(u8 value);
u8 SPI_Receive(void);
u8 SPI_Transceive(u8 value);

/* Integrated SS + Transfer Functions */
void SPI_TransmitToSlave(u8 port, u8 pin, u8 value);
u8 SPI_TransceiveWithSlave(u8 port, u8 pin, u8 value);

#endif /* SPI_INTERFACE_H_ */