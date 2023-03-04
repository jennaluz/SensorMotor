/*
 * SensorMotor/include/private/hdc1080_driver.h
 */

#include <hardware/i2c.h>
#include <math.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "hdc1080_driver.h"

#define I2C_PORT i2c1
const uint8_t HDC_ADDR          = 0x40;
const uint8_t HDC_TMP_REG       = 0x00;
const uint8_t HDC_HMD_REG       = 0x01;
const uint8_t HDC_CONFIG_REG    = 0x02;

/*
 * Initialize I2C port, and SDA and SCL pins.
 */
void vHDC1080Init()
{
    // initialize default port on default SDA and SCL pins
    i2c_init(I2C_PORT, 100 * 1000);    // put I2C hardware into known state and enable

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // make I2C pins available to picotool
    //bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    return;
}

/*
 *
 */
void vHDC1080ReadTmp()
{
    uint8_t uiTmpReg = HDC_TMP_REG;
    uint8_t uiTmpValue[2] = {};

    int iReturn = 0;
    uint16_t uiReturnValue = 0;
    float fFahrenheit = 0;

    // point to temperature register
    iReturn = i2c_write_blocking(I2C_PORT, HDC_ADDR, &uiTmpReg, 1, false);
    sleep_ms(25);

    // read from temperature register
    iReturn = i2c_read_blocking(I2C_PORT, HDC_ADDR, uiTmpValue, 2, false);
    uiReturnValue = (uiTmpValue[0] << 8) | uiTmpValue[1];

    // convert return value to fahrenheit
    fFahrenheit = (((uiReturnValue / pow(2, 16)) * 165 - 40) * 9 / 5) + 32;
    printf("%f degrees F\n", fFahrenheit);

    return;
}

/*
 *
 */
void vHDC1080ReadHmd()
{

}
