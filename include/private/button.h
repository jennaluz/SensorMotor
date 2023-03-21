/*
 * SensorMotor/include/private/button.h
 *
 * Initializes button IRQs.
 * Defines button tasks for each button.
 * Uses a callback function and semaphores to handle button input.
 */


#pragma once


#include <FreeRTOS.h>
#include <semphr.h>

#include <pico/stdlib.h>


extern SemaphoreHandle_t button1_semaphore;
extern SemaphoreHandle_t button2_semaphore;
extern SemaphoreHandle_t button3_semaphore;


void button_irq_init();
void button_callback(uint gpio, uint32_t events);
void button1_handler(void *parameters);
void button2_handler(void *parameters);
void button3_handler(void *parameters);
