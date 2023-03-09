/*
 * SensorMotor/include/private/error.h
 */


#pragma once


typedef enum error_code_e {
    ERROR_UNKNOWN_INPUT   = 9,
    ERROR_OVERFLOW        = 10,
    ERROR_EMERGENCY_STOP  = 11,
} error_code_e;


void vError(error_code_e eError);
