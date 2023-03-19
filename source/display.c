/*
 * SensorMotor/source/display.c
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
#include "system_code.h"


QueueHandle_t display_queue = NULL;
QueueHandle_t left_display_queue = NULL;
QueueHandle_t right_display_queue = NULL;
QueueHandle_t sensor_base_queue = NULL;
SemaphoreHandle_t display_semaphore = NULL;


/*
 *
 */
void display_handler()
{
    system_code display_code = DISPLAY_TEMPERATURE;
    display_setting base_code = SET_DECIMAL;
    int temperature = 70;
    int humidity = 50;
    int sensor_digit[2] = {0, 0};

    while (true) {
        xQueueReceive(display_queue, &display_code, 0);

        switch (display_code) {
            case DISPLAY_TEMPERATURE:
                xQueuePeek(sensor_base_queue, &base_code, 0);
                xQueuePeek(temperature_queue, &temperature, 0);

                if (base_code == SET_DECIMAL) {
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

                if (base_code == SET_DECIMAL) {
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

        //taskYIELD();
        vTaskDelay(1);
    }
}


/*
 *
 */
void left_display_handler()
{
    uint8_t pin_config = 0x00;

    while (true) {
        if (xSemaphoreTake(display_semaphore, 0) == pdTRUE) {
            xQueueReceive(left_display_queue, &pin_config, 0);

            display_value(SET_LEFT, pin_config);

            xSemaphoreGive(display_semaphore);
        }

        taskYIELD();
    }
}



/*
 *
 */
void right_display_handler()
{
    uint8_t pin_config = 0x00;

    while (true) {
        if (xSemaphoreTake(display_semaphore, 0) == pdTRUE) {
            xQueueReceive(right_display_queue, &pin_config, 0);

            display_value(SET_RIGHT, pin_config);

            xSemaphoreGive(display_semaphore);
        }

        taskYIELD();
    }
}
