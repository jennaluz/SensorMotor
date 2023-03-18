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
    system_code_e display_code = DISPLAY_TEMPERATURE;
    sensor_base_e base_code = DECIMAL;
    int temperature = 70;
    int humidity = 50;
    int sensor_digit[2] = {0, 0};
    /*
    uint8_t uiDisplayConfig[19] = {
        0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6, // digits
        0xEE, 0x3E, 0x1A, 0x7A, 0x9E, 0x8E, 0x1E, 0x3A, 0x92,       // characters
    };
    */

    while (true) {
        xQueueReceive(display_queue, &display_code, 0);

        switch (display_code) {
            case DISPLAY_TEMPERATURE:
                xQueuePeek(sensor_base_queue, &base_code, 0);
                xQueuePeek(temperature_queue, &temperature, 0);

                if (base_code == DECIMAL) {
                    sensor_digit[0] = temperature / 10;
                    sensor_digit[1] = temperature % 10;
                } else {
                    sensor_digit[0] = temperature / 16;
                    sensor_digit[1] = temperature % 16;
                }

                xQueueSend(left_display_queue, &sensor_digit[0], 0);
                xQueueSend(right_display_queue, &sensor_digit[1], 0);

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

                xQueueSend(left_display_queue, &sensor_digit[0], 0);
                xQueueSend(right_display_queue, &sensor_digit[1], 0);

                break;
            case MOTOR_STATUS:
                break;
            case ERROR_UNKNOWN_INPUT:
                break;
            case ERROR_OVERFLOW:
                break;
            case ERROR_EMERGENCY_STOP:
                break;
            default:
                printf("Error\n");
        }

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
            //printf("L%d\n", uiPinConfig);
            gpio_put(PIN_CC2, 1);
            display_value(pin_config);
            gpio_put(PIN_CC1, 0);

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

            gpio_put(PIN_CC1, 1);
            display_value(pin_config);
            gpio_put(PIN_CC2, 0);

            xSemaphoreGive(display_semaphore);
        }

        taskYIELD();
    }
}
