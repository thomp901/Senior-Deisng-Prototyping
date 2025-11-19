#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#include "hardware/i2c.h"

void init_i2c() {
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function();
    gpio_set_function();
    gpio_pull_up();
    gpio_pull_up();
}

int main() {
    stdio_init_all();
    sleep_ms(1000);
    i2c_steup();
}
