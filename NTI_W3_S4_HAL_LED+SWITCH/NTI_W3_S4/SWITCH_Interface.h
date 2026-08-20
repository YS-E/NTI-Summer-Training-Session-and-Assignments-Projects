/*
 * SWITCH_Interface.h
 *
 * Created: 12/08/2026 11:49:02 am
 *  Author: YS
 */ 


#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

void SWITCH_voidInit(u8 copy_u8Port, u8 copy_u8Pin);

u8   SWITCH_u8GetState(u8 copy_u8Port, u8 copy_u8Pin);

u8   SWITCH_u8GetToggleState(u8 copy_u8Port, u8 copy_u8Pin);

#endif