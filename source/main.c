/*
 * SensorMotor/source/main.c
 */

#include <pico/stdlib.h>
#include <stdio.h>

#include "hdc1080_driver.h"
#include "motor_driver.h"

int main()
{
    stdio_init_all();

    // initialize stepper motor gpio pins
    //vMotorInit();
    vHDC1080Init();

    while (true) {
        //vHDC1080ReadTmp();
        vHDC1080ReadHmd();
        sleep_ms(100);
    }
}
