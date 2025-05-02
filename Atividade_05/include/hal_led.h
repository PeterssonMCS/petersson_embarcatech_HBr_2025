#ifndef HAL_LED_H
#define HAL_LED_H

#include "pico/cyw43_arch.h"

//Set the led to high
void set_led_high();

//Set the led to low
void set_led_low();

//Check if initialized
int led_initialized();

#endif