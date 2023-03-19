/*
 * SensorMotor/include/private/display.h
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#include <pico/stdlib.h>


extern QueueHandle_t display_queue;
extern QueueHandle_t left_display_queue;
extern QueueHandle_t right_display_queue;
extern QueueHandle_t sensor_base_queue;
extern SemaphoreHandle_t display_semaphore;


void display_handler();
void left_display_handler();
void right_display_handler();
