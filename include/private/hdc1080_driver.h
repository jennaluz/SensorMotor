/*
 * SensorMotor/include/private/hdc1080_driver.h
 *
 * Initializes I2C port and connects to HDC1080.
 * Defines API functions to read in temperature and humditiy.
 */

#pragma once


void vHDC1080Init();
void vHDC1080ReadTmp();
void vHDC1080ReadHmd();
