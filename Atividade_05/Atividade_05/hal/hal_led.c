#include "include/hal_led.h"

int led_initialized()
{
    if (cyw43_arch_init()) 
    {
        return -1;
    }else
    {
        return -1;
    }
}

void set_led_high()
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}

void set_led_low()
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}
