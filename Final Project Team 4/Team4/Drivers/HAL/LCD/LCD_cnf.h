#ifndef LCD_CNF_H_
#define LCD_CNF_H_

/* CPU Frequency for delay accurate calculations (Adjust to your HW board e.g., 8000000UL or 16000000UL) */
#ifndef F_CPU
#define F_CPU                8000000UL
#endif

/* Control Pin Configurations */
#define LCD_RS_PORT          PORTC_ID
#define LCD_RS_PIN           PIN0

#define LCD_E_PORT           PORTC_ID
#define LCD_E_PIN            PIN1

/* Data Pin Configurations (4-Bit Mode) */
#define LCD_D4_PORT          PORTC_ID
#define LCD_D4_PIN           PIN2

#define LCD_D5_PORT          PORTC_ID
#define LCD_D5_PIN           PIN3

#define LCD_D6_PORT          PORTC_ID
#define LCD_D6_PIN           PIN4

#define LCD_D7_PORT          PORTC_ID
#define LCD_D7_PIN           PIN5

#endif /* LCD_CNF_H_ */