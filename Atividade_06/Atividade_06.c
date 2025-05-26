#include <stdio.h>
#include "pico/stdlib.h"
#include "include/wifi_conn.h"

int main()
{
    stdio_init_all();

    connect_to_wifi("Holy", "ZicaZica");

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
