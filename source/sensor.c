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


QueueHandle_t sensor_base_queue = NULL;
QueueHandle_t temperature_queue = NULL;
QueueHandle_t humidity_queue = NULL;


/*
 * Reads in temperature and humidity values from HDC1080.
 * Overwrites the corresponding queue to send the most up to date value.
 */
void sensor_handler()
{
    int temperature = 0;
    int humidity = 0;

    while (true) {
        temperature = sensor_read_tmp();
        xQueueOverwrite(temperature_queue, &temperature);

        humidity = sensor_read_hmd();
        xQueueOverwrite(humidity_queue, &humidity);

        taskYIELD();
    }
}
