/*
 * SensorMotor/source/pixel.cpp
 */


#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include "WS2812.hpp"

#include <stdio.h>

#include "pixel.h"
#include "system_code.h"


QueueHandle_t pixel_queue = NULL;

const uint PIXEL_PIN    = 20;
const uint PIXEL_LENGTH = 4;


void pixel_handler(void *parameters)
{
    system_code pixel_code;
    uint32_t pixel0;
    uint32_t pixel1;
    uint32_t pixel2;
    uint32_t pixel3;

    // initialize pixel settings
    WS2812 pixel_strip(PIXEL_PIN, PIXEL_LENGTH, pio0, 0, WS2812::FORMAT_WRGB);

    pixel_strip.setPixelColor(1, 1, 1, 1, 1);
    pixel_strip.setPixelColor(2, 1, 1, 1, 1);
    pixel_strip.setPixelColor(3, 1, 1, 1, 1);
    pixel_strip.setPixelColor(0, 0xFF, 0xFF, 0xFF, 0xFF);
    pixel_strip.show();

    while (true) {
        // check temperature and humidity

        if (xQueueReceive(pixel_queue, &pixel_code, 0) == pdTRUE) {
            switch (pixel_code) {
                case DISPLAY_TEMPERATURE:
                    printf("pixel\n");
                    break;
                case DISPLAY_HUMIDITY:
                    break;
                case MOTOR_STATUS:
                    break;
                case ERROR_EMERGENCY_STOP:
                    break;
                default:
                    break;
            }
        }

        taskYIELD();
    }
}
