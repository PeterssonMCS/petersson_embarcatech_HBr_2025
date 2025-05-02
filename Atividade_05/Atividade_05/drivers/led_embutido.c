#include "include/hal_led.h"
#include "include/led_embutido.h"

void led_blink()
{
    set_led_high();
    sleep_ms(500);
    set_led_low();
    sleep_ms(500);
}