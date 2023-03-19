/*
 * SensorMotor/include/private/motor_driver.h
 *
 * Initializes Stepper Motor GPIO pins.
 * Defines API functions to move the Stepper Motor.
 */


#pragma once


void motor_init();
void motor_reset();
void motor_clockwise();
void motor_counterclockwise();
void motor_halt();
void motor_increment();
void motor_decrement();
