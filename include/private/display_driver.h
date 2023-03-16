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

typedef enum display_config_e {
    DISPLAY_0 = 0,
    DISPLAY_1 = 1,
    DISPLAY_2 = 2,
    DISPLAY_3 = 3,
    DISPLAY_4 = 4,
    DISPLAY_5 = 5,
    DISPLAY_6 = 6,
    DISPLAY_7 = 7,
    DISPLAY_8 = 8,
    DISPLAY_9 = 9,
    DISPLAY_A = 10,
    DISPLAY_B = 11,
    DISPLAY_C = 12,
    DISPLAY_D = 13,
    DISPLAY_E = 14,
    DISPLAY_F = 15,
} display_config_e;


void vDisplayInit();
void vDisplayReset();
void vConfigDisplay(display_config_e eConfig);
