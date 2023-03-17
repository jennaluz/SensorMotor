/*
 * SensorMotor/source/display.c
 *
 * Receives data from display_queue and configures the left and right display based on data.
 */


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

#include <pico/stdlib.h>

#include <stdio.h>

#include "display.h"
#include "display_driver.h"
#include "sensor.h"
#include "sensor_driver.h"
#include "system_code.h"


QueueHandle_t display_queue = NULL;
QueueHandle_t left_display_queue = NULL;
QueueHandle_t right_display_queue = NULL;
SemaphoreHandle_t display_semaphore = NULL;


/*
 * Recevies input from xDisplayQueue and switches based on value.
 * Proceeds to receive data from required queues and sends left and right display value to
 *    respective queues.
 */
void display_handler()
{
    system_code display_code = DISPLAY_TEMPERATURE;
    sensor_base base_code = DECIMAL;
    int temperature = 70;
    int humidity = 50;
    int sensor_digit[2] = {0, 0};

    while (true) {
        xQueueReceive(display_queue, &display_code, 0);

        switch (display_code) {
            case DISPLAY_TEMPERATURE:
                xQueuePeek(sensor_base_queue, &base_code, 0);
                printf("base %d\n", base_code);
                xQueuePeek(temperature_queue, &temperature, 0);

                if (base_code == DECIMAL) {
                    sensor_digit[0] = temperature / 10;
                    sensor_digit[1] = temperature % 10;
                } else {
                    sensor_digit[0] = temperature / 16;
                    sensor_digit[1] = temperature % 16;
                }

                break;
            case DISPLAY_HUMIDITY:
                xQueuePeek(sensor_base_queue, &base_code, 0);
                xQueuePeek(humidity_queue, &humidity, 0);

                if (base_code == DECIMAL) {
                    sensor_digit[0] = humidity / 10;
                    sensor_digit[1] = humidity % 10;
                } else {
                    sensor_digit[0] = humidity / 16;
                    sensor_digit[1] = humidity % 16;
                }

                break;
            case MOTOR_STATUS:
                break;
            case ERROR_UNKNOWN_INPUT:
                break;
            case ERROR_OVERFLOW:
                break;
            case ERROR_EMERGENCY_STOP:
                sensor_digit[0] = DISPLAY_E;
                sensor_digit[1] = DISPLAY_E;

                break;
            default:
                printf("Error\n");
        }

        xQueueSend(left_display_queue, &sensor_digit[0], 0);
        xQueueSend(right_display_queue, &sensor_digit[1], 0);

        vTaskDelay(1);
    }
}


/*
 * Uses display_semaphore to synchronize with right_display_handler().
 * Recevies data from left_display_queue and configures pins according to data.
 */
void left_display_handler()
{
    int pin_config = 0;

    while (true) {
        if (xSemaphoreTake(display_semaphore, 0) == pdTRUE) {
            xQueueReceive(left_display_queue, &pin_config, 0);

            gpio_put(PIN_CC2, 1);
            config_display(pin_config);
            gpio_put(PIN_CC1, 0);

            xSemaphoreGive(display_semaphore);
        }

        taskYIELD();
    }
}


/*
 * Uses display_semaphore to synchronize with left_display_handler().
 * Recevies data from right_display_queue and configures pins according to data.
 */
void right_display_handler()
{
    int pin_config = 0;

    while (true) {
        if (xSemaphoreTake(display_semaphore, 0) == pdTRUE) {
            xQueueReceive(right_display_queue, &pin_config, 0);

            gpio_put(PIN_CC1, 1);
            config_display(pin_config);
            gpio_put(PIN_CC2, 0);

            xSemaphoreGive(display_semaphore);
        }

        taskYIELD();
    }
}
