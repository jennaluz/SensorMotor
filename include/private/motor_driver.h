/*
 * TempHmdMotor/include/private/motor_driver.h
 *
 * Defines GPIO pins used for stepper motor.
 * Defines API functions for stepper motor.
 */

#pragma once

#include <pico/stdlib.h>

extern const uint COIL_1;
extern const uint COIL_2;
extern const uint COIL_3;
extern const uint COIL_4;

void vStepClockwise();
