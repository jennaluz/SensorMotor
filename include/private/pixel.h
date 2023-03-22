/*
 * SensorMotor/include/private/pixel.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t pixel_queue;


void pixel_handler(void *parameters);
