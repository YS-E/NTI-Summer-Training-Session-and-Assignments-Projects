/*
 * SPI_Interface.h
 *
 * Created: 6/30/2023 7:25:36 PM
 *  Author: Rizk
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_Master_Init();


void SPI_Slave_Init();


void SPI_Send_Data(u8 spi_data);


u8 SPI_Read_Data(void);



#endif /* SPI_INTERFACE_H_ */