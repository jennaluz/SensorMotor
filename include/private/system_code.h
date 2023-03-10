/*
 * SensorMotor/include/private/codes.h
 *
 * Defines codes for the Stepper Motor, 7 Segment Display, and error codes.
 */


#pragma once


typedef enum system_code_e {
    DISPLAY_TEMPERATURE     = 0,
    DISPLAY_HUMIDITY        = 1,
    MOTOR_CLOCKWISE         = 2,
    MOTOR_COUNTERCLOCKWISE  = 3,
    MOTOR_ALTERNATE         = 4,
    MOTOR_TEMPERATURE       = 5,
    MOTOR_HUMIDITY          = 6,
    MOTOR_HALT              = 7,
    MOTOR_STATUS            = 8,
    ERROR_UNKNOWN_INPUT     = 9,
    ERROR_OVERFLOW          = 10,
    ERROR_EMERGENCY_STOP    = 11,
} system_code_e;
