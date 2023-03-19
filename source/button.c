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
#include "display_driver.h"
#include "motor.h"
#include "portmacro.h"
#include "sensor.h"
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
            printf("Unexcpected input");
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


/*
 * Blocks on button1_semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 */
void button1_handler()
{
    TickType_t end_time = 0;
    uint button_pushes = 0;
    display_setting base_code = SET_DECIMAL;
    system_code motor_code = MOTOR_TEMPERATURE;

    while (true) {
        xSemaphoreTake(button1_semaphore, portMAX_DELAY);

        // button 1 was pushed
        end_time = xTaskGetTickCount() + 2 * configTICK_RATE_HZ;

        while (xTaskGetTickCount() < end_time) {
            // debounce
            vTaskDelay(175 / portTICK_PERIOD_MS);
            xSemaphoreTake(button1_semaphore, 0);
            button_pushes++;

            // check for more input
            if (xTaskGetTickCount() < end_time) {
                xSemaphoreTake(button1_semaphore, end_time - xTaskGetTickCount());
            }
        }

        //printf("Button 1 was pushed %d time(s).\n", uiPushes);
        switch (button_pushes) {
            case 1:
                motor_code = MOTOR_TEMPERATURE;
                xQueueOverwrite(motor_queue, &motor_code);
                //printf("Move stepper motor on temperature\n");
                break;
            case 2:
                motor_code = MOTOR_HUMIDITY;
                xQueueOverwrite(motor_queue, &motor_code);
                //printf("Move stepper motor on humidity\n");
                break;
            case 3:
                if (base_code == SET_DECIMAL) {
                    base_code = SET_HEXADECIMAL;
                } else {
                    base_code = SET_DECIMAL;
                }

                printf("toggle between\n");
                xQueueOverwrite(sensor_base_queue, &base_code);
                break;
            case 4:
                system_error(ERROR_EMERGENCY_STOP);

                motor_code = MOTOR_HALT;
                xQueueOverwrite(motor_queue, &motor_code);

                break;
            default:
                printf("Error: unknown input\n");
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
void button2_handler()
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
            vTaskDelay(175 / portTICK_PERIOD_MS);
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
                xQueueOverwrite(motor_queue, &motor_code);
                //printf("Continuously move stepper motor clockwise\n");
                break;
            case 2:
                motor_code = MOTOR_COUNTERCLOCKWISE;
                xQueueOverwrite(motor_queue, &motor_code);
                //printf("Continuously move stepper motor counterclockwise\n");
                break;
            case 3:
                motor_code = MOTOR_ALTERNATE;
                xQueueOverwrite(motor_queue, &motor_code);
                //printf("Alternate stepper motor between clockwise and counterclockwise revolutions\n");
                break;
            default:
                printf("Error: unknown input\n");
        }

        //printf("Button 2 was pushed %d time(s).\n", uiPushes);

        // reset pushes counter
        button_pushes = 0;

        taskYIELD();
    }
}


/*
 * Blocks on button3_semaphore.
 * Once initially taken, debounces button and wait for more input within a 2s timeframe.
 */
void button3_handler()
{
    TickType_t end_time = 0;
    uint button_pushes = 0;
    system_code display_code = DISPLAY_TEMPERATURE;

    while (true) {
        xSemaphoreTake(button3_semaphore, portMAX_DELAY);

        // button 3 was pushed
        end_time = xTaskGetTickCount() + 2 * configTICK_RATE_HZ;

        while (xTaskGetTickCount() < end_time) {
            // debounce
            vTaskDelay(175 / portTICK_PERIOD_MS);
            xSemaphoreTake(button3_semaphore, 0);
            button_pushes++;

            // check for more input
            if (xTaskGetTickCount() < end_time) {
                xSemaphoreTake(button3_semaphore, end_time - xTaskGetTickCount());
            }
        }

        //printf("Button 3 was pushed %d time(s).\n", uiPushes);
        switch(button_pushes) {
            case 1:
                display_code = DISPLAY_TEMPERATURE;
                xQueueSend(display_queue, &display_code, 0);
                //printf("d\n");
                break;
            case 2:
                display_code = DISPLAY_HUMIDITY;
                xQueueSend(display_queue, &display_code, 0);
                break;
            case 3:
                display_code = MOTOR_STATUS;
                xQueueSend(display_queue, &display_code, 0);
                break;
            default:
                printf("Error: unknown input\n");
        }

        // reset pushes counter
        button_pushes = 0;

        taskYIELD();
    }
}
