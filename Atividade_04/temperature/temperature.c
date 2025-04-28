#include "temperature.h"

float adc_to_celsius( uint16_t adc_val )
{
    float temperature;
    temperature = 27 - ( adc_val*3.3/4095 - 0.706)/0.001721;
    return temperature;
}