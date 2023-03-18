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


QueueHandle_t xDisplayQueue = NULL;
QueueHandle_t xLeftDisplayQueue = NULL;
QueueHandle_t xRightDisplayQueue = NULL;
SemaphoreHandle_t xDisplaySemaphore = NULL;

enum display_index_e {
    DISPLAY_C = 12,
    DISPLAY_D = 13,
    DISPLAY_E = 14,
    DISPLAY_F = 15,
    DISPLAY_H = 16,
    DISPLAY_O = 17,
    DISPLAY_X = 18,
};


/*
 *
 */
void vDisplayHandler()
{
    system_code_e eDisplayCode = DISPLAY_TEMPERATURE;
    sensor_base_e eSensorBase = DECIMAL;
    int iTemperature = 70;
    int iHumidity = 50;
    int sensor_digit[2] = {0, 0};
    /*
    uint8_t uiDisplayConfig[19] = {
        0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6, // digits
        0xEE, 0x3E, 0x1A, 0x7A, 0x9E, 0x8E, 0x1E, 0x3A, 0x92,       // characters
    };
    */

    while (true) {
        xQueueReceive(xDisplayQueue, &eDisplayCode, 0);

        switch (eDisplayCode) {
            case DISPLAY_TEMPERATURE:
                xQueuePeek(xSensorBaseQueue, &eSensorBase, 0);
                xQueuePeek(xTemperatureQueue, &iTemperature, 0);

                if (eSensorBase == DECIMAL) {
                    sensor_digit[0] = iTemperature / 10;
                    sensor_digit[1] = iTemperature % 10;
                    //xQueueSend(xLeftDisplayQueue, &uiDisplayConfig[iTemperature / 10], 0);
                    //xQueueSend(xRightDisplayQueue, &uiDisplayConfig[iTemperature % 10], 0);
                } else {
                    sensor_digit[0] = iTemperature / 16;
                    sensor_digit[1] = iTemperature % 16;
                    //xQueueSend(xLeftDisplayQueue, &uiDisplayConfig[iTemperature / 16], 0);
                    //xQueueSend(xRightDisplayQueue, &uiDisplayConfig[iTemperature % 16], 0);
                }

                xQueueSend(xLeftDisplayQueue, &sensor_digit[0], 0);
                xQueueSend(xRightDisplayQueue, &sensor_digit[1], 0);

                break;
            case DISPLAY_HUMIDITY:
                xQueuePeek(xSensorBaseQueue, &eSensorBase, 0);
                xQueuePeek(xHumidityQueue, &iHumidity, 0);

                if (eSensorBase == DECIMAL) {
                    sensor_digit[0] = iHumidity / 10;
                    sensor_digit[1] = iHumidity % 10;
                    //xQueueSend(xLeftDisplayQueue, &uiDisplayConfig[iHumidity / 10], 0);
                    //xQueueSend(xRightDisplayQueue, &uiDisplayConfig[iHumidity % 10], 0);
                } else {
                    sensor_digit[0] = iHumidity / 16;
                    sensor_digit[1] = iHumidity % 16;
                    //xQueueSend(xLeftDisplayQueue, &uiDisplayConfig[iHumidity / 16], 0);
                    //xQueueSend(xRightDisplayQueue, &uiDisplayConfig[iHumidity % 16], 0);
                }

                xQueueSend(xLeftDisplayQueue, &sensor_digit[0], 0);
                xQueueSend(xRightDisplayQueue, &sensor_digit[1], 0);

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
void vLeftDisplayHandler()
{
    uint8_t uiPinConfig = 0x00;
    uint8_t uiMask = 0x01;

    while (true) {
        if (xSemaphoreTake(xDisplaySemaphore, 0) == pdTRUE) {
            xQueueReceive(xLeftDisplayQueue, &uiPinConfig, 0);
            //printf("L%d\n", uiPinConfig);
            gpio_put(PIN_CC2, 1);
            vDisplayReset();
            vConfigDisplay(uiPinConfig);

            gpio_put(PIN_CC1, 0);
            xSemaphoreGive(xDisplaySemaphore);
        }

        taskYIELD();
    }
}



/*
 *
 */
void vRightDisplayHandler()
{
    uint8_t uiPinConfig = 0x00;
    uint8_t uiMask = 0x01;

    while (true) {
        if (xSemaphoreTake(xDisplaySemaphore, 0) == pdTRUE) {
            xQueueReceive(xRightDisplayQueue, &uiPinConfig, 0);
            //printf("R%d\n", uiPinConfig);
            gpio_put(PIN_CC1, 1);
            vDisplayReset();
            vConfigDisplay(uiPinConfig);

            gpio_put(PIN_CC2, 0);
            xSemaphoreGive(xDisplaySemaphore);
        }

        taskYIELD();
    }
}
