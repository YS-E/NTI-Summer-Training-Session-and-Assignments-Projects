#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

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

/* Initialization Commands */
#define LCD_CMD_INIT_RESET                          0x03U
#define LCD_CMD_INIT_4BIT_MODE                      0x02U

/* DDRAM Line Base Addresses */
#define LCD_ROW0_BASE_ADDR                          0x80U
#define LCD_ROW1_BASE_ADDR                          0xC0U
#define LCD_ROW2_BASE_ADDR                          0x94U
#define LCD_ROW3_BASE_ADDR                          0xD4U

/* Private Helper Functions */
static void LCD_voidSendEnablePulse(void);
static void LCD_voidSend4Bits(u8 Copy_u8Data);

#endif /* LCD_PRIVATE_H_ */