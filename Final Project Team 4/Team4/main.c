#define F_CPU 8000000UL
#include <util/delay.h>

#include "Drivers/LIB/Std_Types.h"
#include "Drivers/LIB/Bit_Math.h"

#include "Drivers/MCAL/DIO/DIO_Interface.h"
#include "Drivers/MCAL/Timers/TIMER_Interface.h"
#include "Drivers/MCAL/PWM/PWM_Interface.h"
#include "Drivers/MCAL/ADC/ADC_Interface.h"
#include "Drivers/MCAL/EXT/EXT_Interface.h"
#include "Drivers/MCAL/GIE/GIE_Interface.h"
#include "Drivers/MCAL/UART/UART_Interface.h"

#include "Drivers/HAL/FAN/FAN_Interface.h"
#include "Drivers/HAL/LED/LED_Interface.h"
#include "Drivers/HAL/Button/BUTTON_Interface.h"
#include "Drivers/HAL/LCD/LCD_Interface.h"



//---------------------------------------------------------
// Variables and function declaration 
// for handling the Three Lighting systems

// Bluetooth
u8 BT_FLAG = 0U;
u16 LDR_VAL = 0U;
u8 BT_RECIVE = 0U;
// Manual Button
u8 ButtonPrevState = 0U;
u8 ButtonCurrentState = 0U;
// LDR
u8 LDR_PrevIsNight = 0U;
u8 LDR_IsInitialized = 0U;

void Lighting_Initiation(void);
void Lighting_Loop(void);




//-----------------------------------------------------------
// Variables and function declaration 
// for Handling the Fire Alarm
volatile u8 alarm = 1;

void FireAlarm_Initiation(void);
void FireAlarm_Loop(void);
void Fire_Alarm_Interrupt(void);




//-----------------------------------------------------------
// Variables and function declaration 
// for Handling the Rain Sensor
u8 rain = 0;
u8 current_state=0;
s8 last_state = -1;

void RainSensor_Initiation(void);
void RainSensor_Loop(void);




//-------------------------------------------------------------
// Variables and function declaration 
// for handling Fan Control and Temperature
volatile u16 TemperatureC = 0;

/* Fan 1 connected to PB3 (OC0 / Timer0) */
FAN_ConfigType Fan1_Timer0 = {
	.Channel      = FAN_CHANNEL_TIMER0_OC0,
	.Timer1FreqHz = 0
};

/* Fan 2 connected to PD4 (OC1B / Timer1 Channel B as wired in the schematic) */
FAN_ConfigType Fan2_Timer1 = {
	.Channel      = FAN_CHANNEL_TIMER1_OC1B,
	.Timer1FreqHz = 1000UL /* 1 kHz PWM */
};

void Fan_Initiation(void);
void Fan_Loop(void);




//------------------------------------------------------------
// Variables and function declaration
// for handling the LCD Screen and its timer
u8 row = 0;
s32 temp = 0; 
u8 day = 1;
u32 counter=0;

// One Timer2 overflow with prescaler = 1024 (Prescaler = 7):
#define APP_OVERFLOWS_FOR_1_SEC   6U
#define APP_TIMER2_PRESCALER_1024 7U
u8 ShowingTakeCare = 0U;

/* Returns 1 exactly once every ~1 second, 0 otherwise. Never waits. */
static u8 App_OneSecondTick(void);
void LCD_Initiation(void);
void LCD_Loop(void);

//----------------------------------------------------------------







int main(void)
{
	// Setup Code (runs once)
	Lighting_Initiation();
	RainSensor_Initiation();
	FireAlarm_Initiation();
	Fan_Initiation();
	LCD_Initiation();
	
	// Loop Code (runs continuously)
	while (1)
	{
		Lighting_Loop();
		RainSensor_Loop();
		FireAlarm_Loop();
		Fan_Loop();
		LCD_Loop();	
	}
}








// ----------------------
// Definition of functions
// ----------------------

