/*
 * TempHmdMotor/source/motor_driver.c
 */

#include "motor_driver.h"

const uint COIL_1 = 6;
const uint COIL_2 = 0;
const uint COIL_3 = 1;
const uint COIL_4 = 20;

void vStepClockwise()
{
    // reset all coil pins
    gpio_put(COIL_1, 0);
    gpio_put(COIL_2, 0);
    gpio_put(COIL_3, 0);
    gpio_put(COIL_4, 0);

    // perform 8-step clockwise sequence
    gpio_put(COIL_4, 1);    // 0001
    gpio_put(COIL_3, 1);    // 0011
    gpio_put(COIL_4, 0);    // 0010
    gpio_put(COIL_2, 1);    // 0110
    gpio_put(COIL_3, 0);    // 0100
    gpio_put(COIL_1, 1);    // 1100
    gpio_put(COIL_2, 0);    // 1000
    gpio_put(COIL_4, 1);    // 1001

    return;
}
