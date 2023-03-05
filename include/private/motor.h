/*
 * SensorMotor/include/private/motor.h
 *
 * Defines task that handles the Stepper Motor.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t xMotorQueue;

typedef enum motor_status_e {
    MOTOR_CLOCKWISE         = 0,
    MOTOR_COUNTERCLOCKWISE  = 1,
    MOTOR_ALTERNATE         = 2,
} motor_status_e;


void vMotorHandler();
