/*
 * SensorMotor/include/private/motor_driver.h
 *
 * Initializes Stepper Motor GPIO pins.
 * Defines API functions to move stepper motor.
 */


#pragma once


#include <pico/stdlib.h>


void vMotorInit();
void vMotorReset();
void vMotorClockwise();
void vMotorCounterclockwise();
void vMotorAlternate();
void vMotorHalt();
void vMotorIncrement();
void vMotorDecrement();
