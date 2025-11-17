#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

void init_adc() {
    //Moisture Sensor Initlizaiton
    adc_init();
    adc_gpio_init(45); //gpio 45
    adc_select_input(5); //channel 5
}

void init_adc_brightness() {
    adc_init();
    adc_gpio_init(46); //gpio 46
    adc_select_input(6); //channel 6
}

uint16_t read_adc() {
    return adc_read();
}