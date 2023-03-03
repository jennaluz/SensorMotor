/*
 * TempHmdMotor/source/motor_driver.c
 */

#include "motor_driver.h"

const uint COIL_1 = 12;
const uint COIL_2 = 13;
const uint COIL_3 = 6;
const uint COIL_4 = 0;
const uint REV_STEPS = 525; // revolutions per step

void vMotorInit()
{
    gpio_init(COIL_1);
    gpio_init(COIL_2);
    gpio_init(COIL_3);
    gpio_init(COIL_4);

    gpio_set_dir(COIL_1, GPIO_OUT);
    gpio_set_dir(COIL_2, GPIO_OUT);
    gpio_set_dir(COIL_3, GPIO_OUT);
    gpio_set_dir(COIL_4, GPIO_OUT);

    return;
}

/*
 * Reset all Stepper Motor GPIO pins.
 */
void vMotorReset()
{
    gpio_put(COIL_1, 0);
    gpio_put(COIL_2, 0);
    gpio_put(COIL_3, 0);
    gpio_put(COIL_4, 0);

    return;
}

/*
 * Execute 8-step clockwise sequence.
 */
void vMotorClockwise()
{
    // reset motor gpio pins
    vMotorReset();

    gpio_put(COIL_4, 1);    // 0001
    sleep_ms(1);
    gpio_put(COIL_3, 1);    // 0011
    sleep_ms(1);
    gpio_put(COIL_4, 0);    // 0010
    sleep_ms(1);
    gpio_put(COIL_2, 1);    // 0110
    sleep_ms(1);
    gpio_put(COIL_3, 0);    // 0100
    sleep_ms(1);
    gpio_put(COIL_1, 1);    // 1100
    sleep_ms(1);
    gpio_put(COIL_2, 0);    // 1000
    sleep_ms(1);
    gpio_put(COIL_4, 1);    // 1001

    return;
}

/*
 * Execute 8-step counterclockwise sequence.
 */
void vMotorCounterclockwise()
{
    // reset motor gpio pins
    vMotorReset();

    gpio_put(COIL_4, 1);
    gpio_put(COIL_1, 1);    // 1001
    sleep_ms(1);
    gpio_put(COIL_4, 0);    // 1000
    sleep_ms(1);
    gpio_put(COIL_2, 1);    // 1100
    sleep_ms(1);
    gpio_put(COIL_1, 0);    // 0100
    sleep_ms(1);
    gpio_put(COIL_3, 1);    // 0110
    sleep_ms(1);
    gpio_put(COIL_2, 0);    // 0010
    sleep_ms(1);
    gpio_put(COIL_4, 1);    // 0011
    sleep_ms(1);
    gpio_put(COIL_3, 0);    // 0011

    return;
}

/*
 * Complete a single revolution based on REV_STEPS.
 * Alternate between clockwise and counterclockwise revolutions.
 */
void vMotorAlternate()
{
    int i = 0;
    for (i = 0; i < REV_STEPS; i++) {
        vMotorClockwise();
    }

    for (i = 0; i < REV_STEPS; i++) {
        vMotorCounterclockwise();
    }
}
