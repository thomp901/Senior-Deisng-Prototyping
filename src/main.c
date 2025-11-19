#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "hardware/i2c.h"
#include "mpl3115a2_interface.h"

void init_i2c() { //This snippet is from the SDK Functions Documentation
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

int main() {
    stdio_init_all();
    init_i2c();

    baro_init(); //Calling the C++

    //int32_t pressure_reading = baro_get_pressure_pascal();
   // int32_t temperature_reading = baro_get_altitude_meters();
   // float temperature = baro_getTemperature();

   while(true) {
   float pressure_reading = baro_get_pressure_pascal();
   float temperature = baro_get_temperature();
   printf("Temperature: %.2f Celcius, Pressure %.2f Pascal\n", temperature, pressure_reading);
   sleep_ms(1000);

   }
    
}
