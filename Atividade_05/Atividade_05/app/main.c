#include "include/hal_led.h"
#include "pico/stdlib.h"
#include "include/led_embutido.h"

int main() 
{
    stdio_init_all();

    if( led_initialized() == -1)
    {
        return -1;
    }

    while (true) 
    {
        led_blink();
    }
}