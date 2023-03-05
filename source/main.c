/*
 * SensorMotor/source/main.c
 */

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/time.h>

#include <stdio.h>

#include "button.h"
#include "display_driver.h"
#include "hdc1080_driver.h"
#include "motor_driver.h"


int main()
{
    stdio_init_all();

    // initialize stepper motor gpio pins
    vDisplayInit();
    vMotorInit();
    vHDC1080Init();
    vButtonIRQInit();

    // create semaphores
    xButton1Semaphore = xSemaphoreCreateBinary();
    xButton2Semaphore = xSemaphoreCreateBinary();
    xButton3Semaphore = xSemaphoreCreateBinary();

    // create tasks
    xTaskCreate(vButton1, "Button 1 Event", 256, NULL, 5, NULL);
    xTaskCreate(vButton2, "Button 2 Event", 256, NULL, 5, NULL);
    xTaskCreate(vButton3, "Button 3 Event", 256, NULL, 5, NULL);

    vTaskStartScheduler();

    while (true) {};
}
