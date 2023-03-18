/*
 * SensorMotor/include/private/sensor_driver.h
 *
 * Initializes I2C port and connects to HDC1080.
 * Reads in temperature and humidity from the HDC1080.
 */


#include <FreeRTOS.h>
#include <task.h>

#include <hardware/i2c.h>
#include <math.h>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "sensor_driver.h"


const uint8_t HDC_ADDR          = 0x40;
const uint8_t HDC_TMP_REG       = 0x00;
const uint8_t HDC_HMD_REG       = 0x01;
const uint8_t HDC_CONFIG_REG    = 0x02;


/*
 * Initialize I2C port, and SDA and SCL pins.
 */
void sensor_init()
{
    // initialize default port on default SDA and SCL pins
    i2c_init(PICO_DEFAULT_I2C_INSTANCE, 100 * 1000);    // put I2C hardware into known state and enable

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}


/*
 * Reads in the HDC1080 temperature register.
 * Converts value into degrees fahrenheit and returns that value.
 */
float sensor_read_tmp()
{
    uint8_t reg_return[2] = {};
    int8_t return_bytes = 0;
    uint16_t return_value = 0;
    float fahrenheit = 0;

    // point to temperature register
    return_bytes = i2c_write_blocking(PICO_DEFAULT_I2C_INSTANCE, HDC_ADDR, &HDC_TMP_REG, 1, false);
    vTaskDelay(20);

    // read from temperature register
    return_bytes = i2c_read_blocking(PICO_DEFAULT_I2C_INSTANCE, HDC_ADDR, reg_return, 2, false);
    return_value = (reg_return[0] << 8) | reg_return[1];

    // convert return value to fahrenheit
    fahrenheit = (((return_value / pow(2, 16)) * 165 - 40) * 9 / 5) + 32;
    //printf("%f degrees F\n", fFahrenheit);

    return fahrenheit;
}


/*
 * Reads in the HDC1080 humidity register.
 * Converts value into relative humditiy.
 */
float sensor_read_hmd()
{
    uint8_t reg_value[2] = {};
    int8_t return_bytes = 0;
    uint16_t return_value = 0;
    float relative_humidity = 0;

    // point to humidity register
    return_bytes = i2c_write_blocking(PICO_DEFAULT_I2C_INSTANCE, HDC_ADDR, &HDC_HMD_REG, 1, false);
    vTaskDelay(20);

    // read from humidity register
    return_bytes = i2c_read_blocking(PICO_DEFAULT_I2C_INSTANCE, HDC_ADDR, reg_value, 2, false);
    return_value = (reg_value[0] << 8) | reg_value[1];

    // convert return value to relative humidity
    relative_humidity = (return_value / pow(2, 16)) * 100;
    //printf("RH %f\n", fRelativeHumdity);

    // return relative humidity
    return relative_humidity;
}
