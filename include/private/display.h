/*
 * SensorMotor/include/private/display.h
 *
 * Handles input for the 7 Segment Display.
 * Uses API calls to configure the 7 Segment Display.
 * Uses the display_semaphore to synchronize the left and right displays.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>


extern QueueHandle_t display_queue;
extern QueueHandle_t left_display_queue;
extern QueueHandle_t right_display_queue;
extern QueueHandle_t sensor_base_queue;
extern SemaphoreHandle_t display_semaphore;


void display_handler(void *parameters);
void left_display_handler(void *parameters);
void right_display_handler(void *parameters);
