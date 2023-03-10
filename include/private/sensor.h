/*
 * SensorMotor/include/private/sensor.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t xSensorBaseQueue;
extern QueueHandle_t xTemperatureQueue;
extern QueueHandle_t xHumidityQueue;

typedef enum sensor_base_e {
    DECIMAL     = 0,
    HEXADECIMAL = 1,
} sensor_base_e;


void vSensorHandler();
