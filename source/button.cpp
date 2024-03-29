/*
 * SensorMotor/source/button.cpp
 *
 * Initializes button interrupt service routines.
 * Uses a semaphore to signal button tasks when their respective buttons were pushed.
 */


#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include <stdio.h>

#include "button.h"
#include "display.h"
#include "display_driver.h"
#include "motor.h"
#include "pixel.h"
#include "system_code.h"
#include "system_error.h"


SemaphoreHandle_t button1_semaphore = NULL;
SemaphoreHandle_t button2_semaphore = NULL;
SemaphoreHandle_t button3_semaphore = NULL;

const uint BUTTON_1 = 19;
const uint BUTTON_2 = 9;
const uint BUTTON_3 = 8;


/*
 * Initializes interrupt requests for each buttons.
 * Each event calls the button_callback() function.
 */
void button_irq_init()
{
    gpio_set_irq_enabled_with_callback(BUTTON_1, GPIO_IRQ_EDGE_RISE, true, button_callback);
    gpio_set_irq_enabled(BUTTON_2, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BUTTON_3, GPIO_IRQ_EDGE_RISE, true);
}


/*
 * Gives the semaphore corresponding to the button that was pushed.
 */
void button_callback(uint gpio, uint32_t events)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    switch (gpio) {
        case BUTTON_1:
            xSemaphoreGiveFromISR(button1_semaphore, &xHigherPriorityTaskWoken);
            break;
        case BUTTON_2:
            xSemaphoreGiveFromISR(button2_semaphore, &xHigherPriorityTaskWoken);
            break;
        case BUTTON_3:
            xSemaphoreGiveFromISR(button3_semaphore, &xHigherPriorityTaskWoken);
            break;
        default:
            system_error(ERROR_UNKNOWN_INPUT);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*
 * Blocks on button1_semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 */
void button1_handler(void *parameters)
{
    TickType_t end_time = 0;
    uint button_pushes = 0;
    display_setting base_code = SET_DECIMAL;
    system_code motor_code = MOTOR_TEMPERATURE;
    system_code error_code = ERROR_EMERGENCY_STOP;

    while (true) {
        xSemaphoreTake(button1_semaphore, portMAX_DELAY);

        // button 1 was pushed
        end_time = xTaskGetTickCount() + 2 * configTICK_RATE_HZ;

        while (xTaskGetTickCount() < end_time) {
            // debounce
            vTaskDelay(200 / portTICK_PERIOD_MS);
            xSemaphoreTake(button1_semaphore, 0);
            button_pushes++;

            // check for more input
            if (xTaskGetTickCount() < end_time) {
                xSemaphoreTake(button1_semaphore, end_time - xTaskGetTickCount());
            }
        }

        // make decision based on count of pushes
        switch (button_pushes) {
            case 1:
                motor_code = MOTOR_TEMPERATURE;
                xQueueSend(motor_queue, &motor_code, 0);
                break;
            case 2:
                motor_code = MOTOR_HUMIDITY;
                xQueueSend(motor_queue, &motor_code, 0);
                break;
            case 3:
                if (base_code == SET_DECIMAL) {
                    base_code = SET_HEXADECIMAL;
                } else {
                    base_code = SET_DECIMAL;
                }

                xQueueSend(sensor_base_queue, &base_code, 0);
                break;
            case 4:
                system_error(ERROR_EMERGENCY_STOP);
                xQueueSend(pixel_queue, &error_code, 0);

                motor_code = MOTOR_HALT;
                xQueueOverwrite(motor_queue, &motor_code);
                break;
            default:
                system_error(ERROR_UNKNOWN_INPUT);
        }

        // reset pushes counter
        button_pushes = 0;

        taskYIELD();
    }
}


/*
 * Blocks on button2_semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 * Changes the status of the Stepper Motor based on the button input.
 */
void button2_handler(void *parameters)
{
    TickType_t end_time = 0;
    uint button_pushes = 0;
    system_code motor_code = MOTOR_CLOCKWISE;

    while (true) {
        xSemaphoreTake(button2_semaphore, portMAX_DELAY);

        // button 2 was pushed
        end_time = xTaskGetTickCount() + 2 * configTICK_RATE_HZ;

        while (xTaskGetTickCount() < end_time) {
            // debounce
            vTaskDelay(200 / portTICK_PERIOD_MS);
            xSemaphoreTake(button2_semaphore, 0);
            button_pushes++;

            // check for more input
            if (xTaskGetTickCount() < end_time) {
                xSemaphoreTake(button2_semaphore, end_time - xTaskGetTickCount());
            }
        }

        // make decision based on count of pushes
        switch (button_pushes) {
            case 1:
                motor_code = MOTOR_CLOCKWISE;
                xQueueSend(motor_queue, &motor_code, 0);
                break;
            case 2:
                motor_code = MOTOR_COUNTERCLOCKWISE;
                xQueueSend(motor_queue, &motor_code, 0);
                break;
            case 3:
                motor_code = MOTOR_ALTERNATE;
                xQueueSend(motor_queue, &motor_code, 0);
                break;
            default:
                system_error(ERROR_UNKNOWN_INPUT);
        }

        // reset pushes counter
        button_pushes = 0;

        taskYIELD();
    }
}


/*
 * Blocks on button3_semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 */
void button3_handler(void *parameters)
{
    TickType_t end_time = 0;
    uint button_pushes = 0;
    system_code display_code = DISPLAY_TEMPERATURE;
    system_code motor_code = MOTOR_STATUS;

    while (true) {
        xSemaphoreTake(button3_semaphore, portMAX_DELAY);

        // button 3 was pushed
        end_time = xTaskGetTickCount() + 2 * configTICK_RATE_HZ;

        while (xTaskGetTickCount() < end_time) {
            // debounce
            vTaskDelay(200 / portTICK_PERIOD_MS);
            xSemaphoreTake(button3_semaphore, 0);
            button_pushes++;

            // check for more input
            if (xTaskGetTickCount() < end_time) {
                xSemaphoreTake(button3_semaphore, end_time - xTaskGetTickCount());
            }
        }

        // make decision based on count of pushes
        switch(button_pushes) {
            case 1:
                display_code = DISPLAY_TEMPERATURE;

                xQueueSend(pixel_queue, &display_code, 0);
                if (xQueueSend(display_queue, &display_code, 0) == pdFALSE) {
                    system_error(ERROR_OVERFLOW);
                }
                break;
            case 2:
                display_code = DISPLAY_HUMIDITY;

                xQueueSend(pixel_queue, &display_code, 0);
                if (xQueueSend(display_queue, &display_code, 0) == pdFALSE) {
                    system_error(ERROR_OVERFLOW);
                }
                break;
            case 3:
                display_code = MOTOR_STATUS;

                xQueueSend(pixel_queue, &display_code, 0);
                if (xQueueSend(display_queue, &display_code, 0) == pdFALSE) {
                    system_error(ERROR_OVERFLOW);
                }
                break;
            default:
                system_error(ERROR_UNKNOWN_INPUT);
        }

        // reset pushes counter
        button_pushes = 0;

        taskYIELD();
    }
}