// Lighting
void Lighting_Initiation(void) {
	ADC_Init();
	USART_Init(9600UL, 8U, 1U);

	// Relay setup (default off)
	LED_Init(PORTB_ID, PIN4);

	// DIP switch feature enables
	Button_Init(PORTD_ID, PIN3); // Switch 1: Enable Manual Control
	Button_Init(PORTD_ID, PIN7); // Switch 2: Enable Bluetooth Control
	Button_Init(PORTD_ID, PIN5); // Switch 3: Enable LDR Auto Control

	// Lamp manual toggle push button
	Button_Init(PORTD_ID, PIN6);

	// LDR uses ADC Pin (PORTA, PIN1 initialized via ADC_Init)
}
void Lighting_Loop(void) {

	// Manual (Button)
	if (Button_Read(PORTD_ID, PIN3))
	{
		u8 ButtonCurrentState = Button_Read(PORTD_ID, PIN6);

		// Detect Button Press (Rising Edge)
		if ((ButtonCurrentState == 1U) && (ButtonPrevState == 0U))
		{
			LED_Toggle(PORTB_ID, PIN4);
		}
		ButtonPrevState = ButtonCurrentState;
	}
	else
	{
		ButtonPrevState = 0U;
	}

	// Bluetooth
	if (Button_Read(PORTD_ID, PIN7))
	{
		u8 BT_RECIVE = USART_Receive();
		
		if ((BT_RECIVE == 'O') || (BT_RECIVE == 'o'))
		{
			LED_On(PORTB_ID, PIN4);
		}
		else if ((BT_RECIVE == 'C') || (BT_RECIVE == 'c'))
		{
			LED_Off(PORTB_ID, PIN4);
		}
	}

	// Auto LDR
	LDR_VAL = ADC_ReadValue(ADC_CHANNEL1);
	if (Button_Read(PORTD_ID, PIN5))
	{
		if (LDR_VAL != ADC_READ_ERROR)
		{
			// Determine current state (Night if LDR value <= 512)
			u8 LDR_CurrentIsNight = (LDR_VAL <= 512U) ? 1U : 0U;

			// Sync state on first boot/enable to prevent false triggers
			if (!LDR_IsInitialized)
			{
				LDR_PrevIsNight = LDR_CurrentIsNight;
				LDR_IsInitialized = 1U;
			}

			// Day-to-Night Transition: Turn ON Light
			if ((LDR_CurrentIsNight == 1U) && (LDR_PrevIsNight == 0U))
			{
				LED_On(PORTB_ID, PIN4);
			}
			// Night-to-Day Transition: Turn OFF Light
			else if ((LDR_CurrentIsNight == 0U) && (LDR_PrevIsNight == 1U))
			{
				LED_Off(PORTB_ID, PIN4);
			}

			// Save state for next check
			LDR_PrevIsNight = LDR_CurrentIsNight;
		}
	}
	else
	{
		LDR_IsInitialized = 0U;
	}
}

// Fire & Gas sensors
void Fire_Alarm_Interrupt (void) {
	alarm =DIO_GetPinValue(PORTD_ID,PIN2);
}
void FireAlarm_Initiation(void) {
	LED_Init(PORTB_ID,PIN0);
	LED_Init(PORTB_ID,PIN1);
	LED_Off(PORTB_ID,PIN0);
	LED_Off(PORTB_ID,PIN1);
	alarm = DIO_GetPinValue(PORTD_ID, PIN2);
	EXT_Init(EXT0,ANY_LOGICAL_CHANGE);
	EXT_SetCallBack(Fire_Alarm_Interrupt,EXT0);
	GIE_Enable();
}
void FireAlarm_Loop(void) {
	if (alarm==0)
	{
		LED_On(PORTB_ID,PIN0);
		LED_Off(PORTB_ID,PIN1);
		} else {
		LED_On(PORTB_ID,PIN1);
		LED_Off(PORTB_ID,PIN0);
	}
}

// Rain Sensor
void RainSensor_Initiation(void) {
	Button_Init(PORTC_ID,PIN6);  // for reading the sensor as a button
}
void RainSensor_Loop(void) {
	current_state = Button_Read(PORTC_ID,PIN6);
	if (current_state != last_state) rain=current_state;
	last_state = current_state;
}

