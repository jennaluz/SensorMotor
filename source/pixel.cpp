/*
 * SensorMotor/source/pixel.cpp
 */


#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <pico/stdlib.h>
#include <WS2812.hpp>

#include <stdio.h>

#include "motor.h"
#include "pixel.h"
#include "sensor.h"
#include "system_code.h"


QueueHandle_t pixel_queue = NULL;

const uint PIXEL_PIN    = 20;
const uint PIXEL_LENGTH = 4;


const uint32_t pixel_config[6] = {
    0x00000100, // red
    0x02000401, // orange
    0x01000202, // yellow
    0x01000001, // green
    0x00010000, // blue
    0x00010100, // purple
};

typedef enum pixel_config_index {
    PIXEL_RED     = 0,
    PIXEL_ORANGE  = 1,
    PIXEL_YELLOW  = 2,
    PIXEL_GREEN   = 3,
    PIXEL_BLUE    = 4,
    PIXEL_PURPLE  = 5,
} pixel_config_index;


void pixel_handler(void *parameters)
{
    system_code pixel_code = DISPLAY_TEMPERATURE;
    system_code motor_code;

    int old_tmp = 70;
    int new_tmp = 0;
    int old_hmd = 50;
    int new_hmd = 0;
    int sensor_diff = 0;

    // initialize pixel settings
    WS2812 pixel_strip(PIXEL_PIN, PIXEL_LENGTH, pio0, 0, WS2812::FORMAT_WRGB);

    pixel_strip.setPixelColor(0, pixel_config[PIXEL_RED]);
    pixel_strip.setPixelColor(1, pixel_config[PIXEL_YELLOW]);
    pixel_strip.setPixelColor(2, pixel_config[PIXEL_RED]);
    pixel_strip.setPixelColor(3, pixel_config[PIXEL_GREEN]);
    pixel_strip.show();

    while (true) {
        if (pixel_code != ERROR_EMERGENCY_STOP) {
            // check temperature
            xQueuePeek(temperature_queue, &new_tmp, 0);
            sensor_diff = new_tmp - old_tmp;

            if (sensor_diff > 0) {
                pixel_strip.setPixelColor(0, 4 * pixel_config[PIXEL_RED]);
                pixel_strip.show();
                vTaskDelay(3);
            } else if (sensor_diff < 0) {
                pixel_strip.setPixelColor(0, pixel_config[PIXEL_RED]);
                pixel_strip.show();
                vTaskDelay(3);
            } else {}

            old_tmp = new_tmp;

            // check humidity
            xQueuePeek(humidity_queue, &new_hmd, 0);
            sensor_diff = new_hmd - old_hmd;

            if (sensor_diff > 0) {
                pixel_strip.setPixelColor(1, 2 * pixel_config[PIXEL_YELLOW]);
                pixel_strip.show();
                vTaskDelay(3);
            } else if (sensor_diff < 0) {
                pixel_strip.setPixelColor(1, pixel_config[PIXEL_YELLOW]);
                pixel_strip.show();
                vTaskDelay(3);
            } else {}

            old_hmd = new_hmd;

            // check motor status
            xQueuePeek(motor_direction_queue, &motor_code, 0);

            switch (motor_code) {
                case MOTOR_CLOCKWISE:
                    pixel_strip.setPixelColor(3, pixel_config[PIXEL_GREEN]);
                    pixel_strip.show();
                    break;
                case MOTOR_COUNTERCLOCKWISE:
                    pixel_strip.setPixelColor(3, pixel_config[PIXEL_BLUE]);
                    pixel_strip.show();
                    break;
                case MOTOR_HALT:
                    pixel_strip.setPixelColor(3, pixel_config[PIXEL_ORANGE]);
                    pixel_strip.show();
                    break;
                default:
                    break;
            }

            vTaskDelay(3);
        } else {
            for (int i = 0; i < 6; i++) {
                pixel_strip.setPixelColor(0, pixel_config[i % 6]);
                pixel_strip.setPixelColor(1, pixel_config[(i + 1) % 6]);
                pixel_strip.setPixelColor(2, pixel_config[(i + 2) % 6]);
                pixel_strip.setPixelColor(3, pixel_config[(i + 3) % 6]);
                pixel_strip.show();
                //vTaskDelay(0.5 * configTICK_RATE_HZ);
                vTaskDelay(8);
            }
        }

        // check display status
        if (xQueueReceive(pixel_queue, &pixel_code, 0) == pdTRUE) {
            printf("pixel %d\n", pixel_code);
            switch (pixel_code) {
                case DISPLAY_TEMPERATURE:
                    printf("temp\n");
                    pixel_strip.setPixelColor(2, pixel_config[PIXEL_RED]);
                    pixel_strip.show();
                    break;
                case DISPLAY_HUMIDITY:
                    printf("hmd\n");
                    pixel_strip.setPixelColor(2, pixel_config[PIXEL_YELLOW]);
                    pixel_strip.show();
                    break;
                case MOTOR_STATUS:
                    printf("status\n");
                    pixel_strip.setPixelColor(2, pixel_config[PIXEL_PURPLE]);
                    pixel_strip.show();
                    break;
                default:
                    printf("%d\n", pixel_code);
                    break;
            }
        }

        taskYIELD();
    }
}
