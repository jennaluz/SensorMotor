/*
 * SensorMotor/source/display.c
 *
 * Receives data from xDisplayQueue and configures the left and right display based on data.
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


QueueHandle_t xDisplayQueue = NULL;
QueueHandle_t xLeftDisplayQueue = NULL;
QueueHandle_t xRightDisplayQueue = NULL;
SemaphoreHandle_t xDisplaySemaphore = NULL;


/*
 * Recevies input from xDisplayQueue and switches based on value.
 * Proceeds to receive data from required queues and sends left and right display value to
 *    respective queues.
 */
void vDisplayHandler()
{
    system_code_e eDisplayCode = DISPLAY_TEMPERATURE;
    sensor_base_e eSensorBase = DECIMAL;
    int iTemperature = 70;
    int iHumidity = 50;
    int iSensorDigit[2] = {0, 0};

    while (true) {
        xQueueReceive(xDisplayQueue, &eDisplayCode, 0);

        switch (eDisplayCode) {
            case DISPLAY_TEMPERATURE:
                xQueueReceive(xSensorBaseQueue, &eSensorBase, 0);
                xQueueReceive(xTemperatureQueue, &iTemperature, 0);

                if (eSensorBase == DECIMAL) {
                    iSensorDigit[0] = iTemperature / 10;
                    iSensorDigit[1] = iTemperature % 10;
                } else {
                    iSensorDigit[0] = iTemperature / 16;
                    iSensorDigit[1] = iTemperature % 16;
                }

                break;
            case DISPLAY_HUMIDITY:
                xQueueReceive(xSensorBaseQueue, &eSensorBase, 0);
                xQueueReceive(xHumidityQueue, &iHumidity, 0);

                if (eSensorBase == DECIMAL) {
                    iSensorDigit[0] = iHumidity / 10;
                    iSensorDigit[1] = iHumidity % 10;
                } else {
                    iSensorDigit[0] = iHumidity / 16;
                    iSensorDigit[1] = iHumidity % 16;
                }

                break;
            case MOTOR_STATUS:
                break;
            case ERROR_UNKNOWN_INPUT:
                break;
            case ERROR_OVERFLOW:
                break;
            case ERROR_EMERGENCY_STOP:
                iSensorDigit[0] = DISPLAY_E;
                iSensorDigit[1] = DISPLAY_E;

                break;
            default:
                printf("Error\n");
        }

        xQueueSend(xLeftDisplayQueue, &iSensorDigit[0], 0);
        xQueueSend(xRightDisplayQueue, &iSensorDigit[1], 0);

        vTaskDelay(1);
    }
}


/*
 * Uses xDisplaySemaphore to synchronize with vRightDisplayHandler.
 * Recevies data from xLeftDisplayQueue and configures pins according to data.
 */
void vLeftDisplayHandler()
{
    int iPinConfig = 0;

    while (true) {
        if (xSemaphoreTake(xDisplaySemaphore, 0) == pdTRUE) {
            xQueueReceive(xLeftDisplayQueue, &iPinConfig, 0);

            vDisplayReset();
            gpio_put(PIN_CC2, 1);
            gpio_put(PIN_CC1, 0);
            vConfigDisplay(iPinConfig);

            xSemaphoreGive(xDisplaySemaphore);
        }

        taskYIELD();
    }
}


/*
 * Uses xDisplaySemaphore to synchronize with vLeftDisplayHandler.
 * Recevies data from xRightDisplayQueue and configures pins according to data.
 */
void vRightDisplayHandler()
{
    int iPinConfig = 0;

    while (true) {
        if (xSemaphoreTake(xDisplaySemaphore, 0) == pdTRUE) {
            xQueueReceive(xRightDisplayQueue, &iPinConfig, 0);

            vDisplayReset();
            gpio_put(PIN_CC1, 1);
            gpio_put(PIN_CC2, 0);
            vConfigDisplay(iPinConfig);

            xSemaphoreGive(xDisplaySemaphore);
        }

        taskYIELD();
    }
}
