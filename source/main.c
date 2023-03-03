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
    vMotorInit();

    while (true) {
        vMotorAlternate();
    }
}
