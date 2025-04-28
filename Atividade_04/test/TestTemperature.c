#include "unity/unity.h"
#include "temperature/temperature.h"
#include <stdio.h>
#include "pico/stdlib.h"

void test_adc_reading(void)
{
    printf("Testing for adc reading 800\n");
    TEST_ASSERT_FLOAT_WITHIN( 0.1 , 27 , adc_to_celsius(900) );
}

void test_ambient_temperature(void)
{
    printf("Testing for ambient temperature 27ºC\n");
    TEST_ASSERT_FLOAT_WITHIN( 0.1 , 27 , adc_to_celsius(876) );
}

int main(void)
{
    stdio_init_all();
    sleep_ms(2000);

    UNITY_BEGIN();
    RUN_TEST(test_adc_reading);
    RUN_TEST(test_ambient_temperature);
    UNITY_END();
    while(1);
    return 0;
}