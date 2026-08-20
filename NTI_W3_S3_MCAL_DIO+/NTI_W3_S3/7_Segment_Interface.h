/*
 * 7_Segment_Interface.h
 *
 * Created: 7/18/2023 7:05:06 PM
 *  Author: Rizk
 */ 


#ifndef SEGMENT_INTERFACE_H_
#define SEGMENT_INTERFACE_H_

#define ZERO  0x00
#define ONE   0x01
#define TWO   0x02
#define THREE 0x03
#define FOUR  0x04


void HAL_7SEGMENT_INIT(void);
void HAL_7SEGMENT_WRITE(u8 display_number);



#endif /* 7_SEGMENT_INTERFACE_H_ */