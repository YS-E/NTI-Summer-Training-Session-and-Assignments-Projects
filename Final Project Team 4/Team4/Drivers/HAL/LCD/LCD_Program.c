#include "LCD_cnf.h"
#include <util/delay.h>

#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "LCD_Private.h"
#include "LCD_Interface.h"

u8 LCD_Init(void)
{
	/* 1. Configure Control & Data Pins as Output */
	(void)DIO_SetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_OUTPUT);
	(void)DIO_SetPinDirection(LCD_E_PORT,  LCD_E_PIN,  DIO_OUTPUT);

	(void)DIO_SetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_OUTPUT);
	(void)DIO_SetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_OUTPUT);
	(void)DIO_SetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_OUTPUT);
	(void)DIO_SetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_OUTPUT);

	/* 2. HD44780 4-Bit Hardware Initialization Sequence */
	_delay_ms(20);
	
	LCD_voidSend4Bits(LCD_CMD_INIT_RESET);
	LCD_voidSendEnablePulse();
	_delay_ms(5);

	LCD_voidSend4Bits(LCD_CMD_INIT_RESET);
	LCD_voidSendEnablePulse();
	_delay_us(150);

	LCD_voidSend4Bits(LCD_CMD_INIT_RESET);
	LCD_voidSendEnablePulse();

	LCD_voidSend4Bits(LCD_CMD_INIT_4BIT_MODE);
	LCD_voidSendEnablePulse();

	/* 3. Function & Display Configurations */
	(void)LCD_SendCmd(LCD_CMD_4BIT_MODE_2_LINE);
	(void)LCD_SendCmd(LCD_CMD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
	(void)LCD_ClearScreen();
	(void)LCD_SendCmd(LCD_CMD_ENTRY_MODE_INC_SHIFT_OFF);

	return LCD_OK;
}

u8 LCD_SendCmd(u8 Command)
{
	/* Select Command Register (RS = LOW) */
	(void)DIO_SetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_LOW);

	/* Send High Nibble */
	LCD_voidSend4Bits(Command >> 4U);
	LCD_voidSendEnablePulse();

	/* Send Low Nibble */
	LCD_voidSend4Bits(Command);
	LCD_voidSendEnablePulse();

	return LCD_OK;
}

u8 LCD_SendData(u8 Data)
{
	/* Select Data Register (RS = HIGH) */
	(void)DIO_SetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_HIGH);

	/* Send High Nibble */
	LCD_voidSend4Bits(Data >> 4U);
	LCD_voidSendEnablePulse();

	/* Send Low Nibble */
	LCD_voidSend4Bits(Data);
	LCD_voidSendEnablePulse();

	return LCD_OK;
}

u8 LCD_DisplayStr(const u8 *Copy_pu8Str)
{
	u8 ErrorStatus = LCD_OK;
	u32 u32Index = 0U;

	if (Copy_pu8Str == NULL)
	{
		ErrorStatus = LCD_NULL_POINTER;
	}
	else
	{
		while (Copy_pu8Str[u32Index] != '\0')
		{
			(void)LCD_SendData(Copy_pu8Str[u32Index]);
			u32Index++;
		}
	}

	return ErrorStatus;
}

u8 LCD_DisplayChr(u8 Chr)
{
	return LCD_SendData(Chr);
}

u8 LCD_DisplayNum(s32 Number)
{
	u8 Buffer[11];
	u8 Idx = 0U;
	u8 Length = 0U;

	if (Number == 0)
	{
		(void)LCD_SendData('0');
		return LCD_OK;
	}

	if (Number < 0)
	{
		(void)LCD_SendData('-');
		Number = -Number;
	}

	while (Number > 0)
	{
		Buffer[Idx++] = (u8)((Number % 10) + '0');
		Number /= 10;
	}

	/* Reverse & Display */
	for (Length = Idx; Length > 0U; Length--)
	{
		(void)LCD_SendData(Buffer[Length - 1U]);
	}

	return LCD_OK;
}

u8 LCD_ClearScreen(void)
{
	u8 ErrorStatus = LCD_SendCmd(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(2);
	return ErrorStatus;
}

u8 LCD_ReturnHome(void)
{
	u8 ErrorStatus = LCD_SendCmd(LCD_CMD_RETURN_HOME);
	_delay_ms(2);
	return ErrorStatus;
}

u8 LCD_GotoRowColumn(u8 Row, u8 Col)
{
	u8 ErrorStatus = LCD_OK;

	// 1. Expand allowed columns from 15 to 19 (for 20-character wide screens)
	if (Col > 19U)
	{
		ErrorStatus = LCD_WRONG_PARAM;
	}
	else
	{
		switch (Row)
		{
			case 0U:
			(void)LCD_SendCmd(0x80U + Col); // 0x80 is standard ROW0 base
			break;

			case 1U:
			(void)LCD_SendCmd(0xC0U + Col); // 0xC0 is standard ROW1 base
			break;

			case 2U:
			// Row 2 base address is typically Row 0 Base + 20 (0x94)
			(void)LCD_SendCmd(0x94U + Col);
			break;

			case 3U:
			// Row 3 base address is typically Row 1 Base + 20 (0xD4)
			(void)LCD_SendCmd(0xD4U + Col);
			break;

			default:
			ErrorStatus = LCD_WRONG_PARAM;
			break;
		}
	}

	return ErrorStatus;
}


/* Static Helper Implementation */
static void LCD_voidSendEnablePulse(void)
{
	(void)DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_HIGH);
	_delay_us(1);
	(void)DIO_SetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_LOW);
	_delay_us(100);
}

static void LCD_voidSend4Bits(u8 Data)
{
	(void)DIO_SetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(Data, 0));
	(void)DIO_SetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(Data, 1));
	(void)DIO_SetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(Data, 2));
	(void)DIO_SetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(Data, 3));
}