/*
	led.c
	Teagan Horkan
	3/19/18
	
	Provides easy to use functions for toggling the onboard LEDs
	
*/

#include "led.h"
#include "gpio.h"

void led_green_on(void){
	HAL_GPIO_WritePin(LED_GREEN_GROUP, LED_GREEN_PIN, GPIO_PIN_RESET);
}

void led_green_off(void) {
	HAL_GPIO_WritePin(LED_GREEN_GROUP, LED_GREEN_PIN, GPIO_PIN_SET);
}

void led_green_toggle(void){
	HAL_GPIO_TogglePin(LED_GREEN_GROUP, LED_GREEN_PIN);
}

void led_red_on(void) {
	HAL_GPIO_WritePin(LED_RED_GROUP, LED_RED_PIN, GPIO_PIN_RESET);
}

void led_red_off(void) {
	HAL_GPIO_WritePin(LED_RED_GROUP, LED_RED_PIN, GPIO_PIN_SET);
}

void led_red_toggle(void) {
	HAL_GPIO_TogglePin(LED_RED_GROUP, LED_RED_PIN);
}
