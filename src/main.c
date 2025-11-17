#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
//#include "adc.c" //including the information from the adc.c file

void adc_setup();
extern void init_adc();
extern void init_adc_brightness();
extern uint16_t read_adc();

int main(){
    stdio_init_all();

    adc_setup();

    return 0;
}

void adc_setup() {
   // extern init_adc();
    init_adc();
    for(;;) {
        uint16_t read_moisture = read_adc();
        printf("ADC Result: %u\r", read_moisture);
        sleep_ms(100);

        uint16_t read_brightness = read_adc();
        printf("Brightness Result: %u\r", read_brightness);
        sleep_ms(100);
    }
}