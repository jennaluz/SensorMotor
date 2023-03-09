/*
 * SensorMotor/include/private/motor.h
 *
 * Defines task that handles the Stepper Motor.
 */


#pragma once


#include <FreeRTOS.h>
#include <queue.h>


extern QueueHandle_t xMotorQueue;

typedef enum motor_code_e {
    MOTOR_CLOCKWISE         = 2,
    MOTOR_COUNTERCLOCKWISE  = 3,
    MOTOR_ALTERNATE         = 4,
    MOTOR_TEMPERATURE       = 5,
    MOTOR_HUMIDITY          = 6,
    MOTOR_HALT              = 7,
    MOTOR_STATUS            = 8,
} motor_code_e;


void vMotorHandler();
