/*
 * SensorMotor/include/private/display_driver.h
 *
 * Initializes 7 Segment Display gpio pins.
 */


#pragma once


#include <pico/stdlib.h>


typedef enum display_pinout_e {
    PIN_CC1 = 11, // left digit
    PIN_CC2 = 10, // right digit
    PIN_A   = 26,
    PIN_B   = 27,
    PIN_C   = 29,
    PIN_D   = 18,
    PIN_E   = 25,
    PIN_F   = 7,
    PIN_G   = 28,
    PIN_DP  = 24,
} display_pinout_e;


void vDisplayInit();
void vDisplayReset();
void vConfigDisplay(int config);
