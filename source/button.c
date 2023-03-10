/*
 * SensorMotor/source/button.c
 *
 * Initializes button interrupt service routines.
 * Uses a semaphore to signal button tasks when their respective buttons were pushed.
 */


#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <pico/types.h>

#include <stdio.h>

#include "button.h"
#include "display.h"
#include "motor.h"
#include "sensor.h"
#include "system_code.h"


SemaphoreHandle_t xButton1Semaphore = NULL;
SemaphoreHandle_t xButton2Semaphore = NULL;
SemaphoreHandle_t xButton3Semaphore = NULL;

const uint BUTTON_1 = 19;
const uint BUTTON_2 = 9;
const uint BUTTON_3 = 8;


/*
 * Initializes interrupt requests for each buttons.
 * Each event calls the vButtonCallback() function.
 */
void vButtonIRQInit()
{
    gpio_set_irq_enabled_with_callback(BUTTON_1, GPIO_IRQ_EDGE_RISE, true, vButtonCallback);
    gpio_set_irq_enabled(BUTTON_2, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BUTTON_3, GPIO_IRQ_EDGE_RISE, true);
}


/*
 * Gives the semaphore corresponding to the button that was pushed.
 */
void vButtonCallback(uint gpio, uint32_t events)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    switch (gpio) {
        case BUTTON_1:
            xSemaphoreGiveFromISR(xButton1Semaphore, &xHigherPriorityTaskWoken);
            break;
        case BUTTON_2:
            xSemaphoreGiveFromISR(xButton2Semaphore, &xHigherPriorityTaskWoken);
            break;
        case BUTTON_3:
            xSemaphoreGiveFromISR(xButton3Semaphore, &xHigherPriorityTaskWoken);
            break;
        default:
            printf("Unexcpected input");
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*
 * Blocks on xButtono1Semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 */
void vButton1Handler()
{
    static uint uiPushes = 0;
    static absolute_time_t xEndTime = 0;
    sensor_base_e eSensorBase = DECIMAL;
    system_code_e eMotorCode = MOTOR_TEMPERATURE;

    while (true) {
        xSemaphoreTake(xButton1Semaphore, portMAX_DELAY);

        // button 1 was pushed
        xEndTime = make_timeout_time_ms(2000);

        while (get_absolute_time() < xEndTime) {
            // debounce
            vTaskDelay(175 / portTICK_PERIOD_MS);
            xSemaphoreTake(xButton1Semaphore, 0);
            uiPushes++;

            // check for more input
            if (get_absolute_time() < xEndTime) {
                xSemaphoreTake(xButton1Semaphore, absolute_time_diff_us(get_absolute_time(), xEndTime) / 1000 / portTICK_PERIOD_MS);
            }
        }

        //printf("Button 1 was pushed %d time(s).\n", uiPushes);
        switch (uiPushes) {
            case 1:
                eMotorCode = MOTOR_TEMPERATURE;
                xQueueOverwrite(xMotorQueue, &eMotorCode);
                //printf("Move stepper motor on temperature\n");
                break;
            case 2:
                eMotorCode = MOTOR_HUMIDITY;
                xQueueOverwrite(xMotorQueue, &eMotorCode);
                //printf("Move stepper motor on humidity\n");
                break;
            case 3:
                if (eSensorBase == DECIMAL) {
                    eSensorBase = HEXADECIMAL;
                } else {
                    eSensorBase = DECIMAL;
                }

                printf("toggle between\n");
                xQueueOverwrite(xSensorBaseQueue, &eSensorBase);
                break;
            case 4:
                eMotorCode = MOTOR_HALT;
                xQueueOverwrite(xMotorQueue, &eMotorCode);
                printf("Emergency stop stepper motor\n");
                break;
            default:
                printf("Error: unknown input\n");
        }

        // reset pushes counter
        uiPushes = 0;
    }
}


/*
 * Blocks on xButtono2Semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 * Changes the status of the Stepper Motor based on the button input.
 */
void vButton2Handler()
{
    static uint uiPushes = 0;
    static absolute_time_t xEndTime = 0;
    system_code_e eMotorCode = MOTOR_CLOCKWISE;

    while (true) {
        xSemaphoreTake(xButton2Semaphore, portMAX_DELAY);

        // button 2 was pushed
        xEndTime = make_timeout_time_ms(2000);

        while (get_absolute_time() < xEndTime) {
            // debounce
            vTaskDelay(175 / portTICK_PERIOD_MS);
            xSemaphoreTake(xButton2Semaphore, 0);
            uiPushes++;

            // check for more input
            if (get_absolute_time() < xEndTime) {
                xSemaphoreTake(xButton2Semaphore, absolute_time_diff_us(get_absolute_time(), xEndTime) / 1000 / portTICK_PERIOD_MS);
            }
        }

        // make decision based on count of pushes
        switch (uiPushes) {
            case 1:
                eMotorCode = MOTOR_CLOCKWISE;
                xQueueOverwrite(xMotorQueue, &eMotorCode);
                //printf("Continuously move stepper motor clockwise\n");
                break;
            case 2:
                eMotorCode = MOTOR_COUNTERCLOCKWISE;
                xQueueOverwrite(xMotorQueue, &eMotorCode);
                //printf("Continuously move stepper motor counterclockwise\n");
                break;
            case 3:
                eMotorCode = MOTOR_ALTERNATE;
                xQueueOverwrite(xMotorQueue, &eMotorCode);
                //printf("Alternate stepper motor between clockwise and counterclockwise revolutions\n");
                break;
            default:
                printf("Error: unknown input\n");
        }

        //printf("Button 2 was pushed %d time(s).\n", uiPushes);

        // reset pushes counter
        uiPushes = 0;
    }
}


/*
 * Blocks on xButtono3Semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 */
void vButton3Handler()
{
    system_code_e eDisplayCode = DISPLAY_TEMPERATURE;
    static uint uiPushes = 0;
    static absolute_time_t xEndTime = 0;

    while (true) {
        xSemaphoreTake(xButton3Semaphore, portMAX_DELAY);

        // button 3 was pushed
        xEndTime = make_timeout_time_ms(2000);

        while (get_absolute_time() < xEndTime) {
            // debounce
            vTaskDelay(175 / portTICK_PERIOD_MS);
            xSemaphoreTake(xButton3Semaphore, 0);
            uiPushes++;

            // check for more input
            if (get_absolute_time() < xEndTime) {
                xSemaphoreTake(xButton3Semaphore, absolute_time_diff_us(get_absolute_time(), xEndTime) / 1000 / portTICK_PERIOD_MS);
            }
        }

        //printf("Button 3 was pushed %d time(s).\n", uiPushes);
        switch(uiPushes) {
            case 1:
                eDisplayCode = DISPLAY_TEMPERATURE;
                xQueueSend(xDisplayQueue, &eDisplayCode, 0);
                break;
            case 2:
                eDisplayCode = DISPLAY_HUMIDITY;
                xQueueSend(xDisplayQueue, &eDisplayCode, 0);
                break;
            case 3:
                eDisplayCode = MOTOR_STATUS;
                xQueueSend(xDisplayQueue, &eDisplayCode, 0);
                break;
            default:
                printf("Error: unknown input\n");
        }

        // reset pushes counter
        uiPushes = 0;
    }
}
