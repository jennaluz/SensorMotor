/*
 * SensorMotor/include/private/display.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#include <pico/stdlib.h>


extern QueueHandle_t xDisplayQueue;
extern QueueHandle_t xLeftDisplayQueue;
extern QueueHandle_t xRightDisplayQueue;
extern SemaphoreHandle_t display_semaphore;


void vDisplayHandler();
void vLeftDisplayHandler();
void vRightDisplayHandler();
