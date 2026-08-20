#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "../../LIB/Std_Types.h"

/* Return Status Codes */
#define LCD_OK                   0U
#define LCD_NOT_OK               1U
#define LCD_NULL_POINTER         2U
#define LCD_WRONG_PARAM          3U

/* HD44780 Instruction Set Macros */
#define LCD_CMD_CLEAR_DISPLAY                       0x01U
#define LCD_CMD_RETURN_HOME                         0x02U
#define LCD_CMD_ENTRY_MODE_DEC_SHIFT_OFF            0x04U
#define LCD_CMD_ENTRY_MODE_DEC_SHIFT_ON             0x05U
#define LCD_CMD_ENTRY_MODE_INC_SHIFT_OFF            0x06U
#define LCD_CMD_ENTRY_MODE_INC_SHIFT_ON             0x07U
#define LCD_CMD_CURSOR_MOVE_SHIFT_LEFT              0x10U
#define LCD_CMD_CURSOR_MOVE_SHIFT_RIGHT             0x14U
#define LCD_CMD_DISPLAY_SHIFT_LEFT                  0x18U
#define LCD_CMD_DISPLAY_SHIFT_RIGHT                 0x1CU
#define LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0CU
#define LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0DU
#define LCD_CMD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0EU
#define LCD_CMD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0FU
#define LCD_CMD_DISPLAY_OFF_CURSOR_OFF              0x08U
#define LCD_CMD_8BIT_MODE_2_LINE                    0x38U
#define LCD_CMD_4BIT_MODE_2_LINE                    0x28U

#define LCD_CMD_CGRAM_START                         0x40U
#define LCD_CMD_DDRAM_START                         0x80U

/* Public APIs */
u8 LCD_Init(void);
u8 LCD_SendCmd(u8 Command);
u8 LCD_SendData(u8 Data);

u8 LCD_DisplayStr(const u8 *Copy_pu8Str);
u8 LCD_DisplayChr(u8 Chr);
u8 LCD_DisplayNum(s32 Number);

u8 LCD_ClearScreen(void);
u8 LCD_ReturnHome(void);
u8 LCD_GotoRowColumn(u8 Row, u8 Col);

#endif /* LCD_INTERFACE_H_ */