/*
* SensorMotor/source/display_driver.c
*/


#include "display_driver.h"
#include <pico/stdlib.h>


/*
 * Initializes all GPIO pins for the 7 Segment Display
 */
void display_init()
{
    gpio_init(PIN_CC1);
    gpio_init(PIN_CC2);

    gpio_init(PIN_A);
    gpio_init(PIN_B);
    gpio_init(PIN_C);
    gpio_init(PIN_D);
    gpio_init(PIN_E);
    gpio_init(PIN_F);
    gpio_init(PIN_G);
    gpio_init(PIN_DP);

    gpio_set_dir(PIN_CC1, GPIO_OUT);
    gpio_set_dir(PIN_CC2, GPIO_OUT);

    gpio_set_dir(PIN_A, GPIO_OUT);
    gpio_set_dir(PIN_B, GPIO_OUT);
    gpio_set_dir(PIN_C, GPIO_OUT);
    gpio_set_dir(PIN_D, GPIO_OUT);
    gpio_set_dir(PIN_E, GPIO_OUT);
    gpio_set_dir(PIN_F, GPIO_OUT);
    gpio_set_dir(PIN_G, GPIO_OUT);
    gpio_set_dir(PIN_DP, GPIO_OUT);

    gpio_put(PIN_CC1, 1);
    gpio_put(PIN_CC2, 1);
}


/*
*
*/
void display_reset()
{
    gpio_put(PIN_A, 0);
    gpio_put(PIN_B, 0);
    gpio_put(PIN_C, 0);
    gpio_put(PIN_D, 0);
    gpio_put(PIN_E, 0);
    gpio_put(PIN_F, 0);
    gpio_put(PIN_G, 0);
    gpio_put(PIN_DP, 0);
}

void display_value(display_setting digit, display_config pin_config)
{
    display_reset();

    if (digit == SET_LEFT) {
        gpio_put(PIN_CC2, 1);
        gpio_put(PIN_CC1, 0);
    } else {
        gpio_put(PIN_CC1, 1);
        gpio_put(PIN_CC2, 0);
    }

    switch(pin_config) {
        case DISPLAY_0:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            break;
        case DISPLAY_1:
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            break;
        case DISPLAY_2:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_3:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_4:
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_5:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_6:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_7:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            break;
        case DISPLAY_8:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_9:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_A:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_B:
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_C:
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_CC:
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_D:
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_E:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_F:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_H:
            gpio_put(PIN_C, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_O:
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case DISPLAY_X:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_G, 1);
            break;
    }
}
