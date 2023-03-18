/*
 * SensorMotor/include/private/sensor_driver.h
 *
 * Initializes I2C port and connects to HDC1080.
 * Defines API functions to read in temperature and humditiy.
 */


#pragma once


void sensor_init();
float sensor_read_tmp();
float sensor_read_hmd();
