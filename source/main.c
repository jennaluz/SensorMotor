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

    // create queues
    xDisplayQueue = xQueueCreate(10, sizeof(int));
    xMotorQueue = xQueueCreate(1, sizeof(int));
    xTemperatureQueue = xQueueCreate(1, sizeof(int));
    xHumidityQueue = xQueueCreate(1, sizeof(int));

    // create tasks
    xTaskCreate(vButton1Handler, "Button 1 Handler", 256, NULL, 4, NULL);
    xTaskCreate(vButton2Handler, "Button 2 Handler", 256, NULL, 4, NULL);
    xTaskCreate(vButton3Handler, "Button 3 Handler", 256, NULL, 4, NULL);
    //xTaskCreate(vDisplayHandler, "7 Segment Display Handler", 256, NULL, 3, NULL);
    xTaskCreate(vMotorHandler, "Stepper Motor Handler", 256, NULL, 3, NULL);
    xTaskCreate(vSensorHandler, "HDC1080 Handler", 256, NULL, 3, NULL);

    vTaskStartScheduler();

    while (true) {};
}
