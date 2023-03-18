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

void display_value(int config)
{
    switch(config) {
        case 0:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            break;
        case 1:
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            break;
        case 2:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case 3:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_G, 1);
            break;
        case 4:
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 5:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 6:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 7:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            break;
        case 8:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 9:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 10:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 11:
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 12:
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case 13:
            gpio_put(PIN_B, 1);
            gpio_put(PIN_C, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_G, 1);
            break;
        case 14:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_D, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
        case 15:
            gpio_put(PIN_A, 1);
            gpio_put(PIN_E, 1);
            gpio_put(PIN_F, 1);
            gpio_put(PIN_G, 1);
            break;
    }
}
