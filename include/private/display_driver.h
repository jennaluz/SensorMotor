/*
 * SensorMotor/include/private/display_driver.h
 *
 * Initializes 7 Segment Display gpio pins.
 */


#pragma once


#include <pico/stdlib.h>


/*
const uint8_t DISPLAY_0 = 0x00;
const uint8_t DISPLAY_1 = 0x01;
const uint8_t DISPLAY_2 = 0x02;
const uint8_t DISPLAY_3 = 0x03;
const uint8_t DISPLAY_4 = 0x04;
const uint8_t DISPLAY_5 = 0x05;
const uint8_t DISPLAY_6 = 0x06;
const uint8_t DISPLAY_7 = 0x07;
const uint8_t DISPLAY_8 = 0x08;
const uint8_t DISPLAY_9 = 0x09;
const uint8_t DISPLAY_A = 0x0A;
const uint8_t DISPLAY_B = 0x0B;
const uint8_t DISPLAY_C = 0x0C;
const uint8_t DISPLAY_D = 0x0D;
const uint8_t DISPLAY_E = 0x0E;
const uint8_t DISPLAY_F = 0x0F;
*/


void vDisplayInit();
