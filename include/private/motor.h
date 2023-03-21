/*
 * SensorMotor/include/private/motor.h
 *
 * Handles Stepper Motor input through motor_queue.
 * Sends the current direction of the Stepper Motor through motor_direction_queue.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t motor_queue;
extern QueueHandle_t motor_direction_queue;


void motor_handler(void *parameters);
