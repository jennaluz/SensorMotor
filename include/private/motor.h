/*
 * SensorMotor/include/private/motor.h
 *
 * Defines task that handles the Stepper Motor.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t motor_queue;
extern QueueHandle_t motor_direction_queue;


void motor_handler();
