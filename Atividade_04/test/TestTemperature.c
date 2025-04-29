#include "unity/unity.h"
#include "temperature/temperature.h"
#include <stdio.h>
#include "pico/stdlib.h"

//Testing for Ambient Temperature of 27º C
void test_ambient_temperature(void)
{
    printf("Testing for ambient temperature 27ºC\n");
    TEST_ASSERT_FLOAT_WITHIN( 0.5 , 27 , adc_to_celsius(876) );
}

//Testing for RP2040 Maximum Temperature of 80º C
void test_max_temperature(void)
{
    printf("Testing for max temperature of 80ºC\n");
    TEST_ASSERT_FLOAT_WITHIN( 0.5 , 80 , adc_to_celsius(762) );
}

//Testing for RP2040 Minimum Temperature of -20º C
void test_min_temperature(void)
{
    printf("Testing for minimal temperature -20ºC\n");
    TEST_ASSERT_FLOAT_WITHIN( 0.5 , -20 , adc_to_celsius(976) );
}

int main(void)
{
    stdio_init_all();
    sleep_ms(5000);

    UNITY_BEGIN();
    RUN_TEST(test_ambient_temperature);
    RUN_TEST(test_max_temperature);
    RUN_TEST(test_min_temperature);
    UNITY_END();
    while(1);
    return 0;
}
