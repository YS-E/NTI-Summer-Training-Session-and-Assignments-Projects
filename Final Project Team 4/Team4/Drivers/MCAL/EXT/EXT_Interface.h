#ifndef EXT_INTERFACE_H_
#define EXT_INTERFACE_H_

#include "../../LIB/Std_Types.h"

#define EXT0 (u8)(0X00)
#define EXT1 (u8)(0X01)
#define EXT2 (u8)(0X02)

#define LOW_LEVEL          (u8)(0X00)
#define ANY_LOGICAL_CHANGE (u8)(0X01)
#define FALLING_EDGE       (u8)(0X02)
#define RISING_EDGE        (u8)(0X03)

#define G_INTERRUPT_NOT_WORK (u8)(0X00)
#define G_INTERRUPT_WORK  (u8)(0X01)

void EXT_Init(u8 ExtNum,u8 ControlSens);
void EXT_SetCallBack(  void (*ptr_ext)(void) ,u8 ExtNum );
void EXT_Disable(u8 ExtNum);

#endif /* EXT_INTERFACE_H_ */
