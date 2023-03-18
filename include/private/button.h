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


extern SemaphoreHandle_t xButton1Semaphore;
extern SemaphoreHandle_t xButton2Semaphore;
extern SemaphoreHandle_t xButton3Semaphore;


void vButtonIRQInit();
void vButtonCallback(uint gpio, uint32_t events);
void vButton1Handler();
void vButton2Handler();
void vButton3Handler();
