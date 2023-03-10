/*
 * SensorMotor/include/private/motor.h
 *
 * Defines task that handles the Stepper Motor.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t xMotorQueue;


void vMotorHandler();
