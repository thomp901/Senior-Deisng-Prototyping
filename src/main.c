#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "hardware/i2c.h"
#include "mpl3115a2_interface.h"

void init_i2c() {
    //i2c_init(i2c_default, 100 * 1000);
    //gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    //gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN), GPIO_FUNC_I2C;
    //gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    //gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

int main() {
    //stdio_init_all();
    //sleep_ms(1000);
    //i2c_steup();
}
