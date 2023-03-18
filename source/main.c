/*
 * SensorMotor/source/main.c
 */


#include <FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/time.h>

#include <stdio.h>

#include "button.h"
#include "display.h"
#include "display_driver.h"
#include "motor.h"
#include "motor_driver.h"
#include "sensor.h"
#include "sensor_driver.h"


int main()
{
    stdio_init_all();

    // initialize stepper motor gpio pins
    vDisplayInit();
    vMotorInit();
    vSensorInit();
    vButtonIRQInit();

    // create semaphores
    xButton1Semaphore = xSemaphoreCreateBinary();
    xButton2Semaphore = xSemaphoreCreateBinary();
    xButton3Semaphore = xSemaphoreCreateBinary();
    xDisplaySemaphore = xSemaphoreCreateBinary();

    // create queues
    xDisplayQueue = xQueueCreate(10, sizeof(int));
    xLeftDisplayQueue = xQueueCreate(1, sizeof(uint8_t));
    xRightDisplayQueue = xQueueCreate(1, sizeof(uint8_t));
    xMotorQueue = xQueueCreate(1, sizeof(int));
    xSensorBaseQueue = xQueueCreate(1, sizeof(int));
    xTemperatureQueue = xQueueCreate(1, sizeof(int));
    xHumidityQueue = xQueueCreate(1, sizeof(int));

    // create tasks
    xTaskCreate(vButton1Handler, "Button 1", 256, NULL, 4, NULL);
    xTaskCreate(vButton2Handler, "Button 2", 256, NULL, 4, NULL);
    xTaskCreate(vButton3Handler, "Button 3", 256, NULL, 4, NULL);
    xTaskCreate(vDisplayHandler, "Display", 256, NULL, 3, NULL);
    xTaskCreate(vLeftDisplayHandler, "Left Display", 256, NULL, 3, NULL);
    xTaskCreate(vRightDisplayHandler, "Right Display", 256, NULL, 3, NULL);
    xTaskCreate(vMotorHandler, "Stepper Motor Handler", 256, NULL, 3, NULL);
    xTaskCreate(vSensorHandler, "HDC1080 Handler", 256, NULL, 3, NULL);

    // give display semaphore
    xSemaphoreGive(xDisplaySemaphore);

    vTaskStartScheduler();

    while (true) {};
}
