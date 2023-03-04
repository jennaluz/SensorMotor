/*
 * SensorMotor/include/private/motor_driver.h
 *
 * Defines GPIO pins used for stepper motor.
 * Defines API functions for stepper motor.
 */

#pragma once

#include <pico/stdlib.h>

void vMotorInit();
void vMotorReset();
void vMotorClockwise();
void vMotorCounterclockwise();
void vMotorAlternate();
