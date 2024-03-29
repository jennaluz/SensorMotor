/*
 * SensorMotor/source/motor_driver.cpp
 *
 * Sends a sequence of signals to the Stepper Motor GPIO pins to manipulate it.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>

#include "motor_driver.h"


const uint COIL_1         = 12;
const uint COIL_2         = 13;
const uint COIL_3         = 6;
const uint COIL_4         = 0;
const uint INTERVAL_STEPS = 10;


/*
 * Initializes all GPIO pins for the Stepper Motor.
 */
void motor_init()
{
    gpio_init(COIL_1);
    gpio_init(COIL_2);
    gpio_init(COIL_3);
    gpio_init(COIL_4);

    gpio_set_dir(COIL_1, GPIO_OUT);
    gpio_set_dir(COIL_2, GPIO_OUT);
    gpio_set_dir(COIL_3, GPIO_OUT);
    gpio_set_dir(COIL_4, GPIO_OUT);
}


/*
 * Reset all Stepper Motor GPIO pins.
 */
void motor_reset()
{
    gpio_put(COIL_1, 0);
    gpio_put(COIL_2, 0);
    gpio_put(COIL_3, 0);
    gpio_put(COIL_4, 0);
}


/*
 * Execute 8-step clockwise sequence.
 */
void motor_clockwise()
{
    // reset motor gpio pins
    motor_reset();

    gpio_put(COIL_4, 1);
    gpio_put(COIL_1, 1);    // 1001
    vTaskDelay(1);
    gpio_put(COIL_4, 0);    // 1000
    vTaskDelay(1);
    gpio_put(COIL_2, 1);    // 1100
    vTaskDelay(1);
    gpio_put(COIL_1, 0);    // 0100
    vTaskDelay(1);
    gpio_put(COIL_3, 1);    // 0110
    vTaskDelay(1);
    gpio_put(COIL_2, 0);    // 0010
    vTaskDelay(1);
    gpio_put(COIL_4, 1);    // 0011
    vTaskDelay(1);
    gpio_put(COIL_3, 0);    // 0011
}


/*
 * Execute 8-step counterclockwise sequence.
 */
void motor_counterclockwise()
{
    // reset motor gpio pins
    motor_reset();

    gpio_put(COIL_4, 1);    // 0001
    vTaskDelay(1);
    gpio_put(COIL_3, 1);    // 0011
    vTaskDelay(1);
    gpio_put(COIL_4, 0);    // 0010
    vTaskDelay(1);
    gpio_put(COIL_2, 1);    // 0110
    vTaskDelay(1);
    gpio_put(COIL_3, 0);    // 0100
    vTaskDelay(1);
    gpio_put(COIL_1, 1);    // 1100
    vTaskDelay(1);
    gpio_put(COIL_2, 0);    // 1000
    vTaskDelay(1);
    gpio_put(COIL_4, 1);    // 1001
}


/*
 * Sends an invalid step sequence to halt the Stepper Motor.
 */
void motor_halt()
{
    gpio_put(COIL_4, 0);
    gpio_put(COIL_4, 1);
}


/*
 * Moves the Stepper Motor a small amount clockwise.
 */
void motor_increment()
{
    int i = 0;

    for (i = 0; i < INTERVAL_STEPS; i++) {
        motor_clockwise();
    }
}


/*
 * Moves the Stepper Motor a small amount counterclockwise.
 */
void motor_decrement()
{
    int i = 0;

    for (i = 0; i < INTERVAL_STEPS; i++) {
        motor_counterclockwise();
    }
}
