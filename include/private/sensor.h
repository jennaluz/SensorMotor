/*
 * SensorMotor/include/private/sensor.h
 *
 * Uses HDC1080 API calls to receive temperature and relative humidity.
 * Constantly sends input to their respective queues.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t temperature_queue;
extern QueueHandle_t humidity_queue;


void sensor_handler(void *parameters);
