/*
 * Blinker_Config.h
 *
 * Created: 11/08/2026 9:35:51 pm
 *  Author: YS
 */ 


#ifndef BLINKER_CONFIG_H_
#define BLINKER_CONFIG_H_

#define LED_PORT PORTB_ID
#define LED_PIN PIN0

#define FASTER_PORT PORTD_ID
#define FASTER_PIN PIN2

#define SLOWER_PORT PORTD_ID
#define SLOWER_PIN PIN3
#define START_DEFUALT 2

// 3000 -> off (adjust in main if changed at "off value")
// 2000 -> most delay
// 1000 -> default start point
// 750
// 500
// 250
// 100  -> least delay
// 0    -> on
#define SET_ARR { 3000, 2000, 1000, 750, 500, 250, 100, 0 }

#define SET_NUM 8



#endif /* BLINKER_CONFIG_H_ */