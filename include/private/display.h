/*
 * SensorMotor/include/private/display.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t xDisplayQueue;


void vDisplayHandler();
