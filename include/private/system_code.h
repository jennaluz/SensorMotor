/*
 * SensorMotor/include/private/codes.h
 *
 * Defines codes for the Stepper Motor, 7 Segment Display, and error codes.
 */


#pragma once


typedef enum system_code {
    DISPLAY_REPEAT          = -1,
    DISPLAY_TEMPERATURE     = 0,
    DISPLAY_HUMIDITY        = 1,
    MOTOR_RESET             = 2,
    MOTOR_CLOCKWISE         = 3,
    MOTOR_COUNTERCLOCKWISE  = 4,
    MOTOR_ALTERNATE         = 5,
    MOTOR_TEMPERATURE       = 6,
    MOTOR_HUMIDITY          = 7,
    MOTOR_HALT              = 8,
    MOTOR_STATUS            = 9,
    ERROR_UNKNOWN_INPUT     = 10,
    ERROR_OVERFLOW          = 11,
    ERROR_EMERGENCY_STOP    = 12,
} system_code;
