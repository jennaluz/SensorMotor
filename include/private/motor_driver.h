/*
 * SensorMotor/include/private/motor_driver.h
 *
 * Initializes Stepper Motor GPIO pins.
 * Defines API functions to move stepper motor.
 */


#pragma once


#include <pico/stdlib.h>


void motor_init();
void motor_reset();
void motor_clockwise();
void motor_counterclockwise();
void motor_halt();
void motor_increment();
void motor_decrement();
