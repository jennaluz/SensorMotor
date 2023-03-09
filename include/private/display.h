/*
 * SensorMotor/include/private/display.h
 */


#pragma once

#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t xDisplayQueue;


typedef enum display_code_e {
    DISPLAY_TEMPERATURE = 0,
    DISPLAY_HUMIDITY    = 1,
} display_code_e;


void vDisplayHandler();
