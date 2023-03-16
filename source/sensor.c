/*
 * SensorMotor/source/sensor.c
 *
 * Uses the I2C port to interact with the HDC1080 device.
 * Reads in the temperature and humidity from the HDC1080 device.
 */


#include <FreeRTOS.h>
#include <queue.h>
#include <task.h>

#include <pico/stdlib.h>
#include <stdio.h>

#include "display.h"
#include "sensor.h"
#include "sensor_driver.h"


QueueHandle_t xSensorBaseQueue = NULL;
QueueHandle_t xTemperatureQueue = NULL;
QueueHandle_t xHumidityQueue = NULL;


/*
 * Reads in temperature and humidity values from HDC1080.
 * Overwrites the corresponding queue to send the most up to date value.
 */
void vSensorHandler()
{
    int iTemperature = 0;
    int iHumidity = 0;

    while (true) {
        iTemperature = fSensorReadTmp();
        xQueueOverwrite(xTemperatureQueue, &iTemperature);

        iHumidity = fSensorReadHmd();
        xQueueOverwrite(xHumidityQueue, &iHumidity);

        taskYIELD();
    }
}
