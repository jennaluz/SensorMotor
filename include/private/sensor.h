/*
 * SensorMotor/include/private/sensor.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t sensor_base_queue;
extern QueueHandle_t temperature_queue;
extern QueueHandle_t humidity_queue;

typedef enum sensor_base_e {
    DECIMAL     = 0,
    HEXADECIMAL = 1,
} sensor_base_e;


void vSensorHandler();
