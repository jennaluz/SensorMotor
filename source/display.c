/*
 * SensorMotor/source/display.c
 */


#include <FreeRTOS.h>
#include <queue.h>
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


/*
 *
 */
void vDisplayHandler()
{
    system_code_e eDisplayCode = DISPLAY_TEMPERATURE;
    int iTemperature = 0;
    int iHumidity = 0;
    char cSensor[2] = {'0', '0'};

    while (true) {
        xQueueReceive(xDisplayQueue, &eDisplayCode, 0);

        switch (eDisplayCode) {
            case DISPLAY_TEMPERATURE:
                xQueueReceive(xTemperatureQueue, &iTemperature, 0);

                cSensor[0] = iTemperature / 10;
                cSensor[1] = iTemperature % 10;

                //xQueueSend(xLeftDisplayQueue, &)
                break;
            case DISPLAY_HUMIDITY:
                xQueueReceive(xHumidityQueue, &iHumidity, 0);
                break;
            case MOTOR_CLOCKWISE:
                break;
            case MOTOR_COUNTERCLOCKWISE:
                break;
            case MOTOR_ALTERNATE:
                break;
            case MOTOR_TEMPERATURE:
                break;
            case MOTOR_HUMIDITY:
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
    }
}
