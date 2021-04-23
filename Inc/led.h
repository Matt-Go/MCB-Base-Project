/*
	led.h
	Teagan Horkan
	3/19/18
	
	Header file for led.c
	
*/

#ifndef _LED_H_
#define _LED_H_

#define LED_RED_PIN      	GPIO_PIN_7
#define LED_GREEN_PIN    	GPIO_PIN_14

#define LED_RED_GROUP			GPIOE
#define LED_GREEN_GROUP		GPIOF
	 
void led_green_on(void);
void led_green_off(void);
void led_green_toggle(void);
void led_red_on(void);
void led_red_off(void);
void led_red_toggle(void);

#endif // _LED_H_
