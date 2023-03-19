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
#include "motor.h"
#include "sensor.h"
#include "system_code.h"
#include "system_error.h"


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
    system_code display_status = display_code;
    system_code motor_code = MOTOR_RESET;
    display_setting base_code = SET_DECIMAL;
    bool emergency_on = false;
    int temperature = 70;
    int humidity = 50;
    int display_config[2] = {0, 0};

    while (true) {
        xQueueReceive(display_queue, &display_code, 0);

        switch (display_code) {
            case DISPLAY_REPEAT:
                break;
            case DISPLAY_TEMPERATURE:
                if (xQueueReceive(sensor_base_queue, &base_code, 0) == pdTRUE) {
                    if (base_code == SET_DECIMAL) {
                        display_config[0] = DISPLAY_D;
                        display_config[1] = DISPLAY_D;
                    } else {
                        printf("here\n");
                        display_config[0] = DISPLAY_H;
                        display_config[1] = DISPLAY_H;
                    }

                    xQueueSend(left_display_queue, &display_config[0], 0);
                    xQueueSend(right_display_queue, &display_config[1], 0);

                    vTaskDelay(3 * configTICK_RATE_HZ);
                }

                xQueuePeek(temperature_queue, &temperature, 0);

                if (base_code == SET_DECIMAL) {
                    display_config[0] = temperature / 10;
                    display_config[1] = temperature % 10;
                } else {
                    display_config[0] = temperature / 16;
                    display_config[1] = temperature % 16;
                }

                display_status = display_code;

                xQueueSend(left_display_queue, &display_config[0], 0);
                xQueueSend(right_display_queue, &display_config[1], 0);

                break;
            case DISPLAY_HUMIDITY:
                if (xQueueReceive(sensor_base_queue, &base_code, 0) == pdTRUE) {
                    if (base_code == SET_DECIMAL) {
                        display_config[0] = DISPLAY_D;
                        display_config[1] = DISPLAY_D;
                    } else {
                        display_config[0] = DISPLAY_H;
                        display_config[1] = DISPLAY_H;
                    }

                    xQueueSend(left_display_queue, &display_config[0], 0);
                    xQueueSend(right_display_queue, &display_config[1], 0);

                    vTaskDelay(3 * configTICK_RATE_HZ);
                }

                xQueuePeek(humidity_queue, &humidity, 0);

                if (base_code == SET_DECIMAL) {
                    display_config[0] = humidity / 10;
                    display_config[1] = humidity % 10;
                } else {
                    display_config[0] = humidity / 16;
                    display_config[1] = humidity % 16;
                }

                display_status = display_code;

                xQueueSend(left_display_queue, &display_config[0], 0);
                xQueueSend(right_display_queue, &display_config[1], 0);

                break;
            case MOTOR_STATUS:
                break;
            case ERROR_UNKNOWN_INPUT:
                display_config[0] = DISPLAY_X;
                display_config[1] = DISPLAY_X;

                xQueueSend(left_display_queue, &display_config[0], 0);
                xQueueSend(right_display_queue, &display_config[1], 0);

                vTaskDelay(5 * configTICK_RATE_HZ);

                if (emergency_on == true) {
                    emergency_on = false;
                    display_code = ERROR_EMERGENCY_STOP;
                } else {
                    display_code = display_status;
                }
                break;
            case ERROR_OVERFLOW:
                display_config[0] = DISPLAY_O;
                display_config[1] = DISPLAY_F;

                xQueueSend(left_display_queue, &display_config[0], 0);
                xQueueSend(right_display_queue, &display_config[1], 0);

                vTaskDelay(5 * configTICK_RATE_HZ);
                display_code = display_status;
                break;
            case ERROR_EMERGENCY_STOP:
                if (emergency_on == true) {
                    xQueueSend(motor_queue, &motor_code, 0);

                    display_code = display_status;
                    emergency_on = false;
                } else {
                    display_code = DISPLAY_REPEAT;
                    emergency_on = true;

                    display_config[0] = DISPLAY_E;
                    display_config[1] = DISPLAY_E;
                }

                xQueueSend(left_display_queue, &display_config[0], 0);
                xQueueSend(right_display_queue, &display_config[1], 0);

                break;
            default:
                system_error(ERROR_UNKNOWN_INPUT);
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
    display_config pin_config = 0;

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
    display_config pin_config = 0;

    while (true) {
        if (xSemaphoreTake(display_semaphore, 0) == pdTRUE) {
            xQueueReceive(right_display_queue, &pin_config, 0);

            display_value(SET_RIGHT, pin_config);

            xSemaphoreGive(display_semaphore);
        }

        taskYIELD();
    }
}
