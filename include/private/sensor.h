/*
 * SensorMotor/include/private/sensor.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t temperature_queue;
extern QueueHandle_t humidity_queue;


void sensor_handler();
