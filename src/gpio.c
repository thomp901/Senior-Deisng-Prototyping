#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/timer.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "pico/rand.h"

//Objective 3: GPIO-Based Button and Display - Ann Z 
//An ability to use GPIO to receive input from a button 
//and display plant health on a 2-digit seven-segment display. Peripheral: GPIO Feature: 
//Input (button to simulate watering) and Output (numerical display of health score) Devices: Push-Button, 
//7-segment display (common cathode or via shift register)

const int SPI_7SEG_SCK = 14;
const int SPI_7SEG_CSn = 13;
const int SPI_7SEG_TX = 15;

void water_isr(){
    int gpio_21 = gpio_get_irq_event_mask(21); //if pressed

    //Acknowledge the interrupt by clearing the appropriate event mask.
    if (gpio_21 & GPIO_IRQ_EDGE_RISE){
        gpio_acknowledge_irq(21, GPIO_IRQ_EDGE_RISE);
        //do something
    }
}


void gpio_watering_init(){
    //initialize an input for the button interrupt
    gpio_init(21);
    gpio_add_raw_irq_handler(21, water_isr);

    gpio_set_irq_enabled(21, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_dormant_irq_enabled(21, GPIO_IRQ_EDGE_RISE, true);
    irq_set_enabled(IO_IRQ_BANK0, true);

    //output gpio set to communicate to the 7 segment function
    gpio_set_function(SPI_7SEG_SCK, GPIO_FUNC_SIO);
    gpio_set_function(SPI_7SEG_CSn, GPIO_FUNC_SIO);
    gpio_set_function(SPI_7SEG_TX, GPIO_FUNC_SIO);

    gpio_set_dir(SPI_7SEG_SCK, 1);
    gpio_set_dir(SPI_7SEG_CSn, 1);
    gpio_set_dir(SPI_7SEG_TX, 1);

    spi_init(spi0, 125000);
    spi_set_format(spi0, 16, 0, 0, SPI_MSB_FIRST);
}


