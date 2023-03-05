/*
* SensorMotor/source/display_driver.c
*/


#include <pico/stdlib.h>


const uint DISPLAY_CC1  = 11; // left digit
const uint DISPLAY_CC2  = 10; // right digit

const uint DISPLAY_A    = 26;
const uint DISPLAY_B    = 27;
const uint DISPLAY_C    = 29;
const uint DISPLAY_D    = 18;
const uint DISPLAY_E    = 25;
const uint DISPLAY_F    = 7;
const uint DISPLAY_G    = 28;
const uint DISPLAY_DP   = 24;


/*
 * Initializes all GPIO pins for the 7 Segment Display
 */
void vDisplayInit()
{
    gpio_init(DISPLAY_CC1);
    gpio_init(DISPLAY_CC2);

    gpio_init(DISPLAY_A);
    gpio_init(DISPLAY_B);
    gpio_init(DISPLAY_C);
    gpio_init(DISPLAY_D);
    gpio_init(DISPLAY_E);
    gpio_init(DISPLAY_F);
    gpio_init(DISPLAY_G);
    gpio_init(DISPLAY_DP);

    gpio_set_dir(DISPLAY_CC1, GPIO_OUT);
    gpio_set_dir(DISPLAY_CC2, GPIO_OUT);

    gpio_set_dir(DISPLAY_A, GPIO_OUT);
    gpio_set_dir(DISPLAY_B, GPIO_OUT);
    gpio_set_dir(DISPLAY_C, GPIO_OUT);
    gpio_set_dir(DISPLAY_D, GPIO_OUT);
    gpio_set_dir(DISPLAY_E, GPIO_OUT);
    gpio_set_dir(DISPLAY_F, GPIO_OUT);
    gpio_set_dir(DISPLAY_G, GPIO_OUT);
    gpio_set_dir(DISPLAY_DP, GPIO_OUT);

    gpio_put(DISPLAY_CC1, 1);
    gpio_put(DISPLAY_CC2, 1);
}