// Fans
void Fan_Initiation(void){
	/* Initialize Peripherals */
	ADC_Init();
	FAN_Init(&Fan1_Timer0);
	FAN_Init(&Fan2_Timer1);
}
void Fan_Loop(void){
	u16 Local_AdcRaw = 0;
	u32 Local_u32MilliVolt = 0;
	/* Read analog reading from PA0 / Channel 0 (0 - 1023) */
	Local_AdcRaw = ADC_ReadValue(ADC_CHANNEL0);

	if (Local_AdcRaw != ADC_READ_ERROR)
	{
		/* Convert steps to mV (AVCC = 5V reference: V = ADC * 5000 / 1023) */
		Local_u32MilliVolt = ((u32)Local_AdcRaw * 5000UL) / 1023UL;

		/* LM35 sensitivity: 10 mV / 1C */
		TemperatureC = (u16)(Local_u32MilliVolt / 10UL);

		/* Temperature control conditions */
		if (TemperatureC >= 40)
		{
			/* > 40C: Fan 1 at 100%, Fan 2 (Timer1 on PD4) at 100% */
			FAN_SetSpeed(&Fan1_Timer0, 100);
			FAN_SetSpeed(&Fan2_Timer1, 100);
		}
		else if (TemperatureC >= 30 && TemperatureC < 40)
		{
			/* > 30C: Fan 1 at 75%, Fan 2 OFF */
			FAN_SetSpeed(&Fan1_Timer0, 75);
			FAN_SetSpeed(&Fan2_Timer1, 75);
		}
		else if (TemperatureC >= 20 && TemperatureC < 30)
		{
			/* > 20C: Fan 1 at 50%, Fan 2 OFF */
			FAN_SetSpeed(&Fan1_Timer0, 50);
			FAN_SetSpeed(&Fan2_Timer1, 50);
		}
		else
		{
			/* <= 20C: Both fans OFF */
			FAN_SetSpeed(&Fan1_Timer0, 0);
			FAN_SetSpeed(&Fan2_Timer1, 0);
		}
	}
}

// LCD
static u8 App_OneSecondTick(void)
{
	static u8 OverflowCount = 0U;
	u8 Elapsed = 0U;
	
	if (TIMER_IsOverflow(TIMER_2) == 1U)
	{
		OverflowCount++;
		
		if (OverflowCount >= APP_OVERFLOWS_FOR_1_SEC)
		{
			OverflowCount = 0U;
			Elapsed = 1U;
		}
	}
	
	return Elapsed;
}
void LCD_Initiation(void) {
	LCD_Init();
	TIMER_Init(TIMER_2, APP_TIMER2_PRESCALER_1024);
}
void LCD_Loop(void) {
	// Reset row counter
	row = 0;
	
	// Temperature Display
	temp=TemperatureC;
	LCD_GotoRowColumn(row, 0);
	LCD_DisplayStr((u8*)" Temperature: ");
	LCD_DisplayNum(temp);
	LCD_DisplayStr((u8*)" C    ");
	row++;
	
	// Time State Display
	day = (LDR_VAL > 512U);
	LCD_GotoRowColumn(row, 0);
	if (day) {
		LCD_DisplayStr((u8*)"       Its Day      ");
	}
	else {
		LCD_DisplayStr((u8*)"      Its Night    ");
	}
	row++;
	
	// Rain State Display
	
	LCD_GotoRowColumn(row, 0);
	if (rain) {
		if (App_OneSecondTick() == 1U)
		{
			if (ShowingTakeCare == 1U)
			{
				LCD_DisplayStr((u8*)"  '' IT'S RAINING '' ");
				ShowingTakeCare = 0U;
			}
			else
			{
				LCD_DisplayStr((u8*)"   !! TAKE CARE !!   ");
				ShowingTakeCare = 1U;
			}
		}
		row++;
	}
	
	// Alarm State Display
	LCD_GotoRowColumn(row, 0);
	if (alarm) {
		LCD_DisplayStr((u8*)"    !!! ALARM !!!   ");
	} else {
		LCD_DisplayStr((u8*)"                   ");
	}
	if (!rain || !alarm) {
		row++;
		LCD_GotoRowColumn(row, 0);
		LCD_DisplayStr((u8*)"                   ");
	}
	if (!rain && !alarm) {
		row++;
		LCD_GotoRowColumn(row, 0);
		LCD_DisplayStr((u8*)"                   ");
	}
}