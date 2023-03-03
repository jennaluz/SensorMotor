/*
 * TempHmdMotor/source/main.c
 */

#include <pico/stdlib.h>
#include <stdio.h>

#include "motor_driver.h"

int main()
{
    stdio_init_all();

    // initialize stepper motor gpio pins
    gpio_init(COIL_1);
    gpio_init(COIL_2);
    gpio_init(COIL_3);
    gpio_init(COIL_4);

    gpio_set_dir(COIL_1, GPIO_OUT);
    gpio_set_dir(COIL_2, GPIO_OUT);
    gpio_set_dir(COIL_3, GPIO_OUT);
    gpio_set_dir(COIL_4, GPIO_OUT);

    int i = 0;
    for (i = 0; i < 500; i++) {
        vStepClockwise();
    }
}
